#include "../UI/user_interface.h"
#include <stdio.h>
#include "fsl_debug_console.h"
#include "fsl_uart.h"

/* UART instance and clock */
#define UART            UART0
#define UART_CLKSRC     UART0_CLK_SRC
#define UART_CLK_FREQ   CLOCK_GetFreq(UART0_CLK_SRC)
#define UART_IRQn       UART0_RX_TX_IRQn
#define UART_IRQHandler UART0_RX_TX_IRQHandler

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t tx_buffer = 0;
uint8_t valid_data = 1;

void ui_homescreen(int led_refresh_rate, int start_colour[3], int end_colour[3],
		int colour_change_rate, int current_mode_index, int resolution[3]) {
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t  _____        _      ______ _______ _______ ______  \r\n");
	PRINTF("\t\t\t |  __ \\ /\\   | |    |  ____|__   __|__   __|  ____| \r\n");
	PRINTF("\t\t\t | |__) /  \\  | |    | |__     | |     | |  | |__    \r\n");
	PRINTF("\t\t\t |  ___/ /\\ \\ | |    |  __|    | |     | |  |  __|   \r\n");
	PRINTF("\t\t\t | |  / ____ \\| |____| |____   | |     | |  | |____  \r\n");
	PRINTF(
			"\t\t\t |_| /_/    \\_\\______|______|  |_|     |_|  |______| \tVersion 1.0\r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Device Mode\t:\tMaster \r\n");
	PRINTF("\t\t\t\t Slave Status\t:\tOnline \r\n");
	PRINTF("\t\t\t\t Process Status\t:\tRunning \r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Current Configurations:- \r\n");
	PRINTF("\t\t\t\t Refresh Rate\t\t:\t%d Hz \r\n", led_refresh_rate);
	PRINTF("\t\t\t\t Start Color Code\t:\t%d %d %d True Color \r\n",
			start_colour[0], start_colour[1], start_colour[2]);
	PRINTF("\t\t\t\t End Color Code\t\t:\t%d %d %d True Color \r\n",
			end_colour[0], end_colour[1], end_colour[2]);
	PRINTF("\t\t\t\t Color Change Rate\t:\t%d\r\n", colour_change_rate);

	switch (current_mode_index) {
	case 1:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP \r\n");
		break;
	case 2:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-DOWN \r\n");
		break;
	case 3:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP/DOWN \r\n");
		break;
	case 4:
		PRINTF("\t\t\t\t Mode\t\t\t:\tManual \r\n");
		break;
	default:
		PRINTF("\t\t\t\t Mode\t\t\t:\tInvalid \r\n");
		break;
	}
	PRINTF("\t\t\t\t Resolution\t\t:\t%d %d %d RGB\r\n", resolution[0],
			resolution[1], resolution[2]);
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Current RGB Code : x x x \r\n");
	PRINTF("\r\n");
	PRINTF("\r\n");

}

void ui_homescreen_slave() {

	int current_mode_index = 1;
	int colour_change_rate = 1;
	int led_refresh_rate = 1;
	int start_colour[3] = { 0, 0, 0 }, end_colour[3] = { 0, 0, 0 },
			resolution[3] = { 1, 1, 1 };

	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t  _____        _      ______ _______ _______ ______  \r\n");
	PRINTF("\t\t\t |  __ \\ /\\   | |    |  ____|__   __|__   __|  ____| \r\n");
	PRINTF("\t\t\t | |__) /  \\  | |    | |__     | |     | |  | |__    \r\n");
	PRINTF("\t\t\t |  ___/ /\\ \\ | |    |  __|    | |     | |  |  __|   \r\n");
	PRINTF("\t\t\t | |  / ____ \\| |____| |____   | |     | |  | |____  \r\n");
	PRINTF(
			"\t\t\t |_| /_/    \\_\\______|______|  |_|     |_|  |______| \tVersion 1.0\r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Device Mode\t:\tSlave \r\n");
	PRINTF("\t\t\t\t Master Status\t:\tOnline \r\n");
	PRINTF("\t\t\t\t Process Status\t:\tRunning \r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Current Configurations:- \r\n");
	PRINTF("\t\t\t\t Refresh Rate\t\t:\t%d Hz \r\n", led_refresh_rate);
	PRINTF("\t\t\t\t Start Color Code\t:\t%d %d %d True Color \r\n",
			start_colour[0], start_colour[1], start_colour[2]);
	PRINTF("\t\t\t\t End Color Code\t\t:\t%d %d %d True Color \r\n",
			end_colour[0], end_colour[1], end_colour[2]);
	PRINTF("\t\t\t\t Color Change Rate\t:\t%d\r\n", colour_change_rate);

	switch (current_mode_index) {
	case 1:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP \r\n");
		break;
	case 2:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-DOWN \r\n");
		break;
	case 3:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP/DOWN \r\n");
		break;
	case 4:
		PRINTF("\t\t\t\t Mode\t\t\t:\tManual \r\n");
		break;
	default:
		PRINTF("\t\t\t\t Mode\t\t\t:\tInvalid \r\n");
		break;
	}
	PRINTF("\t\t\t\t Resolution\t\t:\t%d %d %d RGB\r\n", resolution[0],
			resolution[1], resolution[2]);
	PRINTF("\r\n");
}

