/**
 * @file	MLC_TeamB.c
 * @brief	Multicolor LED Controller Software for single RGB LED.
 *
 * All functions to access/control FRDM K-64 and RGB LED is located in this file.
 *
 * @note
 *
 * Revision History:
 * 	-161220 MSG : Creation Date
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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "../UI/user_interface.h"

/*******************************************
 * Const and Macro Defines
 *******************************************/

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
static void configure_device(void *pvParameters);
static void generate_pattern(void *pvParameters);

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Define the init structure for the output LED pin*/
	    gpio_pin_config_t pin_config = {
	        kGPIO_DigitalInput
	    };
	   GPIO_PinInit(GPIOD, 0U, &pin_config);


	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();

	if (xTaskCreate(configure_device, "CONFIGURE_DEVICE", 1000, NULL, 2,
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
	vTaskStartScheduler();
	while (1)
		;
	return 0;
}

static void configure_device(void *pvParameters) {

	uint32_t master_slave_flag;
	master_slave_flag = GPIO_PinRead ( GPIOD, 0 );
	//PRINTF("%d", master_slave_flag);
	if (master_slave_flag == 1){
		master_ui();
	}else {
		slave_ui();
	}
}

static void generate_pattern(void *pvParameters) {
    int number;

    PRINTF("\033[16;25Hhello");

	while (1)
		;
}
