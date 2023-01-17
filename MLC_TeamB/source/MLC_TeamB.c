/**
 * @file	MLC_TeamB.c
 * @brief	Multicolor LED Controller Software for single RGB LED.
 *
 * All functions to access/control FRDM K-64 and RGB LED is located in this file.
 *
 * @note
 *
 * Revision History:
 * 	-161222 MSG : Creation Date
 */

/* Freescale includes. */
#include <stdio.h>
#include "peripherals.h"
#include "MK64F12.h"
#include "fsl_uart.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "fsl_i2c_edma.h"
#include "fsl_dmamux.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#include "clock_config.h"
#include "board.h"
#include "pin_mux.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/*Program includes.*/
#include "../UI/user_interface.h"
#include "../Peripherals/peripheral.h"
#include "../Pattern_Generation/Pattern_Generation.h"
/*******************************************
 * Const and Macro Defines
 *******************************************/

/* UART instance and clock */
#define UART            UART0
#define UART_CLKSRC     UART0_CLK_SRC
#define UART_CLK_FREQ   CLOCK_GetFreq(UART0_CLK_SRC)
#define UART_IRQn       UART0_RX_TX_IRQn
#define UART_IRQHandler UART0_RX_TX_IRQHandler

/***************************************/
/**
 * Colour Queue Data Format
 */
#define DATA_FLAG 0
#define RED_VALUE 1
#define GREEN_VALUE 2
#define BLUE_VALUE 3
/***************************************/
/**
 * Configuration Queue Data Format
 */
#define REFRESH_RATE 0
#define RGB_SCHEME 1
#define RED_START_VALUE 2
#define GREEN_START_VALUE 3
#define BLUE_START_VALUE 4
#define RED_END_VALUE 5
#define GREEN_END_VALUE 6
#define BLUE_END_VALUE 7
#define RED_RESOLUTION_VALUE 8
#define GREEN_RESOLUTION_VALUE 9
#define BLUE_RESOLUTION_VALUE 10
#define CHANGE_RATE 11
#define MODE 12
#define CYCLES 13
//Additions  for UI Data Handling
#define PROCESS_STATUS 14
#define COMPANION_STATUS 15
#define CURRENT_RED_VALUE 16
#define CURRENT_GREEN_VALUE 17
#define CURRENT_BLUE_VALUE 18

/***************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void pattern_task(void *pvParameters);
static void ui_master(void *pvParameters);
static void ui_slave(void *pvParameters);

static QueueHandle_t config_queue = NULL;
static QueueHandle_t color_queue = NULL;

extern uint8_t valid_data;
extern uint8_t tx_buffer;

char master_handshake_buffer[10] = "MASTER";
char slave_handshake_buffer[10] = "SLAVE";

i2c_master_edma_handle_t g_m_dma_handle;
edma_handle_t edmaHandle;
uint8_t g_master_txBuff[I2C_FRAME_WIDTH] = "MASTER";
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
static void i2c_master_callback(I2C_Type *base,
		i2c_master_edma_handle_t *handle, status_t status, void *userData)
{
	/* Signal transfer success when received success status. */
	PRINTF("\r\nI2C Transfer Complete\r\n");
}

