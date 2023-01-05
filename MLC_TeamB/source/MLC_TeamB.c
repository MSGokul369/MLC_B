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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "../Pattern_Generation/Pattern_Generation.h"
#include "../UI/user_interface.h"

/*******************************************
 * Const and Macro Defines
 *******************************************/

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

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();
	int com_arr[] = {1000, 1, 0, 0, 0, 7, 7, 3, 1, 1, 1, 2, 1, 2};
	auto_mode(com_arr);
	if (xTaskCreate(generate_pattern, "CONFIGURE_DEVICE", 1000, NULL, 2,
	NULL) != pdPASS) {
		PRINTF("Task creation failed!.\n\t");
		while (1)
			;
	}
	if (xTaskCreate(configure_device, "GENERATE_PATTERN", 1000, NULL, 2,
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
	master_ui();
	 taskYIELD ()
}
static void generate_pattern(void *pvParameters) {


	int config[14] ={1000,1,7,7,3,0,0,0,1,1,1,1,1};


	auto_mode(config);
	PRINTF("Pattern");
	while (1)
		;
}
