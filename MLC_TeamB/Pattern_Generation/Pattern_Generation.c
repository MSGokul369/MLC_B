/**
 * @file  Pattern_generation.c
 * @brief Pattern generator for MLC
 *
 * Functions for operating MLC in different mode  and associated delay  function
 *
 * @note
 *
 * Revision History
 * 			16122020  NN : Creation Date
 */
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_ftm.h"
#include "fsl_debug_console.h"
#include "task.h"
#include "queue.h"
/*************************************************
 * Const and Macro Defines
 *************************************************/
#define FTM_ADDRESS FTM3
#define BLUE 1U
#define RED 2U
#define GREEN 3
#define BLUE_MAX 3.0  //Max value is calculated by formula 2^n - 1 where n is the number of bit for representing a colour
#define RED_MAX 7.0
#define GREEN_MAX 7.0
#define FTM_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#define FTM_MODE kFTM_EdgeAlignedPwm
#define START_OR_STOP 1
#define FORWORD 2
#define BACKWORD 3
#define PAUSE 4


/**************************************************************
 *Typedefs and Enum Declarations
 *************************************************************/

//  None
/****************************************************************
 * External Variable Declarations
 ****************************************************************/

//  None
/*****************************************************************
 * Const Declarations
 *****************************************************************/

//  None
/******************************************************************
 * Public Variables
 ******************************************************************/

//  None
/******************************************************************
 * Private Variables
 ******************************************************************/

ftm_config_t ftmInfo;
int red_inc, green_inc, blue_inc;
int red_dec, green_dec, blue_dec;
uint8_t red_duty, command;
uint8_t green_duty, break_flag = 0;
uint8_t blue_duty;
uint8_t cycle;
ftm_chnl_pwm_signal_param_t parameter[3];

/*******************************************************************
 * Private Prototype
 *******************************************************************/

int Delay(int delay_mul);

/******************************************************************
 * Public Prototype
 ******************************************************************/
//int auto_mode(int config_array[]);
//int manual_mode(int config_array[14]);
/**
 *@ brief Delay
 *Function for implementing delay in microseconds
 *
 *@param delay_mul
 *
 *@return return_value
 *
 *@note
 *
 *Revision History
 * 			16122022 NN : Creation Date
 * 			10012023 NN : Delay function added
 * 			11012023 NN : Bug fixing
 */
int Delay(int delay_mul) {
	BaseType_t return_value;
	TickType_t xTaskWakeuptime;
	TickType_t delay_time;
	xTaskWakeuptime = xTaskGetTickCount();
	delay_time = delay_mul*10;
	return_value = xTaskDelayUntil(&xTaskWakeuptime, delay_time);
	return return_value;
}

/**
 * @brief clour_update
 * Function for updating current colours in the queue
 *
 * @param red
 * @param green
 * @param blue
 * @param colour_pattern[]
 *
 * @return 0
 *
 * @note
 *
 * Revision History
 * 			16122022 NN : Creation Date
 * 			11012023 NN : Updated queue usage
 *
 */

/***
 * @brief auto_mode
 *
 * Function for generating patterns in auto up mode, auto down mode, auto updown mode
 *
 * @param confog_array[]
 *
 * @return 0
 *
 * @note
 *
 * Revision History
 * 			17122022 NN : Creation Date
 * 			09012023 NN : Bug fixing
 *
 */