void ui_rgb_code_scheme(int current_rgb_scheme_index) {
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Palette       Version 1.0 \r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	PRINTF("\t Select color code Scheme \r\n");
	PRINTF("\r\n");
	/*PRINTF("\t1.\t332 RGB \r\n");
	 PRINTF("\t2.\t444 RGB \r\n");
	 PRINTF("\t3.\t888 RGB \r\n");
	 PRINTF("\t4.\tHome \r\n");
	 PRINTF("\r\n");
	 */

	switch (current_rgb_scheme_index) {
	case 1:
		PRINTF("\tCurrent color scheme - 332 RGB\r\n");
		PRINTF("\r\n");

		break;
	case 2:
		PRINTF("\tCurrent color scheme - 444 RGB\r\n");
		PRINTF("\r\n");

		break;
	case 3:
		PRINTF("\tCurrent color scheme - 888 RGB\r\n");
		PRINTF("\r\n");

		break;
	default:
		PRINTF("Data invalid\r\n");
		PRINTF("\r\n");

		break;
	}
	PRINTF("\r\n");

}

void ui_configure_colour_pattern(int led_refresh_rate, int start_colour[3],
		int end_colour[3], int colour_change_rate, int current_mode_index,
		int resolution[3]) {
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Palette       Version 1.0 \r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	PRINTF("\t Configure Color Pattern \r\n");
	PRINTF("\r\n");
	PRINTF("\r\n");
	PRINTF("\r\n");
	PRINTF("\r\n");
	PRINTF("\t1.\t\t\t\t\t\t:\t%d %d %d RGB \r\n", start_colour[0],
			start_colour[1], start_colour[2]);
	PRINTF("\t2.\t\t\t\t\t\t:\t%d %d %d RGB \r\n", end_colour[0], end_colour[1],
			end_colour[2]);
	PRINTF("\t3.\t\t\t\t\t\t:\t%d %d %d RGB \r\n", resolution[0], resolution[1],
			resolution[2]);
	PRINTF("\t4.\t\t\t\t\t\t:\t%d \r\n", colour_change_rate);
	PRINTF("\t5.\t\t\t\t\t\t:\t%d \r\n", led_refresh_rate);
	switch (current_mode_index) {
	case 1:
		PRINTF("\t\t\t\t\t\t\t:\tAuto-UP \r\n");
		break;
	case 2:
		PRINTF("\t\t\t\t\t\t\t:\tAuto-DOWN \r\n");
		break;
	case 3:
		PRINTF("\t\t\t\t\t\t\t:\tAuto-UP/DOWN \r\n");
		break;
	case 4:
		PRINTF("\t\t\t\t\t\t\t:\tManual \r\n");
		break;
	default:
		PRINTF("\t\t\t\t\t\t\t:\tInvalid \r\n");
		break;
	}
	PRINTF("\t\t\t\t\r\n");
}

