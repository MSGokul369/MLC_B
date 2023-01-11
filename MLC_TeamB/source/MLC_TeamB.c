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

void delay(float second) {
	second = second * (42000000 / 20);
	while (second)
		second--;
}

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
	//BOARD_InitI2CPeripherals();

	master_slave_flag = GPIO_PinRead( GPIOD, 0);

	/* Enable RX interrupt. */
	UART_EnableInterrupts(UART,
			kUART_RxDataRegFullInterruptEnable
					| kUART_RxOverrunInterruptEnable);
	EnableIRQ(UART_IRQn);

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
	configMINIMAL_STACK_SIZE + 100, NULL, hello_task_PRIORITY, NULL) !=
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
	int configuration_send_array[14] = { 1, 1, 0, 0, 0, 7, 7, 3, 1, 1, 1, 1, 1,
			1 };
	int configuration_array[14] = { 1, 1, 0, 0, 0, 7, 7, 3, 1, 1, 1, 1, 1, 1 };
	int *configuration_pointer = configuration_array;

	while (1) {
		while (1) {

			configuration_pointer = master_ui(configuration_array[0],
					configuration_array[1], configuration_array[2],
					configuration_array[3], configuration_array[4],
					configuration_array[5], configuration_array[6],
					configuration_array[7], configuration_array[8],
					configuration_array[9], configuration_array[10],
					configuration_array[11], configuration_array[12],
					configuration_array[13]);

			if ((configuration_pointer[2] != 112)
					&& (configuration_pointer[2] != 115)) {

				for (int i = 0; i <= 13; i++) {
					configuration_array[i] = configuration_pointer[i];
				}
				for (int i = 0; i <= 13; i++) {
					configuration_send_array[i] = configuration_pointer[i];
				}

				for (int i = 0; i <= 13; i++) {
					PRINTF("%d ", configuration_array[i]);
				}
				for (int i = 0; i <= 13; i++) {
					PRINTF("%d ", configuration_send_array[i]);
				}

			} else if ((configuration_pointer[2] == 112)
					&& (configuration_pointer[2] == 115)) {

				configuration_pointer = master_ui(configuration_array[0],
						configuration_array[1], configuration_array[2],
						configuration_array[3], configuration_array[4],
						configuration_array[5], configuration_array[6],
						configuration_array[7], configuration_array[8],
						configuration_array[9], configuration_array[10],
						configuration_array[11], configuration_array[12],
						configuration_array[13]);

				for (int i = 0; i <= 13; i++) {
					configuration_send_array[i] = configuration_pointer[i];
				}

				for (int i = 0; i <= 13; i++) {
					PRINTF("%d ", configuration_array[i]);
				}
				for (int i = 0; i <= 13; i++) {
					PRINTF("%d ", configuration_send_array[i]);
				}
			}
		}
	}
}

static void ui_slave(void *pvParameters) {

}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void pattern_task(void *pvParameters) {
	/*int config_arr[15];
	 int color_arr[4];
	 int i, j, k, cur_red, cur_green, cur_blue;
	 for (;;) {
	 PRINTF("Pattern generator\r\n");
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
	 while (1) {
	 if (xQueueSendToFront(color_queue, color_arr,
	 0) == pdPASS) {
	 break;
	 }
	 }
	 delay(0.01 * config_arr[CHANGE_RATE]);
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
	 */
}
