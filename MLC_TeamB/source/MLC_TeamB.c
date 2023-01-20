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
 * Command Returns
 */
#define START_OR_STOP 1
#define FORWORD 2
#define BACKWORD 3
#define PAUSE 4
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

/**
 * Configuration I2C Frame
 */
#define I_REFRESH_RATE_MSH 0
#define I_REFRESH_RATE_LSH 1
#define I_RGB_SCHEME 2
#define I_RED_START_VALUE 3
#define I_GREEN_START_VALUE 4
#define I_BLUE_START_VALUE 5
#define I_RED_END_VALUE 6
#define I_GREEN_END_VALUE 7
#define I_BLUE_END_VALUE 8
#define I_RED_RESOLUTION_VALUE 9
#define I_GREEN_RESOLUTION_VALUE 10
#define I_BLUE_SRESOLUTION_VALUE 11
#define I_CHANGE_RATE_HUNDREDS 12
#define I_CHANGE_RATE 13
#define I_MODE 14
#define I_CYCLES 15
//#define I2C_FRAME_WIDTH 15
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
uint8_t i2c_free_flag = 1;

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
		i2c_master_edma_handle_t *handle, status_t status, void *userData) {
	/* Signal transfer success when received success status. */
	//PRINTF("\r\nI2C Transfer Complete\r\n");
	i2c_free_flag = 1;
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
		configMINIMAL_STACK_SIZE + 1200,
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
void i2c_send_config(uint8_t *config_buf) {
	while (!i2c_free_flag)
		; //Wait for I2C
	i2c_free_flag--;
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
	if (i2c_status != 0) {
		PRINTF("I2C Error %d", i2c_status);
	}
}
status_t master_handshake(void) {
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
	masterXfer.data = (uint8_t*) master_handshake_buffer;
	status_t i2c_status = I2C_MasterTransferEDMA(I2C_MASTER_BASEADDR,
			&g_m_dma_handle, &masterXfer);
	PRINTF("\r\nI2C Transfer Status: %d\r\n", i2c_status);
	masterXfer.direction = kI2C_Read;
	masterXfer.data = (uint8_t*) slave_data;
	i2c_status += I2C_MasterTransferEDMA(I2C_MASTER_BASEADDR, &g_m_dma_handle,
			&masterXfer);
//	for (uint32_t i = 0U; i < I2C_FRAME_WIDTH; i++) {
//		PRINTF("%c	 ", slave_data[i]);
//	}
	if (strcmp(slave_data, slave_handshake_buffer) == 0) {
		ret = kStatus_Success;
	} else {
		ret = kStatus_Fail;
	}
//	PRINTF("\r\nI2C Transfer Status: %d\r\n", ret);
	return ret;
}
static void ui_master(void *pvParameters) {

	boot_screen();
	int ui_status_flags[19] = { 1000, 1, 0, 0, 0, 7, 7, 3, 1, 1, 1, 1, 1, 1, 0,
			0, 0, 0 };
	uint8_t i2c_config[I2C_FRAME_WIDTH];
	//int dummy[19] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int color_q[5] = { 0, 0, 0, 0, 0 };
	int stop_val[15] = { 0, 's', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int pause_val[15] = { 0, 'p', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint8_t stop_val_i2c[15] = { 0, 0, 's', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint8_t pause_val_i2c[15] =
			{ 0, 0, 'p', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	while (1) {
		ui_status_flags[COMPANION_STATUS] = master_handshake();
		master_ui(ui_status_flags);
		i2c_config[I_REFRESH_RATE_MSH] =
				(uint8_t) (ui_status_flags[REFRESH_RATE] / 100);
		i2c_config[I_REFRESH_RATE_LSH] =
				(uint8_t) (ui_status_flags[REFRESH_RATE] % 100);
		for (int i = I_RGB_SCHEME; i < I_CHANGE_RATE_HUNDREDS; i++) {
			i2c_config[i] = (uint8_t) ui_status_flags[i - 1];
		}
		i2c_config[I_CHANGE_RATE_HUNDREDS] =
				(uint8_t) ui_status_flags[CHANGE_RATE] / 100;
		i2c_config[I_CHANGE_RATE] = (uint8_t) ui_status_flags[CHANGE_RATE]
				% 100;
		i2c_config[I_CYCLES] = (uint8_t) ui_status_flags[CYCLES];
		i2c_send_config(i2c_config);
//		while (xQueueReceive(config_queue, dummy, 0))
//			;
		while (1) {
			if (xQueueSendToFront(config_queue, ui_status_flags,
					0) == pdPASS) {
				break;
			}
		}
		ui_homescreen(ui_status_flags);
		uint8_t i2c_send[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		while (1) {
			if (xQueueReceive(color_queue, color_q, 0) == pdPASS) {
				PRINTF("\033[24;55H                               ");
				PRINTF("\033[24;55H                               ");
				PRINTF("\033[24;55H%d %d %d", color_q[1], color_q[2],
						color_q[3]);
				i2c_send[0] = (uint8_t) 0;
				i2c_send[1] = (uint8_t) color_q[1];
				i2c_send[2] = (uint8_t) color_q[2];
				i2c_send[3] = (uint8_t) color_q[3];
				PRINTF("\033[25;55H%d %d %d", i2c_send[1], i2c_send[2],
						i2c_send[3]);
				ui_status_flags[CURRENT_RED_VALUE] = color_q[1];
				ui_status_flags[CURRENT_GREEN_VALUE] = color_q[2];
				ui_status_flags[CURRENT_BLUE_VALUE] = color_q[3];
				i2c_send_config(i2c_send);
				if (color_q[1] == ui_status_flags[RED_END_VALUE]
						&& color_q[2] == ui_status_flags[GREEN_END_VALUE]
						&& color_q[3] == ui_status_flags[BLUE_END_VALUE]) {
					start_stop(ui_status_flags);
					break;
				}
			}
			if (valid_data) {
				valid_data = 0;
				if (tx_buffer == 13) {
					i2c_send_config(stop_val_i2c);
					start_stop(ui_status_flags);
					while (1) {
						if (xQueueSendToFront(config_queue, stop_val,
								0) == pdPASS) {
							break;
						}
					}



					//while(1);
					break;
				} else if (tx_buffer == 32) {

					play_pause(ui_status_flags);

					i2c_send_config(pause_val_i2c);
					while (1) {
						if (xQueueSendToFront(config_queue, pause_val,
								0) == pdPASS) {
							break;
						}
					}
				}
			}
		}
	}
	//ui_delay(5000000);
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
	for (;;) {
		//PRINTF("Pattern generator\r\n");
		if (xQueueReceive(config_queue, config_arr, 0) == pdPASS) {
			auto_mode(config_arr);
//			while (1) {
//				if (xQueueSendToFront(color_queue, color_arr,
//						0) == pdPASS) {
//					break;
//				}
//			}
		}
		//vTaskSuspend(NULL);
	}
}
int colour_update(int red, int green, int blue) {
	int colour_pattern[5];

	colour_pattern[0] = 1;
	colour_pattern[1] = red;
	colour_pattern[2] = green;
	colour_pattern[3] = blue;

	while (1) {
		if (xQueueSendToFront(color_queue, colour_pattern,0) == pdPASS) {
			break;
		}
	}

	return 0;
}
int comnts_read(void) {
	int commands[15];
	int ret = 0;
	if (xQueuePeek(config_queue, commands, 0) == pdPASS) {
		///PRINTF("c[0] %d c[1] %d", commands[0], commands[1]);
		if (commands[0] == 0 && commands[1] == 's') {
			PRINTF("Stop Received from Queue");
			xQueueReceive(config_queue, commands, 0);
			ret = START_OR_STOP;
		} else if (commands[0] == 0 && commands[1] == '<') {
			PRINTF("Back Received from Queue");
			xQueueReceive(config_queue, commands, 0);
			ret = BACKWORD;
		} else if (commands[0] == 0 && commands[1] == '>') {
			PRINTF("Forward Received from Queue");
			xQueueReceive(config_queue, commands, 0);
			ret = FORWORD;
		} else if (commands[0] == 0 && commands[1] == 'p') {
			PRINTF("Pause Received from Queue");
			xQueueReceive(config_queue, commands, 0);
			ret = PAUSE;
		}
	}
	return ret;
}