int auto_mode(int config_array[]) {

	FTM_GetDefaultConfig(&ftmInfo);
	ftmInfo.prescale = FTM_CalculateCounterClkDiv(FTM_ADDRESS, config_array[0],
	FTM_CLOCK);
	FTM_Init(FTM_ADDRESS, &ftmInfo);
	red_duty = (config_array[2] / RED_MAX) * 100;
	green_duty = (config_array[3] / GREEN_MAX) * 100;
	blue_duty = (config_array[4] / BLUE_MAX) * 100;
	parameter[0].chnlNumber = (ftm_chnl_t) RED;
	parameter[0].level = kFTM_LowTrue;
	parameter[0].dutyCyclePercent = red_duty;
	parameter[0].firstEdgeDelayPercent = 0U;
	parameter[0].enableComplementary = false;
	parameter[0].enableDeadtime = false;

	parameter[1].chnlNumber = (ftm_chnl_t) GREEN;
	parameter[1].level = kFTM_LowTrue;
	parameter[1].dutyCyclePercent = green_duty;
	parameter[1].firstEdgeDelayPercent = 0U;
	parameter[1].enableComplementary = false;
	parameter[1].enableDeadtime = false;

	parameter[2].chnlNumber = (ftm_chnl_t) BLUE;
	parameter[2].level = kFTM_LowTrue;
	parameter[2].dutyCyclePercent = blue_duty;
	parameter[2].firstEdgeDelayPercent = 0U;
	parameter[2].enableComplementary = false;
	parameter[2].enableDeadtime = false;

	//FTM_SetupPwm(FTM_ADDRESS, parameter, 2, FTM_MODE, config_array[0], FTM_CLOCK);
	FTM_SetupPwm(FTM_ADDRESS, parameter, 3, FTM_MODE, config_array[0],
	FTM_CLOCK);
	//FTM_SetupPwm(FTM_ADDRESS, parameter, 3, FTM_MODE, config_array[0], FTM_CLOCK);
	FTM_StartTimer(FTM_ADDRESS, kFTM_SystemClock);

	// Read the commands
	cycle = config_array[13];
//	for (int j = 0; j < 14; j++) {
//		//PRINTF("IN pattern generation\n\r");
//		PRINTF("%d\r\n", config_array[j]);
//	}
	//command = comnts_read();
	//if (command == START_OR_STOP) {

	if (config_array[12] == 1) {
		do {

			if (cycle == 0) {
				cycle = 1;
			} else {
				cycle--;
			}
			// Up mode
			//PRINTF("1 IS WORKING \r\n");
			for (red_inc = config_array[2]; red_inc <= config_array[5];
					red_inc = red_inc + config_array[8]) {
//				PRINTF("%d,%d,%d\r\n", red_inc, green_inc, blue_inc);
				command = comnts_read();
				if (command == START_OR_STOP) {
					break;
				} else {
					while (command == PAUSE) {
						command = comnts_read();
						PRINTF("In while loop\n\r");
						if (command == PAUSE) {
							break;
						}
					}

					for (green_inc = config_array[3];
							green_inc <= config_array[6];
							green_inc = green_inc + config_array[9]) {
						command = comnts_read();
						if (command == START_OR_STOP) {
							break_flag = 1;
							break;
						} else {
							while (command == PAUSE) {
								command = comnts_read();
								if (command == PAUSE) {
									break;
								}
							}

							for (blue_inc = config_array[3];
									blue_inc <= config_array[7];
									blue_inc = blue_inc + config_array[10]) {
								command = comnts_read();
								if (command == START_OR_STOP) {
									break_flag = 1;
									break;
								} else {
									while (command == PAUSE) {
										command = comnts_read();
										if (command == PAUSE) {
											break_flag = 1;
											break;
										}
									}
									blue_duty = (blue_inc / 3.0) * 100;
									FTM_UpdatePwmDutycycle(FTM_ADDRESS,
											(ftm_chnl_t) BLUE, FTM_MODE,
											blue_duty);
									FTM_SetSoftwareTrigger(FTM_ADDRESS,
									true);
									colour_update(red_inc, green_inc, blue_inc);
//									PRINTF("%d,%d,%d \r\n", red_duty,
//											green_duty, blue_duty);
									Delay(config_array[11]);

								}
							}
							if (break_flag == 1) {
								break;
							}
							green_duty = (green_inc / 7.0) * 100;
							FTM_UpdatePwmDutycycle(FTM_ADDRESS,
									(ftm_chnl_t) GREEN, FTM_MODE, green_duty);
							FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
							//colour_update(red_inc, green_inc, blue_inc);
							//Delay(config_array[11]);

						}
						if (break_flag == 1) {
							break;
						}
						red_duty = (red_inc / 7.0) * 100;
						FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) RED,
						FTM_MODE, red_duty);
						FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
						//colour_update(red_inc, green_inc, blue_inc);
						//Delay(config_array[11]);
					}
				}
				FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) RED,
				FTM_MODE, ((config_array[5] / 7.0) * 100));
				FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) GREEN,
				FTM_MODE, ((config_array[6] / 7.0) * 100));
				FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) BLUE,
				FTM_MODE, ((config_array[7] / 3.0) * 100));
				FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
			}

		} while (cycle);
		//Rounding to the end colour
		//FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) RED, FTM_MODE,((config_array[5] / 7.0) * 100));
		//FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) GREEN, FTM_MODE,((config_array[6] / 7.0) * 100));
		//FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) BLUE, FTM_MODE,((config_array[7] / 3.0) * 100));
		//FTM_SetSoftwareTrigger(FTM_ADDRESS, true);

		if (config_array[12] == 2) {

			do {
				if (cycle == 0) {
					cycle = 1;
				} else
					cycle--;

				//Down mode
				PRINTF("IN DOWN MODE");
				for (red_dec = config_array[5]; red_dec >= config_array[2];
						red_dec = red_dec - config_array[8]) {
					command = comnts_read();
					if (command == START_OR_STOP) {
						break;
					} else {
						while (command == PAUSE) {
							command = comnts_read();
							if (command == PAUSE) {
								break;
							}
						}

						for (green_dec = config_array[6];
								green_dec >= config_array[3];
								green_dec = green_dec - config_array[9]) {

							command = comnts_read();
							if (command == START_OR_STOP) {
								break;
							} else {
								while (command == PAUSE) {
									command = comnts_read();
									if (command == PAUSE) {
										break;
									}
								}

								for (blue_dec = config_array[7];
										blue_dec >= config_array[4];
										blue_dec = blue_dec
												- config_array[10]) {
									PRINTF("%d, %d, %d\r\n", red_duty,
											green_duty, blue_duty);
									if (command == START_OR_STOP) {
										break_flag = 1;
										break;
									} else {
										while (command == PAUSE) {
											command = comnts_read();
											if (command == PAUSE) {
												break;
											}
										}
										blue_duty = (blue_dec / 3.0) * 100;
										FTM_UpdatePwmDutycycle(FTM_ADDRESS,
												(ftm_chnl_t) BLUE, FTM_MODE,
												blue_duty);
										FTM_SetSoftwareTrigger(FTM_ADDRESS,
										true);
										colour_update(red_dec, green_dec,
												blue_dec);
										Delay(config_array[11]);

									}
								}
								if (break_flag == 1) {
									break;
								}

								green_duty = (green_dec / 7.0) * 100;
								FTM_UpdatePwmDutycycle(FTM_ADDRESS,
										(ftm_chnl_t) GREEN, FTM_MODE,
										green_duty);
								FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
								//colour_update(red_dec, green_dec, blue_dec);
								//Delay(config_array[11]);
							}
						}
						if (break_flag == 1) {
							break;
						}
						red_duty = (red_dec / 7.0) * 100;
						FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) RED,
						FTM_MODE, red_duty);
						FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
						//colour_update(red_dec, green_dec, blue_dec);
						//Delay(config_array[11]);
					}
					FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) RED,
					FTM_MODE, ((config_array[5] / 7.0) * 100));
					FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) GREEN,
					FTM_MODE, ((config_array[6] / 7.0) * 100));
					FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) BLUE,
					FTM_MODE, ((config_array[7] / 3.0) * 100));
					FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
				}

			} while (cycle);
			//Rounding to end colour
			FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) RED, FTM_MODE,
					((config_array[5] / 7.0) * 100));
			FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) GREEN,
			FTM_MODE, ((config_array[6] / 7.0) * 100));
			FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) BLUE, FTM_MODE,
					((config_array[7] / 3.0) * 100));
			FTM_SetSoftwareTrigger(FTM_ADDRESS, true);

		}
		if (config_array[12] == 3) {
			do {
				if (config_array[13] == 0) {
					cycle = 1;
				} else {
					cycle--;
					//PRINTF("In mode3");
					//updown mode
					for (red_inc = config_array[2]; red_inc <= config_array[5];
							red_inc = red_inc + config_array[8]) {

						command = comnts_read();
						if (command == START_OR_STOP) {
							break;
						} else {
							while (command == PAUSE) {
								command = comnts_read();
								if (command == PAUSE) {
									break;
								}
							}
							for (green_inc = config_array[3];
									green_inc <= config_array[6];
									green_inc = green_inc + config_array[9]) {

								command = comnts_read();
								if (command == START_OR_STOP) {
									break_flag = 1;
									break;
								} else {
									while (command == PAUSE) {
										command = comnts_read();
										if (command == PAUSE) {
											break;
										}
									}
									for (blue_inc = config_array[4];
											blue_inc <= config_array[7];
											blue_inc = blue_inc
													+ config_array[10]) {
										PRINTF("%d, %d, %d\r\n", red_duty,
												green_duty, blue_duty);
										command = comnts_read();
										if (command == START_OR_STOP) {
											break;
										} else {
											command = comnts_read();
											if (command == PAUSE) {
												break;

											}
											blue_duty = (blue_inc / 3.0) * 100;
											FTM_UpdatePwmDutycycle(
											FTM_ADDRESS, (ftm_chnl_t) BLUE,
											FTM_MODE, blue_duty);
											FTM_SetSoftwareTrigger(
											FTM_ADDRESS, true);
											colour_update(red_inc, green_inc,
													blue_inc);
											Delay(config_array[11]);
										}
									}
									if (break_flag == 1) {
										break;
									}
									green_duty = (green_inc / 7.0) * 100;
									FTM_UpdatePwmDutycycle(FTM_ADDRESS,
											(ftm_chnl_t) GREEN, FTM_MODE,
											green_duty);
									FTM_SetSoftwareTrigger(FTM_ADDRESS,
									true);
									//colour_update(red_inc, green_inc, blue_inc);
									//Delay(config_array[11]);
								}
							}
							if (break_flag == 1) {
								break;
							}
							red_duty = (red_inc / 7.0) * 100;
							FTM_UpdatePwmDutycycle(FTM_ADDRESS,
									(ftm_chnl_t) RED, FTM_MODE, red_duty);
							FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
							//colour_update(red_inc, green_inc, blue_inc);
							//Delay(config_array[11]);
						}
						// Rounding to the end colour
						FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) RED,
						FTM_MODE, ((config_array[5] / 7.0) * 100));
						FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) GREEN,
						FTM_MODE, ((config_array[6] / 7.0) * 100));
						FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) BLUE,
						FTM_MODE, ((config_array[7] / 3.0) * 100));
						FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
						//PRINTF("UPMODE");
						Delay(config_array[11]);
						//Starting the up to down pattern genertion
						command = comnts_read();
						if (command == START_OR_STOP) {
							break;
						} else {
							while (command == PAUSE) {
								command = comnts_read();
								if (command == PAUSE) {
									break;
								}
							}
							for (red_dec = config_array[5];
									red_dec >= config_array[2];
									red_dec = red_dec - config_array[8]) {

								command = comnts_read();
								if (command == START_OR_STOP) {
									break;
								} else {
									while (command == PAUSE) {
										command = comnts_read();
										if (command == PAUSE) {
											break;
										}
									}
									for (green_dec = config_array[6];
											green_dec >= config_array[3];
											green_dec = green_dec
													- config_array[9]) {

										command = comnts_read();
										if (command == START_OR_STOP) {
											break_flag = 1;
											break;
										} else {
											while (command == PAUSE) {
												command = comnts_read();
												if (command == PAUSE) {
													break;
												}
												for (blue_dec = config_array[7];
														blue_dec
																>= config_array[4];
														blue_dec =
																blue_dec
																		- config_array[10]) {
													command = comnts_read();
													if (command == START_OR_STOP) {
														break_flag = 1;
														break;
													} else {
														while (command == PAUSE) {
															command =
																	comnts_read();
															if (command == PAUSE) {
																break;
															}
														}
														PRINTF("%d, %d, %d\r\n",
																red_duty,
																green_duty,
																blue_duty);
														blue_duty = (blue_dec
																/ 3.0) * 100;
														FTM_UpdatePwmDutycycle(
														FTM_ADDRESS,
																(ftm_chnl_t) BLUE,
																FTM_MODE,
																blue_duty);
														FTM_SetSoftwareTrigger(
														FTM_ADDRESS,
														true);
														colour_update(red_dec,
																green_dec,
																blue_dec);
														Delay(config_array[11]);
													}
												}
											}
											if (break_flag == 1) {
												break;
											}
											green_duty = (green_dec / 7.0)
													* 100;
											FTM_UpdatePwmDutycycle(
											FTM_ADDRESS, (ftm_chnl_t) GREEN,
											FTM_MODE, green_duty);
											FTM_SetSoftwareTrigger(
											FTM_ADDRESS, true);
											//colour_update(red_dec, green_dec,	blue_dec);
											//Delay(config_array[11]);
										}
									}
									if (break_flag == 1) {
										break;
									}
									red_duty = (red_dec / 7.0) * 100;
									FTM_UpdatePwmDutycycle(FTM_ADDRESS,
											(ftm_chnl_t) RED, FTM_MODE,
											red_duty);
									FTM_SetSoftwareTrigger(FTM_ADDRESS,
									true);
									//colour_update(red_inc, green_inc, blue_inc);
									//Delay(config_array[11]);
								}
							}
							// Rounding to the start colour
							FTM_UpdatePwmDutycycle(FTM_ADDRESS,
									(ftm_chnl_t) RED, FTM_MODE,
									((config_array[2] / 7.0) * 100));
							FTM_UpdatePwmDutycycle(FTM_ADDRESS,
									(ftm_chnl_t) GREEN, FTM_MODE,
									((config_array[3] / 7.0) * 100));
							FTM_UpdatePwmDutycycle(FTM_ADDRESS,
									(ftm_chnl_t) BLUE, FTM_MODE,
									((config_array[4] / 3.0) * 100));
							FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
							//PRINTF("IN down mode");
						}
					}
				}
			} while (cycle);
		}
	}

	//}
	return 0;
}
/***
 *@brief comnts_read
 *Function for Reading command in the queue and generate corresponding flags as return
 *
 *@param Nill
 *
 *@return FORWORD
 *@return PAUSE
 *@return STOP
 *
 *@note
 *  The different returns are from the different conditions in the in function
 *
 *Revision History

 18122022 NN :Creation Date

 */
