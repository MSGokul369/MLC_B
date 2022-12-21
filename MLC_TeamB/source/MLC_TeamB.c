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
#include "user_interface.h"

/*Kernel Includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"


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
//none

/***********************************
 * Private Prototypes
 ***********************************/
//none

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif
	homescreen();
	PRINTF("Hello World\n");
	while (1);
	return 0;
}