void ui_modes(int current_mode_index) {

	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Palette       Version 1.0 \r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	switch (current_mode_index) {
	case 1:
		PRINTF("\tCurrent Mode - Auto: UP\r\n");
		break;
	case 2:
		PRINTF("\tCurrent Mode - Auto: DOWN\r\n");
		break;
	case 3:
		PRINTF("\tCurrent Mode - Auto: UP/DOWN\r\n");
		break;
	case 4:
		PRINTF("\tCurrent Mode - Manual\r\n");
		break;
	default:
		PRINTF("Mode invalid\r\n");
		break;
	}
	PRINTF("\r\n");
	PRINTF("\t Select Mode \r\n");

}

void ui_delay(int delay) {
	int j;
	for (int d = 0; d < delay; d++) {
		j = j + 1;
		j = j - 1;
	}
}

void master_ui(void) {
	int input_index;
	int current_mode_index = 1;
	int curent_rgb_scheme_index = 1;
	int colour_change_rate = 1;
	int led_refresh_rate = 1;
	int start_color[3] = { 0, 0, 0 }, end_color[3] = { 0, 0, 0 },
			resolution[3] = { 1, 1, 1 };
	int  *start_pointer;

	while (1) {
		ui_homescreen(led_refresh_rate, start_color, end_color,
				colour_change_rate, current_mode_index, resolution);
		while (1) {
			input_index = 0;

			char home_screen__menu[4][30] = { "Configure RGB LED",
					"Configure Color Pattern ", "Start/Stop ", "Pause/Resume " };
			input_index = arrow_key_navigate(home_screen__menu, 4, 26, 10);

			if ((input_index > 0 && input_index < 5)) {
				break;
			} else {
				PRINTF("\r\n\tInvalid Entry!\r\n\tTry again...");
				continue;
			}
		}

		if (input_index == 1) {
			while (1) {
				ui_rgb_code_scheme(curent_rgb_scheme_index);

				char colour_scheme_menu[4][30] = { "332 RGB", "444 RGB",
						"888 RGB", "Home" };
				input_index = arrow_key_navigate(colour_scheme_menu, 4, 9, 10);

				if (input_index == 1) {
					while (1) {
						PRINTF("\r\n\t332 scheme selected...");
						PRINTF("\r\n\tPlease wait...");
						curent_rgb_scheme_index = 1;
						//ui_delay(5000000);
						break;
					}
				} else if (input_index == 2) {
					while (1) {
						PRINTF("\r\n\t444 scheme unavailable!");
						PRINTF("\r\n\tPlease wait...");
						curent_rgb_scheme_index = 1;
						ui_delay(5000000);
						break;
					}
				} else if (input_index == 3) {
					while (1) {
						PRINTF("\r\n\t888 scheme unavailable!");
						PRINTF("\r\n\tPlease wait...");
						curent_rgb_scheme_index = 1;
						ui_delay(5000000);
						break;
					}

				} else if (input_index == 4) {
					PRINTF("\r\n\tLoading Home screen");
					PRINTF("\r\n\tPlease wait...");
					break;
				} else {
					PRINTF("\r\n\tInvalid data received");
				}
			}
		} else if (input_index == 2) {
			while (1) {
				while(1){
				if (input_index == 2){
				ui_configure_colour_pattern(led_refresh_rate, start_color,
						end_color, colour_change_rate, current_mode_index,
						resolution);

				char colour_scheme_menu[7][30] = { "Start color", "End color",
						"Color change resolution", "Color change rate",
						"LED refresh rate", "Mode", "Home", };
				input_index = arrow_key_navigate(colour_scheme_menu, 7, 8, 10);
				UART_DisableInterrupts(UART,
						kUART_RxDataRegFullInterruptEnable
								| kUART_RxOverrunInterruptEnable);
				if (input_index == 1) {

					start_pointer = start_colour_read();
					for (int i = 0; i<=3; i++){
						start_pointer[i] = start_color[i];
					}
				}
				}
				}
				} else if (input_index == 2) {
					while (1) {
						while (1) {
							while (1) {
								PRINTF(
										"\r\n\tEnter End color value for RED : ");
								while (!(kUART_RxDataRegFullFlag
										& UART_GetStatusFlags(UART0)))
									UART_ClearStatusFlags(UART0,
											kUART_RxDataRegFullFlag);
								end_color[0] = UART_ReadByte(UART0) - 48;
								UART_WriteByte(UART0, end_color[0] + 48);
								if (end_color[0] >= 0 && end_color[0] < 8) {
									break;
								} else {
									PRINTF(
											"\r\n\tInvalid Entry!\r\n\tTry again...");
									continue;
								}
							}

							while (1) {
								PRINTF(
										"\r\n\tEnter End color value for GREEN : ");
								while (!(kUART_RxDataRegFullFlag
										& UART_GetStatusFlags(UART0)))
									UART_ClearStatusFlags(UART0,
											kUART_RxDataRegFullFlag);
								end_color[1] = UART_ReadByte(UART0) - 48;
								UART_WriteByte(UART0, end_color[1] + 48);
								if (end_color[1] >= 0 && end_color[1] < 8) {
									break;
								} else {
									PRINTF(
											"\r\n\tInvalid Entry!\r\n\tTry again...");
									continue;
								}
							}

							while (1) {
								PRINTF(
										"\r\n\tEnter End color value for BLUE : ");
								while (!(kUART_RxDataRegFullFlag
										& UART_GetStatusFlags(UART0)))
									UART_ClearStatusFlags(UART0,
											kUART_RxDataRegFullFlag);
								end_color[2] = UART_ReadByte(UART0) - 48;
								UART_WriteByte(UART0, end_color[2] + 48);
								if (end_color[2] >= 0 && end_color[2] < 4) {
									UART_EnableInterrupts(UART,
											kUART_RxDataRegFullInterruptEnable
													| kUART_RxOverrunInterruptEnable);
									break;
								} else {
									PRINTF(
											"\r\n\tInvalid Entry!\r\n\tTry again...");
									continue;
								}
							}
							break;
						}

						break;
					}
				} else if (input_index == 3) {
					while (1) {
						while (1) {
							while (1) {
								PRINTF(
										"\r\n\tEnter Resolution value for RED : ");
								while (!(kUART_RxDataRegFullFlag
										& UART_GetStatusFlags(UART0)))
									UART_ClearStatusFlags(UART0,
											kUART_RxDataRegFullFlag);
								resolution[0] = UART_ReadByte(UART0) - 48;
								UART_WriteByte(UART0, resolution[0] + 48);
								if (resolution[0] >= 0 && resolution[0] < 8) {
									break;
								} else {
									PRINTF(
											"\r\n\tInvalid Entry!\r\n\tTry again...");
									continue;
								}
							}

							while (1) {
								PRINTF(
										"\r\n\tEnter Resolution value for GREEN : ");
								while (!(kUART_RxDataRegFullFlag
										& UART_GetStatusFlags(UART0)))
									UART_ClearStatusFlags(UART0,
											kUART_RxDataRegFullFlag);
								resolution[1] = UART_ReadByte(UART0) - 48;
								UART_WriteByte(UART0, resolution[1] + 48);
								if (resolution[1] >= 0 && resolution[1] < 8) {
									break;
								} else {
									PRINTF(
											"\r\n\tInvalid Entry!\r\n\tTry again...");
									continue;
								}
							}

							while (1) {
								PRINTF("\r\n\tEnter Resolution value for BLUE");
								while (!(kUART_RxDataRegFullFlag
										& UART_GetStatusFlags(UART0)))
									UART_ClearStatusFlags(UART0,
											kUART_RxDataRegFullFlag);
								resolution[2] = UART_ReadByte(UART0) - 48;
								UART_WriteByte(UART0, resolution[2] + 48);
								if (resolution[2] >= 0 && resolution[2] < 4) {
									UART_EnableInterrupts(UART,
											kUART_RxDataRegFullInterruptEnable
													| kUART_RxOverrunInterruptEnable);
									break;
								} else {
									PRINTF(
											"\r\n\tInvalid Entry!\r\n\tTry again...");
									continue;
								}
							}
							break;
						}
						break;
					}

				} else if (input_index == 4) {
					while (1) {
						colour_change_rate = colour_change_rate_read();
						if (colour_change_rate > 0
								&& colour_change_rate <= 500) {
							UART_EnableInterrupts(UART,
									kUART_RxDataRegFullInterruptEnable
											| kUART_RxOverrunInterruptEnable);
							break;
						} else {
							PRINTF("\r\n\tInvalid Entry!\r\n\tTry again...");
							continue;
						}
						break;
					}
				} else if (input_index == 5) {
					while (1) {

						led_refresh_rate = refresh_rate_read();
						if (led_refresh_rate > 0 && led_refresh_rate < 9999) {
							UART_EnableInterrupts(UART,
									kUART_RxDataRegFullInterruptEnable
											| kUART_RxOverrunInterruptEnable);
							break;
						} else {
							PRINTF("\r\n\tInvalid Entry!\r\n\tTry again...");
							continue;
						}
						break;
					}
				} else if (input_index == 6) {
					PRINTF("\r\n\tMode");
					PRINTF("\r\n\tPlease wait...");
					UART_EnableInterrupts(UART,
							kUART_RxDataRegFullInterruptEnable
									| kUART_RxOverrunInterruptEnable);
					//ui_delay(5000000);
					while (1) {
						ui_modes(current_mode_index);
						char mode_menu[5][30] = { "Auto UP", "Auto DOWN",
								"Auto UP/DOWN", "Manual", "Go Back" };
						input_index = arrow_key_navigate(mode_menu, 5, 8, 10);
						if (input_index == 1) {
							while (1) {
								PRINTF("\r\n\tAuto: UP mode selected.");
								PRINTF("\r\n\tPlease wait...");
								current_mode_index = 1;
								//ui_delay(5000000);
								break;
							}
						} else if (input_index == 2) {
							while (1) {
								PRINTF("\r\n\tAuto: DOWN mode selected.");
								PRINTF("\r\n\tPlease wait...");
								current_mode_index = 2;
								//ui_delay(5000000);
								break;
							}
						} else if (input_index == 3) {
							while (1) {
								PRINTF("\r\n\tAuto: UP/DOWN mode selected.");
								PRINTF("\r\n\tPlease wait...");
								current_mode_index = 3;
								//ui_delay(5000000);
								break;
							}

						} else if (input_index == 4) {
							while (1) {
								PRINTF("\r\n\tManual Mode selected");
								PRINTF("\r\n\tPlease wait...");
								current_mode_index = 4;
								//ui_delay(5000000);
								break;
							}
						} else if (input_index == 5) {
							PRINTF("\r\n\tGoing back.");
							PRINTF("\r\n\tPlease wait...");
							//ui_delay(5000000);
							break;
						} else {
							PRINTF("\r\n\tInvalid data received");
						}
					}
				} else if (input_index == 7) {
					PRINTF("\r\n\tLoading Home");
					PRINTF("\r\n\tPlease wait...");
					UART_EnableInterrupts(UART,
							kUART_RxDataRegFullInterruptEnable
									| kUART_RxOverrunInterruptEnable);
					break;
				} else {
					PRINTF("\r\n\tInvalid data received");
				}
			}

		} else if (input_index == 3) {
			start_stop(led_refresh_rate, start_color, end_color,
					colour_change_rate, current_mode_index, resolution);
		} else if (input_index == 4) {
			play_pause(led_refresh_rate, start_color, end_color,
					colour_change_rate, current_mode_index, resolution);
		} else {
			PRINTF("\r\n\tInvalid data received!");
			ui_delay(5000000);
		}

	}
}

