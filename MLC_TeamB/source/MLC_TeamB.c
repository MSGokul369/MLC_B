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
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */

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

static void ui_master(void *pvParameters) {

	boot_screen();
	int ui_status_flags[19] = { 1, 1, 0, 0, 0, 7, 7, 3, 1, 1, 1, 1, 1, 1, 0, 0,
			0, 0 };
	int color_q[5] = { 0, 0, 0, 0, 0 };
	while (1) {
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
				PRINTF("%d", tx_buffer);
				if (tx_buffer == 13) {
					break;
				}
				else if(tx_buffer == 32)
				{
					PRINTF("Paused");
					while(1);
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
