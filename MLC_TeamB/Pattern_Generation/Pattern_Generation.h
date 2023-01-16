
/**
 * @file Pattern_Generation.h
 * Header for pattern generator
 *
 * @note
 *
 * Revision History :
 * 			16122022 NN : Creation Date
 */
#include "pin_mux.h"
#include "clock_config.h"
/********************************************
 * Const and Macro Defines
 ********************************************/

//NULL

/*********************************************
 * Typedefs and Enum Declarations
 *********************************************/

//NULL

/**********************************************
 * const Declarations
 **********************************************/

//NULL

/***********************************************
 * Variable Declarations
 **********************************************/

// NULL

/***********************************************
 * Prototype
 ***********************************************/


int auto_mode(int config_array[]);
int colour_update(int red, int green, int blue, uint8_t colour_pattern[]);
void Delay(int delay_mul);
int manual_mode(int config_array[]);
int coments_read(void);