void start_stop(int led_refresh_rate, int start_colour[3], int end_colour[3],
		int colour_change_rate, int current_mode_index, int resolution[3]) {
	while (1) {
		if (current_mode_index == 1) {
			if ((start_colour[0] < end_colour[0])
					&& (start_colour[1] < end_colour[1])
					&& (start_colour[2] < end_colour[2])) {
				PRINTF("\r\n\tSuccess");
				ui_delay(5000000);
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}
		} else if (current_mode_index == 2) {
			if ((start_colour[0] > end_colour[0])
					&& (start_colour[1] > end_colour[1])
					&& (start_colour[2] > end_colour[2])) {
				PRINTF("\r\n\tSuccess");
				ui_delay(5000000);
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}

		} else if (current_mode_index == 3) {
			if ((start_colour[0] < end_colour[0])
					&& (start_colour[1] < end_colour[1])
					&& (start_colour[2] < end_colour[2])) {
				PRINTF("\r\n\tSuccess");
				ui_delay(5000000);
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}

		} else if (current_mode_index == 4) {
			PRINTF("\r\n\tSuccess");
		} else {
			PRINTF("\r\n\tInvalid Data");
		}
	}
}

void play_pause(int led_refresh_rate, int start_colour[3], int end_colour[3],
		int colour_change_rate, int current_mode_index, int resolution[3]) {
	while (1) {
		if (current_mode_index == 1) {
			if ((start_colour[0] < end_colour[0])
					&& (start_colour[1] < end_colour[1])
					&& (start_colour[2] < end_colour[2])) {
				PRINTF("\r\n\tSuccess");
				ui_delay(5000000);
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}
		} else if (current_mode_index == 2) {
			if ((start_colour[0] > end_colour[0])
					&& (start_colour[1] > end_colour[1])
					&& (start_colour[2] > end_colour[2])) {
				PRINTF("\r\n\tSuccess");
				ui_delay(5000000);
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}

		} else if (current_mode_index == 3) {
			if ((start_colour[0] < end_colour[0])
					&& (start_colour[1] < end_colour[1])
					&& (start_colour[2] < end_colour[2])) {
				PRINTF("\r\n\tSuccess");
				ui_delay(5000000);
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}
		} else if (current_mode_index == 4) {
			PRINTF("\r\n\tSuccess");
		} else {
			PRINTF("\r\n\tInvalid Data");
		}
	}
}