int main(void) {
	/* Init board hardware. */
	int master_slave_flag = 1;

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();
	BOARD_InitI2CPeripherals();

	master_slave_flag = GPIO_PinRead( GPIOD, 0);
	config_queue = xQueueCreate(1, sizeof(int) * 15);
	color_queue = xQueueCreate(1, sizeof(int) * 4);
	vQueueAddToRegistry(config_queue, "Configuration Queue");
	vQueueAddToRegistry(color_queue, "Color Value Queue");
	/* Enable RX interrupt. */
	UART_EnableInterrupts(UART,
			kUART_RxDataRegFullInterruptEnable
					| kUART_RxOverrunInterruptEnable);
	EnableIRQ(UART_IRQn);
	master_slave_flag = GPIO_PinRead(GPIOD, 0);
	if (master_slave_flag) {

		if (xTaskCreate(ui_master, "Master User Interface",
		configMINIMAL_STACK_SIZE + 1000,
		NULL, hello_task_PRIORITY, NULL) !=
		pdPASS) {
			PRINTF("Task creation failed!.\r\n");
			while (1)
				;
		}
	} else {
		if (xTaskCreate(ui_slave, "Slave User Interface",
		configMINIMAL_STACK_SIZE + 1000,
		NULL, hello_task_PRIORITY, NULL) !=
		pdPASS) {
			PRINTF("Task creation failed!.\r\n");
			while (1)
				;
		}
	}

	if (xTaskCreate(pattern_task, "Pattern Generator",
	configMINIMAL_STACK_SIZE + 500, NULL, hello_task_PRIORITY, NULL) !=
	pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	vTaskStartScheduler();
	for (;;)
		;
}
void i2c_send_config(uint8_t config_buf[16])
{
	i2c_master_config_t masterConfig;
	uint32_t sourceClock;
	i2c_master_transfer_t masterXfer;
	edma_config_t config;
	DMAMUX_Init(I2C_DMAMUX_BASEADDR);
	EDMA_GetDefaultConfig(&config);
	EDMA_Init(I2C_DMA_BASEADDR, &config);

	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = I2C_BAUDRATE;
	sourceClock = I2C_MASTER_CLK_FREQ;
	I2C_MasterInit(I2C_MASTER_BASEADDR, &masterConfig, sourceClock);
	memset(&g_m_dma_handle, 0, sizeof(g_m_dma_handle));
	memset(&masterXfer, 0, sizeof(masterXfer));
	//uint8_t g_master_txBuff[I2C_FRAME_WIDTH] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	uint8_t deviceAddress = 0x01U;
	masterXfer.slaveAddress = I2C_MASTER_SLAVE_ADDR;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = (uint32_t) deviceAddress;
	masterXfer.subaddressSize = 0;
	masterXfer.data = g_master_txBuff;
	masterXfer.dataSize = I2C_FRAME_WIDTH;
	masterXfer.flags = kI2C_TransferDefaultFlag;
	DMAMUX_SetSource(I2C_DMAMUX_BASEADDR, I2C_DMA_CHANNEL, DMA_REQUEST_SRC);
	EDMA_CreateHandle(&edmaHandle, I2C_DMA_BASEADDR, I2C_DMA_CHANNEL);
	DMAMUX_EnableChannel(I2C_DMAMUX_BASEADDR, I2C_DMA_CHANNEL);
	I2C_MasterCreateEDMAHandle(I2C_MASTER_BASEADDR, &g_m_dma_handle,
			i2c_master_callback, NULL, &edmaHandle);
	masterXfer.direction = kI2C_Write;
	masterXfer.data = config_buf;
	status_t i2c_status = I2C_MasterTransferEDMA(I2C_MASTER_BASEADDR,
			&g_m_dma_handle, &masterXfer);
	if (i2c_status != 0)
	{
		PRINTF("I2C Error %d", i2c_status);
	}
}
status_t master_handshake(void)
{
	i2c_master_config_t masterConfig;
	uint32_t sourceClock;
	i2c_master_transfer_t masterXfer;
	edma_config_t config;
	char slave_data[I2C_FRAME_WIDTH] = "";
	status_t ret;

	DMAMUX_Init(I2C_DMAMUX_BASEADDR);
	EDMA_GetDefaultConfig(&config);
	EDMA_Init(I2C_DMA_BASEADDR, &config);

	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = I2C_BAUDRATE;
	sourceClock = I2C_MASTER_CLK_FREQ;
	I2C_MasterInit(I2C_MASTER_BASEADDR, &masterConfig, sourceClock);
	memset(&g_m_dma_handle, 0, sizeof(g_m_dma_handle));
	memset(&masterXfer, 0, sizeof(masterXfer));
	//uint8_t g_master_txBuff[I2C_FRAME_WIDTH] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	uint8_t deviceAddress = 0x01U;
	masterXfer.slaveAddress = I2C_MASTER_SLAVE_ADDR;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = (uint32_t) deviceAddress;
	masterXfer.subaddressSize = 0;
	masterXfer.data = g_master_txBuff;
	masterXfer.dataSize = I2C_FRAME_WIDTH;
	masterXfer.flags = kI2C_TransferDefaultFlag;
	DMAMUX_SetSource(I2C_DMAMUX_BASEADDR, I2C_DMA_CHANNEL, DMA_REQUEST_SRC);
	EDMA_CreateHandle(&edmaHandle, I2C_DMA_BASEADDR, I2C_DMA_CHANNEL);
	DMAMUX_EnableChannel(I2C_DMAMUX_BASEADDR, I2C_DMA_CHANNEL);
	I2C_MasterCreateEDMAHandle(I2C_MASTER_BASEADDR, &g_m_dma_handle,
			i2c_master_callback, NULL, &edmaHandle);

	masterXfer.direction = kI2C_Write;
	masterXfer.data = (uint8_t *)master_handshake_buffer;
	status_t i2c_status = I2C_MasterTransferEDMA(I2C_MASTER_BASEADDR,
			&g_m_dma_handle, &masterXfer);
	PRINTF("\r\nI2C Transfer Status: %d\r\n", i2c_status);
	masterXfer.direction = kI2C_Read;
	masterXfer.data = (uint8_t *)slave_data;
	i2c_status += I2C_MasterTransferEDMA(I2C_MASTER_BASEADDR, &g_m_dma_handle,
			&masterXfer);
	for (uint32_t i = 0U; i < I2C_FRAME_WIDTH; i++)
	{
		PRINTF("%c	 ", slave_data[i]);
	}
	if (strcmp(slave_data, slave_handshake_buffer) == 0)
	{
		ret = kStatus_Success;
	}
	else
	{
		ret = kStatus_Fail;
	}
	PRINTF("\r\nI2C Transfer Status: %d\r\n", i2c_status);
	return ret;
}
static void ui_master(void *pvParameters) {

	boot_screen();
	int ui_status_flags[19] = { 1000, 1, 0, 0, 0, 7, 7, 0, 1, 1, 0, 1, 1, 1, 0, 0,
			0, 0 };
	int color_q[5] = { 0, 0, 0, 0, 0 };
	while (1) {
		ui_status_flags[COMPANION_STATUS] = master_handshake();
		master_ui(ui_status_flags);
		while (1) {
			if (xQueueSendToFront(config_queue, ui_status_flags,
					0) == pdPASS) {
				break;
			}
		}
		ui_homescreen(ui_status_flags);
		while (1) {
			if (xQueueReceive(color_queue, color_q, 0) == pdPASS) {
				PRINTF("\033[24;55H%d %d %d", color_q[1], color_q[2],
						color_q[3]);
			}
			if (color_q[1] == ui_status_flags[RED_END_VALUE]
					&& color_q[2] == ui_status_flags[GREEN_END_VALUE]
					&& color_q[3] == ui_status_flags[BLUE_END_VALUE]) {
				break;
			}
			if (valid_data) {
				valid_data = 0;
				if (tx_buffer == 13) {
					start_stop(ui_status_flags);
					break;
				}
				else if(tx_buffer == 32)
				{
					play_pause(ui_status_flags);
					PRINTF("Paused");
				}
			}
		}
		//ui_delay(5000000);
	}
}
//static void color_print(void *pvParameters) {
//	while (1) {
//		if (xQueueReceive(color_queue, color_q, 0) == pdPASS) {
//			PRINTF("\033[24;55H%d %d %d", color_q[1], color_q[2], color_q[3]);
//		}
//		if (color_q[1] == ui_status_flags[RED_END_VALUE]
//				&& color_q[2] == ui_status_flags[GREEN_END_VALUE]
//				&& color_q[3] == ui_status_flags[BLUE_END_VALUE]) {
//			break;
//		}
//	}
//}
static void ui_slave(void *pvParameters) {

}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void pattern_task(void *pvParameters) {
	int config_arr[15];
	int color_arr[4];
	int i, j, k, cur_red, cur_green, cur_blue;
	for (;;) {
		//PRINTF("Pattern generator\r\n");
		if (xQueueReceive(config_queue, config_arr, 0) == pdPASS) {
			color_arr[DATA_FLAG] = 1;
			color_arr[RED_VALUE] = config_arr[RED_START_VALUE];
			color_arr[GREEN_VALUE] = config_arr[GREEN_START_VALUE];
			color_arr[BLUE_VALUE] = config_arr[BLUE_START_VALUE];
			for (i = 0; +i <= config_arr[RED_END_VALUE]; i +=
					config_arr[RED_RESOLUTION_VALUE]) {
				cur_red = config_arr[RED_START_VALUE] + i;
				for (j = 0;
						(config_arr[GREEN_START_VALUE] + j)
								<= config_arr[GREEN_END_VALUE]; j +=
								config_arr[GREEN_RESOLUTION_VALUE]) {
					cur_green = config_arr[GREEN_START_VALUE] + j;
					for (k = 0;
							(config_arr[BLUE_START_VALUE] + k)
									<= config_arr[BLUE_END_VALUE]; k +=
									config_arr[BLUE_RESOLUTION_VALUE]) {
						cur_blue = config_arr[BLUE_START_VALUE] + k;
						color_arr[DATA_FLAG] = 1;
						color_arr[RED_VALUE] = cur_red;
						color_arr[GREEN_VALUE] = cur_green;
						color_arr[BLUE_VALUE] = cur_blue;
//						PRINTF("\033[24;55H%d %d %d", cur_red, cur_green,
//								cur_blue);
//						PRINTF("PAT_OK\r\n");
						while (1) {
							if (xQueueSendToFront(color_queue, color_arr,
									0) == pdPASS) {
								break;
							}
						}
						ui_delay(50000);
						if (config_arr[BLUE_RESOLUTION_VALUE] == 0)
							break;
					}
					if (config_arr[GREEN_RESOLUTION_VALUE] == 0)
						break;
				}
				if (config_arr[RED_RESOLUTION_VALUE] == 0)
					break;
			}
		}
		//vTaskSuspend(NULL);
	}
}