//int comnts_read(void) {
//	static int fn_cnt = 0;
//	uint8_t comands[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//
//	if (fn_cnt == 10) {
//		comands[0] = 0;
//		comands[1] = 60;
//	}
//	fn_cnt++;
//	if (comands[1] == 60) {
//		return FORWORD;
//	} else if (comands[1] == 62) {
//		return BACKWORD;
//	} else if (comands[1] == 80) {
//		return PAUSE;
//	} else {
//		return FORWORD;
//	}
////return 0;
//}
/**
 * @brief manual_mode
 *
 *@param config_array
 *
 *@return 0
 *
 *@note
 *
 *Revision History:
 *
 *		20122022 NN : Creation Date
 *		09012023 NN : Bug fixing
 */
int manual_mode(int config_array[14]) {
	uint8_t word_flag = 0, direc;
	FTM_GetDefaultConfig(&ftmInfo);
	ftmInfo.prescale = FTM_CalculateCounterClkDiv(FTM_ADDRESS, config_array[0],
	FTM_CLOCK);
	FTM_Init(FTM_ADDRESS, &ftmInfo);
	red_duty = (config_array[2] / RED_MAX) * 100;
	green_duty = (config_array[3] / GREEN_MAX) * 100;
	blue_duty = (config_array[4] / BLUE_MAX) * 100;
	parameter[0].chnlNumber = (ftm_chnl_t) RED;
	parameter[0].level = kFTM_LowTrue;
	parameter[0].dutyCyclePercent = red_duty;
	parameter[0].firstEdgeDelayPercent = 0U;
	parameter[0].enableComplementary = false;
	parameter[0].enableDeadtime = false;

	parameter[1].chnlNumber = (ftm_chnl_t) GREEN;
	parameter[1].level = kFTM_LowTrue;
	parameter[1].dutyCyclePercent = green_duty;
	parameter[1].firstEdgeDelayPercent = 0U;
	parameter[1].enableComplementary = false;
	parameter[1].enableDeadtime = false;

	parameter[2].chnlNumber = (ftm_chnl_t) BLUE;
	parameter[2].level = kFTM_LowTrue;
	parameter[2].dutyCyclePercent = blue_duty;
	parameter[2].firstEdgeDelayPercent = 0U;
	parameter[2].enableComplementary = false;
	parameter[2].enableDeadtime = false;

//Setup FTM
	FTM_SetupPwm(FTM_ADDRESS, parameter, 3, FTM_MODE, config_array[0],
	FTM_CLOCK);
//FTM_Software toggle;
	FTM_StartTimer(FTM_ADDRESS, kFTM_SystemClock);

	red_duty = (red_inc / RED_MAX) * 100;
	blue_duty = (blue_inc / BLUE_MAX) * 100;
	green_duty = (green_inc / GREEN_MAX) * 100;
	FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) BLUE,
	FTM_MODE, blue_duty);
	FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) GREEN,
	FTM_MODE, green_duty);
	FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) RED,
	FTM_MODE, red_duty);
	FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
	for (int j = 0; j < 14; j++) {
		PRINTF("%d\r\n", config_array[j]);
	}