void slave_ui() {
	while (1) {
		ui_homescreen_slave();
		while (1)
			;
	}

}

int arrow_key_navigate(char prompt[][30], int num_of_ops, int x_cor, int y_cor) {
	int run_flag = 1;
	int *pointer = malloc(num_of_ops * sizeof(int));
	int ret = 0;
	memset(pointer, 0, num_of_ops * sizeof(int));
	pointer[0] = 1;
	while (run_flag) {
		PRINTF("\e[?25l");
		PRINTF("\033[%d;%dHPress Enter to Select", x_cor, y_cor);
		PRINTF("\033[%d;%dHArrow Keys to move cursor\r\n\n", x_cor + 1, y_cor);
		for (int i = 0; i < num_of_ops; i++) {
			if (pointer[i] == 1) {
				PRINTF("        ");
			} else {
				PRINTF("");
			}
			PRINTF("        %s", prompt[i]);
			if (pointer[i] == 1) {
				PRINTF("\t<==\r\n");
			} else {
				PRINTF("                     \r\n");
			}
		}
		while (1) {
			if (valid_data == 1) {
				break;
			}
		}
		//PRINTF("%d", tx_buffer);
		if (tx_buffer == 66) {
			//PRINTF("Down Arrow\r\n");
			int temp;
			temp = pointer[num_of_ops - 1];
			for (int j = num_of_ops - 1; j != 0; j--) {
				pointer[j] = pointer[j - 1];

			}
			pointer[0] = temp;
		} else if (tx_buffer == 65) {
			//PRINTF("Up Arrow\r\n");
			int temp;
			temp = pointer[0];
			for (int j = 0; j != num_of_ops - 1; j++) {
				pointer[j] = pointer[j + 1];

			}
			pointer[num_of_ops - 1] = temp;
		} else if (tx_buffer == 13) {
			//PRINTF("Enter\r\n");
			for (int j = 0; j < num_of_ops; j++) {
				if (pointer[j] == 1) {
					ret = j;
					run_flag = 0;
					break;
				}
			}
		}
		valid_data = 0;
	}
	return ret + 1;
}

