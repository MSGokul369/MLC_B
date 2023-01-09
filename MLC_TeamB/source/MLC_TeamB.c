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

/*System includes.*/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_uart.h"
#include "timers.h"

/*Program includes.*/
#include "../UI/user_interface.h"

/*RTOS includes.*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*******************************************
 * Const and Macro Defines
 *******************************************/

/* UART instance and clock */
#define UART            UART0
#define UART_CLKSRC     UART0_CLK_SRC
#define UART_CLK_FREQ   CLOCK_GetFreq(UART0_CLK_SRC)
#define UART_IRQn       UART0_RX_TX_IRQn
#define UART_IRQHandler UART0_RX_TX_IRQHandler

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

/***********************************
 *  Typedefs and Enum Declarations
 ***********************************/
//none
/***********************************
 *  External Variable Declarations
 ***********************************/
//none
/***********************************
 *  Const Declarations
 ***********************************/
//none
/***********************************
 *  Public Variables
 ***********************************/
//none
/***********************************
 *  Private Variables
 ***********************************/
//none
/***********************************
 * Private Prototypes
 ***********************************/
static void generate_pattern(void *pvParameters);

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();

	/* Enable RX interrupt. */
	UART_EnableInterrupts(UART,
			kUART_RxDataRegFullInterruptEnable
					| kUART_RxOverrunInterruptEnable);
	EnableIRQ(UART_IRQn);

	uint32_t master_slave_flag;
	master_slave_flag = GPIO_PinRead( GPIOD, 0);

	if (master_slave_flag == 1) {
		if (xTaskCreate(master_ui, "MASTER_UI", 1000, NULL, 2,
		NULL) != pdPASS) {
			PRINTF("Task creation failed!.\n\t");
			while (1)
				;
		}
	} else if (master_slave_flag == 0) {
		if (xTaskCreate(slave_ui, "SLAVE_UI", 1000, NULL, 2,
		NULL) != pdPASS) {
			PRINTF("Task creation failed!.\n\t");
			while (1)
				;
		}
		if (xTaskCreate(generate_pattern, "GENERATE_PATTERN", 1000, NULL, 2,
		NULL) != pdPASS) {
			PRINTF("Task creation failed!.\n\t");
			while (1)
				;
		}
	}
		vTaskStartScheduler();
		while (1)
			;
		return 0;

}

static void generate_pattern(void *pvParameters) {

	PRINTF("\033[16;25Hhello");

	while (1)
		;
}