//PRINTF("%d, %d, %d", red_inc, green_inc, blue_inc);
//PRINTF("%d, %d, %d\r\n", red_duty, green_duty, blue_duty);
	while (config_array[12] == 4) {
		word_flag = comnts_read();
		for (red_inc = config_array[2]; red_inc <= config_array[5];
				red_inc = red_inc + (direc * config_array[8])) {

			for (green_inc = config_array[3]; green_inc <= config_array[6];
					green_inc = green_inc + (direc * config_array[9])) {

				for (blue_inc = config_array[4]; blue_inc <= config_array[7];
						blue_inc = blue_inc + (direc * config_array[10])) {
					PRINTF("%d, %d, %d\r\n", red_duty, green_duty, blue_duty);
					word_flag = comnts_read();
					//PRINTF("%d\r\n",word_flag);
					//if (break_flag == 1) {
					//break;
					if (word_flag == 2) {
						//PRINTF("\r\n in LOOP");
						PRINTF("%d, %d, %d\r\n", red_duty, green_duty,
								blue_duty);
						direc = 1;
						blue_duty = (blue_inc / BLUE_MAX) * 100;
						FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) BLUE,
						FTM_MODE, blue_duty);
						Delay(1000);
						FTM_SetSoftwareTrigger(FTM_ADDRESS,
						true);
						break_flag = 1;
						break;
					} else if (word_flag == 3) {
						direc = -1;

					}

				}
				/*if (break_flag == 1) {
				 break;
				 }*/

				if (word_flag == 2) {
					direc = 1;
				} else if (word_flag == 3) {
					direc = -1;
				}
				PRINTF("\r\nIN GREEN LOOP");
				//green_inc = green_inc + config_array[9];
				FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) GREEN,
				FTM_MODE, green_duty);
				FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
				break_flag = 1;
				break;
			}
			/*if (break_flag == 1) {
			 break;
			 }*/
			//red_inc = red_inc + config_array[8];
			if (word_flag == 2) {
				direc = 1;
			} else if (word_flag == 3) {
				direc = -1;
			}
			FTM_UpdatePwmDutycycle(FTM_ADDRESS, (ftm_chnl_t) RED,
			FTM_MODE, red_duty);
			FTM_SetSoftwareTrigger(FTM_ADDRESS, true);
			//break;
		}

	}
	return 0;
}