int colour_change_rate_read() {
	int colour_change_rate[3];
	int return_val;

	while (1) {
		PRINTF("\n\r\tEdit Values :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_");
		PRINTF("\033[19;55H_");
		PRINTF("\033[19;60H_");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			colour_change_rate[0] = UART_ReadByte(UART0) - 48;
			if ((colour_change_rate[0] >= 0) && (colour_change_rate[0] < 10)) {
				PRINTF("\033[19;50H%d", colour_change_rate[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			colour_change_rate[1] = UART_ReadByte(UART0) - 48;
			if ((colour_change_rate[1] >= 0) && (colour_change_rate[1] < 10)) {
				PRINTF("\033[19;55H%d", colour_change_rate[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			colour_change_rate[2] = UART_ReadByte(UART0) - 48;
			if ((colour_change_rate[2] >= 0) && (colour_change_rate[2] < 10)) {
				PRINTF("\033[19;60H%d", colour_change_rate[2]);
				break;
			} else {
				continue;
			}
		}
		return_val = ((colour_change_rate[0] * 100)
				+ (colour_change_rate[1] * 10) + (colour_change_rate[2]));
		ui_delay(1000000);

		if (return_val <= 500) {
			break;
		} else {
			PRINTF("\n\r\tInvalid Value!\n\r\tTry again...");
			ui_delay(500000);
			continue;
		}

	}
	return return_val;
}

int refresh_rate_read() {
	int refresh_rate[4];
	int return_val;

	while (1) {

		PRINTF("\n\r\tEdit Values :");
		PRINTF("\033[19;50H                                                 ");
		PRINTF("\033[19;50H_");
		PRINTF("\033[19;55H_");
		PRINTF("\033[19;60H_");
		PRINTF("\033[19;65H_");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			refresh_rate[0] = UART_ReadByte(UART0) - 48;
			if ((refresh_rate[0] >= 0) && (refresh_rate[0] < 10)) {
				PRINTF("\033[19;50H%d", refresh_rate[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			refresh_rate[1] = UART_ReadByte(UART0) - 48;
			if ((refresh_rate[1] >= 0) && (refresh_rate[1] < 10)) {
				PRINTF("\033[19;55H%d", refresh_rate[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			refresh_rate[2] = UART_ReadByte(UART0) - 48;
			if ((refresh_rate[2] >= 0) && (refresh_rate[2] < 10)) {
				PRINTF("\033[19;60H%d", refresh_rate[2]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			refresh_rate[3] = UART_ReadByte(UART0) - 48;
			if ((refresh_rate[3] >= 0) && (refresh_rate[3] < 10)) {
				PRINTF("\033[19;65H%d", refresh_rate[3]);
				break;
			} else {
				continue;
			}
		}
		return_val = ((refresh_rate[0] * 1000) + (refresh_rate[1] * 100)
				+ ((refresh_rate[2]) * 10) + refresh_rate[3]);
		ui_delay(1000000);

		if (return_val <= 9999) {
			break;
		} else {
			PRINTF("\n\r\tInvalid Value!\n\r\tTry again...");
			ui_delay(500000);
			continue;
		}

	}
	return return_val;
}

int *start_colour_read() {
	static int start_colour_read[3];

	while (1) {
		PRINTF("\n\r\tEdit Values :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_ R");
		PRINTF("\033[19;55H_ G");
		PRINTF("\033[19;60H_ B");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			start_colour_read[0] = UART_ReadByte(UART0) - 48;
			if ((start_colour_read[0] >= 0) && (start_colour_read[0] <= 7)) {
				PRINTF("\033[19;50H%d", start_colour_read[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			start_colour_read[1] = UART_ReadByte(UART0) - 48;
			if ((start_colour_read[1] >= 0) && (start_colour_read[1] <= 7)) {
				PRINTF("\033[19;55H%d", start_colour_read[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			start_colour_read[2] = UART_ReadByte(UART0) - 48;
			if ((start_colour_read[2] >= 0) && (start_colour_read[2] <= 3)) {
				PRINTF("\033[19;60H%d", start_colour_read[2]);
				break;
			} else {
				continue;
			}
		}
		ui_delay(1000000);


	}
	return start_colour_read;
}


void UART_IRQHandler(void) {
	if (UART_GetStatusFlags(UART)) {
		/* If new data arrived. */
		tx_buffer = UART_ReadByte(UART);
		valid_data = 1;
		//UART_WriteByte(UART,data);
	}
	SDK_ISR_EXIT_BARRIER;
}
