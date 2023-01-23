/**
 * @file
 * @brief
 *
 *
 *
 * @note
 *
 * Revision History:
 * 	-060123 MSG : Creation Date
 */

/*System includes.*/
#include <stdio.h>
#include "fsl_debug_console.h"
#include "fsl_uart.h"

#include "../UI/user_interface.h"

/* UART instance and clock */
#define UART            UART0
#define UART_CLKSRC     UART0_CLK_SRC
#define UART_CLK_FREQ   CLOCK_GetFreq(UART0_CLK_SRC)
#define UART_IRQn       UART0_RX_TX_IRQn
#define UART_IRQHandler UART0_RX_TX_IRQHandler

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
/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t tx_buffer = 0;
uint8_t valid_data = 1;

void boot_screen(void) {
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\e[?25l");
	PRINTF("\033[1m");
	PRINTF("\033[37m");
	PRINTF("\033[40m");
	PRINTF(
			"\n\r                                                                      ");
	PRINTF(
			"\n\r                                                                      ");
	PRINTF(
			"\n\r                                                         \033[35m.:\033[37m           ");
	PRINTF(
			"\n\r                                                        \033[35m:%%+\033[37m           ");
	PRINTF(
			"\n\r                          .:-==++++==-:.               \033[35m=@#\033[37m            ");
	PRINTF(
			"\n\r                      :+#%%@@%%##***##%%@@@@#*=-.        \033[35m+@%%\033[37m            _____      _      _   _       ");
	PRINTF(
			"\n\r                    =%%@%%*=:           .:-+*%%@@%%+-    \033[35m*@%%.\033[37m           |  __ \\    | |    | | | |      ");
	PRINTF(
			"\n\r                  =%%@%%=                     .-+%%@@-\033[35m.#@@-\033[37m            | |__) |_ _| | ___| |_| |_ ___ ");
	PRINTF(
			"\n\r                .#@%%=     \033[31m.*%%@%%+.\033[37m    \033[33m.*%%@%%+.\033[37m    :-:\033[35m%%@@*\033[37m             |  ___/ _` | |/ _ \\ __| __/ _ \\");
	PRINTF(
			"\n\r               :%%@#.      \033[31m%%@@@@@*\033[37m    \033[33m#@@@@@*\033[37m     -\033[35m%%@@#:\033[37m%%=           | |  | (_| | |  __/ |_| ||  __/");
	PRINTF(
			"\n\r              -%%@+        \033[31m=%%@@@%%-\033[37m    \033[33m=%%@@@%%-\033[37m    \033[35m+@@@%%.\033[37m:%%@%%-         |_|   \\__,_|_|\\___|\\__|\\__\\___|");
	PRINTF(
			"\n\r             -@@+           \033[31m:-:\033[37m        \033[33m:-:\033[37m     \033[35m*@@@@:\033[37m   *@@=   ");
	PRINTF(
			"\n\r            :%%@*      .                      \033[35m.#@@@@=\033[37m     *@@:");
	PRINTF(
			"\n\r           .%%@#     \033[32m+%%@@%%=\033[37m                  \033[35m:%%@@@@*\033[37m       %%@*         \tMulticolor LED Controller");
	PRINTF(
			"\n\r           #@%%.    \033[32m=@@@@@@:\033[37m                \033[35m-%%@@@@#\033[37m        #@%%         \tVersion 2.0");
	PRINTF(
			"\n\r          =@@-      \033[32m*@@@%%+\033[37m                \033[35m+@@@@@%%.\033[37m        %%@#         ");
	PRINTF(
			"\n\r         .%%@#        \033[32m.::\033[37m          .::::. \033[35m*@@@@@@-\033[37m        *@@:         ");
	PRINTF(
			"\n\r         =@@:                  =#%%@@@@@-\033[35m+@@@@@@+\033[37m       :#@%%-          ");
	PRINTF(
			"\n\r         #@%%     \033[34m.-=-.\033[37m       :%%@%%+:.   \033[35m.@@@@@@*\033[37m:+====*%%@%%+.           ");
	PRINTF(
			"\n\r         #@%%    \033[34m=@@@@@+\033[37m     .%%@#.      \033[35m=@@@@@*\033[37m *##%%##*=:              ");
	PRINTF(
			"\n\r         *@@.   \033[34m*@@@@@#\033[37m     #@%%.       \033[35m*@@@%%=\033[37m                         ");
	PRINTF(
			"\n\r         .%%@*    \033[34m+#%%#+\033[37m     -@@+       \033[31m::-=+:\033[37m                          ");
	PRINTF(
			"\n\r          -%%@*.            #@%%      \033[31m+@@@@*\033[37m                            ");
	PRINTF(
			"\n\r           .#@%%+.         *@%%:     \033[32m-@@@@@@:\033[37m                           from");
	PRINTF(
			"\n\r             -#@@*=::.:-+%%@#:     \033[32m:%%@@@@@+\033[37m                            Digital Core Technologies");
	PRINTF(
			"\n\r               .=#%%@@@@@%%*-      \033[34m+@@@@@%%=\033[37m                             ");
	PRINTF(
			"\n\r                    ...        \033[34m-%%@@%%#+:\033[37m                               ");
	PRINTF(
			"\n\r                                                                      ");
	PRINTF("\033[0m");
	PRINTF("\n\r\033[5m\tPress Space to continue...\033[0m");
	PRINTF("\033[37m\n");

	while (1) {
		int uart_read;
		UART_DisableInterrupts(UART,
				kUART_RxDataRegFullInterruptEnable
						| kUART_RxOverrunInterruptEnable);
		while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
			UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
		uart_read = UART_ReadByte(UART0);

		if (uart_read == 32) {
			UART_EnableInterrupts(UART,
					kUART_RxDataRegFullInterruptEnable
							| kUART_RxOverrunInterruptEnable);
			break;
		} else {
			continue;
		}
	}

}

void ui_homescreen(int *ui_current_values) {
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t  _____        _      ______ _______ _______ ______  \r\n");
	PRINTF("\t\t\t |  __ \\ /\\   | |    |  ____|__   __|__   __|  ____| \r\n");
	PRINTF("\t\t\t | |__) /  \\  | |    | |__     | |     | |  | |__    \r\n");
	PRINTF("\t\t\t |  ___/ /\\ \\ | |    |  __|    | |     | |  |  __|   \r\n");
	PRINTF("\t\t\t | |  / ____ \\| |____| |____   | |     | |  | |____  \r\n");
	PRINTF(
			"\t\t\t |_| /_/    \\_\\______|______|  |_|     |_|  |______| \tVersion 2.0\r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Device Mode\t:\tMaster \r\n");
	switch (ui_current_values[COMPANION_STATUS]) {
	case kStatus_Success:
		PRINTF("\t\t\t\t Slave Status\t:\tConnected\r\n");
		break;
	default:
		PRINTF("\t\t\t\t Slave Status\t:\tDisconnected with error %d\r\n",
				ui_current_values[COMPANION_STATUS]);
		break;
	}
	switch (ui_current_values[PROCESS_STATUS]) {
	case 0:
		PRINTF("\t\t\t\t Process Status\t:\tStopped \r\n");
		break;
	case 1:
		PRINTF("\t\t\t\t Process Status\t:\tRunning \r\n");
		break;
	case 2:
		PRINTF("\t\t\t\t Process Status\t:\tPaused \r\n");
		break;
	default:
		PRINTF("\t\t\t\t Process Status\t:\tInvalid \r\n");
		break;
	}
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Current Configurations:- \r\n");
	PRINTF("\t\t\t\t Refresh Rate\t\t:\t%d Hz \r\n",
			ui_current_values[REFRESH_RATE]);
	PRINTF("\t\t\t\t Start Color Code\t:\t%d %d %d True Color \r\n",
			ui_current_values[RED_START_VALUE],
			ui_current_values[GREEN_START_VALUE],
			ui_current_values[BLUE_START_VALUE]);
	PRINTF("\t\t\t\t End Color Code\t\t:\t%d %d %d True Color \r\n",
			ui_current_values[RED_END_VALUE],
			ui_current_values[GREEN_END_VALUE],
			ui_current_values[BLUE_END_VALUE]);
	PRINTF("\t\t\t\t Color Change Rate\t:\t%d\r\n",
			ui_current_values[CHANGE_RATE]);

	switch (ui_current_values[MODE]) {
	case 1:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP \r\n");
		break;
	case 2:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-DOWN \r\n");
		break;
	case 3:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP/DOWN | Count : %d \r\n",
				ui_current_values[CYCLES]);
		break;
	case 4:
		PRINTF("\t\t\t\t Mode\t\t\t:\tManual \r\n");
		break;
	default:
		PRINTF("\t\t\t\t Mode\t\t\t:\tInvalid \r\n");
		break;
	}
	PRINTF("\t\t\t\t Resolution\t\t:\t%d %d %d RGB\r\n",
			ui_current_values[RED_RESOLUTION_VALUE],
			ui_current_values[GREEN_RESOLUTION_VALUE],
			ui_current_values[BLUE_RESOLUTION_VALUE]);
	PRINTF("\r\n");
	PRINTF(
			"\t\t\t\t Current RGB Code :   \033[31m%d \033[32m%d \033[34m%d \033[37m\r\n \033[0m",
			ui_current_values[CURRENT_RED_VALUE],
			ui_current_values[CURRENT_GREEN_VALUE],
			ui_current_values[CURRENT_BLUE_VALUE]);
	PRINTF("\r\n");
	PRINTF("\r\n");

}

void ui_homescreen_slave(int *ui_current_values) {
	PRINTF("\e[1;1H\e[2J");
		PRINTF("\r\n");
		PRINTF("\t\t\t  _____        _      ______ _______ _______ ______  \r\n");
		PRINTF("\t\t\t |  __ \\ /\\   | |    |  ____|__   __|__   __|  ____| \r\n");
		PRINTF("\t\t\t | |__) /  \\  | |    | |__     | |     | |  | |__    \r\n");
		PRINTF("\t\t\t |  ___/ /\\ \\ | |    |  __|    | |     | |  |  __|   \r\n");
		PRINTF("\t\t\t | |  / ____ \\| |____| |____   | |     | |  | |____  \r\n");
		PRINTF(
				"\t\t\t |_| /_/    \\_\\______|______|  |_|     |_|  |______| \tVersion 2.0\r\n");
		PRINTF("\r\n");
		PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
		PRINTF("\t\t\t\t    ******************* \r\n");
		PRINTF("\r\n");
		PRINTF("\t\t\t\t Device Mode\t:\tSlave \r\n");
		switch (ui_current_values[COMPANION_STATUS]) {
		case kStatus_Success:
			PRINTF("\t\t\t\t Slave Status\t:\tConnected\r\n");
			break;
		default:
			PRINTF("\t\t\t\t Slave Status\t:\tDisconnected with error %d\r\n",
					ui_current_values[COMPANION_STATUS]);
			break;
		}
		switch (ui_current_values[PROCESS_STATUS]) {
		case 0:
			PRINTF("\t\t\t\t Process Status\t:\tStopped \r\n");
			break;
		case 1:
			PRINTF("\t\t\t\t Process Status\t:\tRunning \r\n");
			break;
		case 2:
			PRINTF("\t\t\t\t Process Status\t:\tPaused \r\n");
			break;
		default:
			PRINTF("\t\t\t\t Process Status\t:\tInvalid \r\n");
			break;
		}
		PRINTF("\r\n");
		PRINTF("\t\t\t\t Current Configurations:- \r\n");
		PRINTF("\t\t\t\t Refresh Rate\t\t:\t%d Hz \r\n",
				ui_current_values[REFRESH_RATE]);
		PRINTF("\t\t\t\t Start Color Code\t:\t%d %d %d True Color \r\n",
				ui_current_values[RED_START_VALUE],
				ui_current_values[GREEN_START_VALUE],
				ui_current_values[BLUE_START_VALUE]);
		PRINTF("\t\t\t\t End Color Code\t\t:\t%d %d %d True Color \r\n",
				ui_current_values[RED_END_VALUE],
				ui_current_values[GREEN_END_VALUE],
				ui_current_values[BLUE_END_VALUE]);
		PRINTF("\t\t\t\t Color Change Rate\t:\t%d\r\n",
				ui_current_values[CHANGE_RATE]);

		switch (ui_current_values[MODE]) {
		case 1:
			PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP \r\n");
			break;
		case 2:
			PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-DOWN \r\n");
			break;
		case 3:
			PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP/DOWN | Count : %d \r\n",
					ui_current_values[CYCLES]);
			break;
		case 4:
			PRINTF("\t\t\t\t Mode\t\t\t:\tManual \r\n");
			break;
		default:
			PRINTF("\t\t\t\t Mode\t\t\t:\tInvalid \r\n");
			break;
		}
		PRINTF("\t\t\t\t Resolution\t\t:\t%d %d %d RGB\r\n",
				ui_current_values[RED_RESOLUTION_VALUE],
				ui_current_values[GREEN_RESOLUTION_VALUE],
				ui_current_values[BLUE_RESOLUTION_VALUE]);
		PRINTF("\r\n");
		PRINTF(
				"\t\t\t\t Current RGB Code :   \033[31m%d \033[32m%d \033[34m%d \033[37m\r\n \033[0m",
				ui_current_values[CURRENT_RED_VALUE],
				ui_current_values[CURRENT_GREEN_VALUE],
				ui_current_values[CURRENT_BLUE_VALUE]);
		PRINTF("\r\n");
		PRINTF("\r\n");

}

void ui_rgb_code_scheme(int current_rgb_scheme_index) {
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Palette       Version 2.0 \r\n");
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

void ui_configure_color_pattern(int *ui_current_values) {
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Palette       Version 2.0 \r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	PRINTF("\t Configure Color Pattern \r\n");
	PRINTF("\r\n");
	PRINTF("\r\n");
	PRINTF("\r\n");
	PRINTF("\r\n");
	PRINTF("\t1.\t\t\t\t\t\t:\t%d %d %d RGB \r\n",
			ui_current_values[RED_START_VALUE],
			ui_current_values[GREEN_START_VALUE],
			ui_current_values[BLUE_START_VALUE]);
	PRINTF("\t2.\t\t\t\t\t\t:\t%d %d %d RGB \r\n",
			ui_current_values[RED_END_VALUE],
			ui_current_values[GREEN_END_VALUE],
			ui_current_values[BLUE_END_VALUE]);
	PRINTF("\t3.\t\t\t\t\t\t:\t%d %d %d RGB \r\n",
			ui_current_values[RED_RESOLUTION_VALUE],
			ui_current_values[GREEN_RESOLUTION_VALUE],
			ui_current_values[BLUE_RESOLUTION_VALUE]);
	PRINTF("\t4.\t\t\t\t\t\t:\t%d \r\n", ui_current_values[CHANGE_RATE]);
	PRINTF("\t5.\t\t\t\t\t\t:\t%d \r\n", ui_current_values[REFRESH_RATE]);
	switch (ui_current_values[MODE]) {
	case 1:
		PRINTF("\t\t\t\t\t\t\t:\tAuto-UP \r\n");
		break;
	case 2:
		PRINTF("\t\t\t\t\t\t\t:\tAuto-DOWN \r\n");
		break;
	case 3:
		PRINTF("\t\t\t\t\t\t\t:\tAuto-UP/DOWN | Count : %d\r\n",
				ui_current_values[CYCLES]);
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

void ui_modes(int current_mode_index, int up_down_count) {

	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Palette       Version 2.0 \r\n");
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
		PRINTF("\tCurrent Mode - Auto: UP/DOWN | Count : %d\r\n",
				up_down_count);
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

void master_ui(int *ui_current_values) {
	int input_index;
	while (1) {
		ui_homescreen(ui_current_values);
		while (1) {
			input_index = 0;

			char home_screen__menu[3][30] = { "Configure RGB LED",
					"Configure Color Pattern ", "Start" };
			input_index = arrow_key_navigate(home_screen__menu, 3, 26, 10);

			if ((input_index > 0 && input_index < 4)) {
				break;
			} else {
				PRINTF("\r\n\tInvalid Entry!\r\n\tTry again...");
				continue;
			}
		}

		if (input_index == 1) {
			while (1) {
				ui_rgb_code_scheme(ui_current_values[RGB_SCHEME]);

				char color_scheme_menu[4][30] = { "332 RGB", "444 RGB",
						"888 RGB", "Home" };
				input_index = arrow_key_navigate(color_scheme_menu, 4, 9, 10);

				if (input_index == 1) {
					while (1) {
						PRINTF("\r\n\t332 scheme selected...");
						PRINTF("\r\n\tPlease wait...");
						ui_current_values[RGB_SCHEME] = 1;
						//ui_delay(5000000);
						break;
					}
				} else if (input_index == 2) {
					while (1) {
						PRINTF("\r\n\t444 scheme unavailable!");
						PRINTF("\r\n\tPlease wait...");
						ui_current_values[RGB_SCHEME] = 1;
						ui_delay(5000000);
						break;
					}
				} else if (input_index == 3) {
					while (1) {
						PRINTF("\r\n\t888 scheme unavailable!");
						PRINTF("\r\n\tPlease wait...");
						ui_current_values[RGB_SCHEME] = 1;
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
				ui_configure_color_pattern(ui_current_values);

				char color_scheme_menu[7][30] = { "Start color", "End color",
						"Color change resolution", "Color change rate",
						"LED refresh rate", "Mode", "Home", };
				input_index = arrow_key_navigate(color_scheme_menu, 7, 8, 10);
				UART_DisableInterrupts(UART,
						kUART_RxDataRegFullInterruptEnable
								| kUART_RxOverrunInterruptEnable);
				if (input_index == 1) {
					while (1) {
						start_color_read(&ui_current_values[RED_START_VALUE]);
						UART_EnableInterrupts(UART,
								kUART_RxDataRegFullInterruptEnable
										| kUART_RxOverrunInterruptEnable);
						break;
					}
				} else if (input_index == 2) {
					while (1) {
						end_color_read(&ui_current_values[RED_END_VALUE]);
						UART_EnableInterrupts(UART,
								kUART_RxDataRegFullInterruptEnable
										| kUART_RxOverrunInterruptEnable);
						break;
					}
				} else if (input_index == 3) {
					while (1) {
						resolution_read(
								&ui_current_values[RED_RESOLUTION_VALUE]);
						UART_EnableInterrupts(UART,
								kUART_RxDataRegFullInterruptEnable
										| kUART_RxOverrunInterruptEnable);
						break;
					}
				} else if (input_index == 4) {
					while (1) {
						ui_current_values[CHANGE_RATE] =
								color_change_rate_read();
						if (ui_current_values[CHANGE_RATE] > 0
								&& ui_current_values[CHANGE_RATE] <= 500) {
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

						ui_current_values[REFRESH_RATE] = refresh_rate_read();
						if (ui_current_values[REFRESH_RATE] > 0
								&& ui_current_values[REFRESH_RATE] < 9999) {
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
						ui_modes(ui_current_values[MODE],
								ui_current_values[CYCLES]);
						char mode_menu[5][30] = { "Auto UP", "Auto DOWN",
								"Auto UP/DOWN", "Manual", "Go Back" };
						input_index = arrow_key_navigate(mode_menu, 5, 8, 10);
						if (input_index == 1) {
							while (1) {
								PRINTF("\r\n\tAuto: UP mode selected.");
								PRINTF("\r\n\tPlease wait...");
								ui_current_values[MODE] = 1;
								//ui_delay(5000000);
								break;
							}
						} else if (input_index == 2) {
							while (1) {
								PRINTF("\r\n\tAuto: DOWN mode selected.");
								PRINTF("\r\n\tPlease wait...");
								ui_current_values[MODE] = 2;
								//ui_delay(5000000);
								break;
							}
						} else if (input_index == 3) {
							while (1) {
								PRINTF("\r\n\tAuto: UP/DOWN mode selected.");
								UART_DisableInterrupts(UART,
										kUART_RxDataRegFullInterruptEnable
												| kUART_RxOverrunInterruptEnable);
								ui_current_values[CYCLES] =
										up_down_count_read();
								ui_delay(1000000);
								UART_EnableInterrupts(UART,
										kUART_RxDataRegFullInterruptEnable
												| kUART_RxOverrunInterruptEnable);
								ui_current_values[MODE] = 3;
								//ui_delay(5000000);
								break;
							}

						} else if (input_index == 4) {
							while (1) {
								PRINTF("\r\n\tManual Mode selected");
								PRINTF("\r\n\tPlease wait...");
								ui_current_values[MODE] = 4;
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

					int status_check = 0;
					int uart_read;

					status_check = validation_warning(ui_current_values);

					if (status_check == 1) {
						while (1) {
							UART_DisableInterrupts(UART,
									kUART_RxDataRegFullInterruptEnable
											| kUART_RxOverrunInterruptEnable);
							while (!(kUART_RxDataRegFullFlag
									& UART_GetStatusFlags(UART0)))
								UART_ClearStatusFlags(UART0,
										kUART_RxDataRegFullFlag);
							uart_read = UART_ReadByte(UART0);

							if (uart_read == 13 || uart_read == 32) {
								break;
							} else {
								continue;
							}
						}
						if (uart_read == 13) {
							UART_EnableInterrupts(UART,
									kUART_RxDataRegFullInterruptEnable
											| kUART_RxOverrunInterruptEnable);
							break;
						} else if (uart_read == 32) {
							UART_EnableInterrupts(UART,
									kUART_RxDataRegFullInterruptEnable
											| kUART_RxOverrunInterruptEnable);
							continue;
						}
					} else {
						UART_EnableInterrupts(UART,
								kUART_RxDataRegFullInterruptEnable
										| kUART_RxOverrunInterruptEnable);
						break;
					}

				} else {
					PRINTF("\r\n\tInvalid data received");
				}
			}

		} else if (input_index == 3) {
			start_stop(ui_current_values);
			break;
		}/* else if (input_index == 4) {
		 play_pause(ui_current_values);
		 if (ui_current_values[PROCESS_STATUS] == 1) {
		 } else if (ui_current_values[PROCESS_STATUS] == 0) {
		 //				message_queue[0] = 0;
		 //				message_queue[1] = 0;
		 //				message_queue[2] = 's';
		 } else if (ui_current_values[PROCESS_STATUS] == 2) {
		 //				message_queue[0] = 0;
		 //				message_queue[1] = 0;
		 //				message_queue[2] = 'p';
		 }
		 break;
		 }*/else {
			PRINTF("\r\n\tInvalid data received!");
			ui_delay(5000000);
		}
	}
}

void start_stop(int *ui_current_values) {
	while (1) {
		if (ui_current_values[MODE] == 1) {
			if (((ui_current_values[RED_START_VALUE]
					+ ui_current_values[RED_RESOLUTION_VALUE])
					<= ui_current_values[RED_END_VALUE])
					&& ((ui_current_values[GREEN_START_VALUE]
							+ ui_current_values[GREEN_RESOLUTION_VALUE])
							<= ui_current_values[GREEN_END_VALUE])
					&& ((ui_current_values[BLUE_START_VALUE]
							+ ui_current_values[BLUE_RESOLUTION_VALUE])
							<= ui_current_values[BLUE_END_VALUE])) {
				if (ui_current_values[PROCESS_STATUS] == 0) {
					ui_current_values[PROCESS_STATUS] = 1;
				} else if (ui_current_values[PROCESS_STATUS] == 1) {
					ui_current_values[PROCESS_STATUS] = 0;
				} else if (ui_current_values[PROCESS_STATUS] == 2) {
					ui_current_values[PROCESS_STATUS] = 1;
				}
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}
		} else if (ui_current_values[MODE] == 2) {
			if (((ui_current_values[RED_START_VALUE]
					- ui_current_values[RED_RESOLUTION_VALUE])
					>= ui_current_values[RED_END_VALUE])
					&& ((ui_current_values[GREEN_START_VALUE]
							- ui_current_values[GREEN_RESOLUTION_VALUE])
							>= ui_current_values[GREEN_END_VALUE])
					&& ((ui_current_values[BLUE_START_VALUE]
							- ui_current_values[BLUE_RESOLUTION_VALUE])
							>= ui_current_values[BLUE_END_VALUE])) {
				if (ui_current_values[PROCESS_STATUS] == 0) {
					ui_current_values[PROCESS_STATUS] = 1;
				} else if (ui_current_values[PROCESS_STATUS] == 1) {
					ui_current_values[PROCESS_STATUS] = 0;
				} else if (ui_current_values[PROCESS_STATUS] == 2) {
					ui_current_values[PROCESS_STATUS] = 1;
				}
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}

		} else if (ui_current_values[MODE] == 3) {
			if ((ui_current_values[RED_START_VALUE]
					< ui_current_values[RED_END_VALUE])
					&& (ui_current_values[GREEN_START_VALUE]
							< ui_current_values[GREEN_END_VALUE])
					&& (ui_current_values[BLUE_START_VALUE]
							< ui_current_values[BLUE_END_VALUE])) {
				if (ui_current_values[PROCESS_STATUS] == 0) {
					ui_current_values[PROCESS_STATUS] = 1;
				} else if (ui_current_values[PROCESS_STATUS] == 1) {
					ui_current_values[PROCESS_STATUS] = 0;
				} else if (ui_current_values[PROCESS_STATUS] == 2) {
					ui_current_values[PROCESS_STATUS] = 1;
				}
				//PRINTF("\r\n\t%d", process_status);
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}

		} else if (ui_current_values[MODE] == 4) {
			PRINTF("\r\n\tSuccess");
			ui_delay(5000000);
			ui_current_values[PROCESS_STATUS] = 1;
			break;
		} else {
			PRINTF("\r\n\tInvalid Data");
			ui_delay(5000000);
			break;
		}
	}
}

void play_pause(int *ui_current_values) {
	while (1) {
		if (ui_current_values[MODE] == 1) {
			if (((ui_current_values[RED_START_VALUE]
					+ ui_current_values[RED_RESOLUTION_VALUE])
					<= ui_current_values[RED_END_VALUE])
					&& ((ui_current_values[GREEN_START_VALUE]
							+ ui_current_values[GREEN_RESOLUTION_VALUE])
							<= ui_current_values[GREEN_END_VALUE])
					&& ((ui_current_values[BLUE_START_VALUE]
							+ ui_current_values[BLUE_RESOLUTION_VALUE])
							<= ui_current_values[BLUE_END_VALUE])) {
				if (ui_current_values[PROCESS_STATUS] == 0) {
					ui_current_values[PROCESS_STATUS] = 0;
				} else if (ui_current_values[PROCESS_STATUS] == 1) {
					ui_current_values[PROCESS_STATUS] = 2;
				} else if (ui_current_values[PROCESS_STATUS] == 2) {
					ui_current_values[PROCESS_STATUS] = 1;
				}
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}
		} else if (ui_current_values[MODE] == 2) {
			if (((ui_current_values[RED_START_VALUE]
					- ui_current_values[RED_RESOLUTION_VALUE])
					>= ui_current_values[RED_END_VALUE])
					&& ((ui_current_values[GREEN_START_VALUE]
							- ui_current_values[GREEN_RESOLUTION_VALUE])
							>= ui_current_values[GREEN_END_VALUE])
					&& ((ui_current_values[BLUE_START_VALUE]
							- ui_current_values[BLUE_RESOLUTION_VALUE])
							>= ui_current_values[BLUE_END_VALUE])) {
				if (ui_current_values[PROCESS_STATUS] == 0) {
					ui_current_values[PROCESS_STATUS] = 0;
				} else if (ui_current_values[PROCESS_STATUS] == 1) {
					ui_current_values[PROCESS_STATUS] = 2;
				} else if (ui_current_values[PROCESS_STATUS] == 2) {
					ui_current_values[PROCESS_STATUS] = 1;
				}
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}

		} else if (ui_current_values[MODE] == 3) {
			if ((ui_current_values[RED_START_VALUE]
					< ui_current_values[RED_END_VALUE])
					&& (ui_current_values[GREEN_START_VALUE]
							< ui_current_values[GREEN_END_VALUE])
					&& (ui_current_values[BLUE_START_VALUE]
							< ui_current_values[BLUE_END_VALUE])) {
				if (ui_current_values[PROCESS_STATUS] == 0) {
					ui_current_values[PROCESS_STATUS] = 0;
				} else if (ui_current_values[PROCESS_STATUS] == 1) {
					ui_current_values[PROCESS_STATUS] = 2;
				} else if (ui_current_values[PROCESS_STATUS] == 2) {
					ui_current_values[PROCESS_STATUS] = 1;
				}
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}
		} else if (ui_current_values[MODE] == 4) {
			PRINTF("\r\n\tSuccess");
			ui_delay(5000000);
			break;
		} else {
			PRINTF("\r\n\tInvalid Data");
			ui_delay(5000000);
			break;
		}
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
				PRINTF("\033[47m");
				PRINTF("\033[30m");
			} else {
				PRINTF("");
			}
			PRINTF("        %s", prompt[i]);
			if (pointer[i] == 1) {
				PRINTF("          <==  \r\n");
				PRINTF("\033[0m");
			} else {
				PRINTF("                       \r\n");
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

int color_change_rate_read() {
	int color_change_rate[3];
	int return_val;

	while (1) {
		PRINTF("\033[19;9HEdit Values :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_");
		PRINTF("\033[19;55H_");
		PRINTF("\033[19;60H_");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			color_change_rate[0] = UART_ReadByte(UART0) - 48;
			if ((color_change_rate[0] >= 0) && (color_change_rate[0] < 10)) {
				PRINTF("\033[19;50H%d", color_change_rate[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			color_change_rate[1] = UART_ReadByte(UART0) - 48;
			if ((color_change_rate[1] >= 0) && (color_change_rate[1] < 10)) {
				PRINTF("\033[19;55H%d", color_change_rate[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			color_change_rate[2] = UART_ReadByte(UART0) - 48;
			if ((color_change_rate[2] >= 0) && (color_change_rate[2] < 10)) {
				PRINTF("\033[19;60H%d", color_change_rate[2]);
				break;
			} else {
				continue;
			}
		}
		return_val = ((color_change_rate[0] * 100) + (color_change_rate[1] * 10)
				+ (color_change_rate[2]));
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

void start_color_read(int *start_color) {
	while (1) {
		PRINTF("\n\r\tEdit Values :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_ R");
		PRINTF("\033[19;55H_ G");
		PRINTF("\033[19;60H_ B");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			start_color[0] = UART_ReadByte(UART0) - 48;
			if ((start_color[0] >= 0) && (start_color[0] <= 7)) {
				PRINTF("\033[19;50H%d", start_color[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			start_color[1] = UART_ReadByte(UART0) - 48;
			if ((start_color[1] >= 0) && (start_color[1] <= 7)) {
				PRINTF("\033[19;55H%d", start_color[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			start_color[2] = UART_ReadByte(UART0) - 48;
			if ((start_color[2] >= 0) && (start_color[2] <= 3)) {
				PRINTF("\033[19;60H%d", start_color[2]);
				break;
			} else {
				continue;
			}
		}
		ui_delay(1000000);
		break;
	}
}

void end_color_read(int *end_color) {
	while (1) {
		PRINTF("\n\r\tEdit Values :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_ R");
		PRINTF("\033[19;55H_ G");
		PRINTF("\033[19;60H_ B");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			end_color[0] = UART_ReadByte(UART0) - 48;
			if ((end_color[0] >= 0) && (end_color[0] <= 7)) {
				PRINTF("\033[19;50H%d", end_color[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			end_color[1] = UART_ReadByte(UART0) - 48;
			if ((end_color[1] >= 0) && (end_color[1] <= 7)) {
				PRINTF("\033[19;55H%d", end_color[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			end_color[2] = UART_ReadByte(UART0) - 48;
			if ((end_color[2] >= 0) && (end_color[2] <= 3)) {
				PRINTF("\033[19;60H%d", end_color[2]);
				break;
			} else {
				continue;
			}
		}
		ui_delay(1000000);
		break;
	}
}

void resolution_read(int *resolution) {

	while (1) {
		PRINTF("\n\r\tEdit Values :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_ R");
		PRINTF("\033[19;55H_ G");
		PRINTF("\033[19;60H_ B");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			resolution[0] = UART_ReadByte(UART0) - 48;
			if ((resolution[0] >= 0) && (resolution[0] <= 7)) {
				PRINTF("\033[19;50H%d", resolution[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			resolution[1] = UART_ReadByte(UART0) - 48;
			if ((resolution[1] >= 0) && (resolution[1] <= 7)) {
				PRINTF("\033[19;55H%d", resolution[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			resolution[2] = UART_ReadByte(UART0) - 48;
			if ((resolution[2] >= 0) && (resolution[2] <= 3)) {
				PRINTF("\033[19;60H%d", resolution[2]);
				break;
			} else {
				continue;
			}
		}
		ui_delay(1000000);
		break;
	}
}

int up_down_count_read() {
	int up_down_count_read[3];
	int return_val;

	while (1) {
		PRINTF("\033[19;9HEnter count :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_");
		PRINTF("\033[19;55H_");
		PRINTF("\033[19;60H_");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			up_down_count_read[0] = UART_ReadByte(UART0) - 48;
			if ((up_down_count_read[0] >= 0) && (up_down_count_read[0] < 10)) {
				PRINTF("\033[19;50H%d", up_down_count_read[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			up_down_count_read[1] = UART_ReadByte(UART0) - 48;
			if ((up_down_count_read[1] >= 0) && (up_down_count_read[1] < 10)) {
				PRINTF("\033[19;55H%d", up_down_count_read[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			up_down_count_read[2] = UART_ReadByte(UART0) - 48;
			if ((up_down_count_read[2] >= 0) && (up_down_count_read[2] < 10)) {
				PRINTF("\033[19;60H%d", up_down_count_read[2]);
				break;
			} else {
				continue;
			}
		}
		return_val = ((up_down_count_read[0] * 100)
				+ (up_down_count_read[1] * 10) + (up_down_count_read[2]));
		ui_delay(1000000);
		break;
	}
	return return_val;
}

int validation_warning(int *ui_current_values) {
	int validation_flag = 0;
	while (1) {
		if (ui_current_values[MODE] == 1) {
			if (((ui_current_values[RED_START_VALUE]
					+ ui_current_values[RED_RESOLUTION_VALUE])
					<= ui_current_values[RED_END_VALUE])
					&& ((ui_current_values[GREEN_START_VALUE]
							+ ui_current_values[GREEN_RESOLUTION_VALUE])
							<= ui_current_values[GREEN_END_VALUE])
					&& ((ui_current_values[BLUE_START_VALUE]
							+ ui_current_values[BLUE_RESOLUTION_VALUE])
							<= ui_current_values[BLUE_END_VALUE])) {
				break;
			} else {
				PRINTF("\r\n\tConfiguration is invalid...");
				PRINTF("\r\n\tPress Enter to proceed ...");
				PRINTF("\r\n\tPress Space to edit configuration ...");
				validation_flag = 1;
				break;
			}
		} else if (ui_current_values[MODE] == 2) {
			if (((ui_current_values[RED_START_VALUE]
					+ ui_current_values[RED_RESOLUTION_VALUE])
					>= ui_current_values[RED_END_VALUE])
					&& ((ui_current_values[GREEN_START_VALUE]
							+ ui_current_values[GREEN_RESOLUTION_VALUE])
							>= ui_current_values[GREEN_END_VALUE])
					&& ((ui_current_values[BLUE_START_VALUE]
							+ ui_current_values[BLUE_RESOLUTION_VALUE])
							>= ui_current_values[BLUE_END_VALUE])) {
				break;
			} else {
				PRINTF("\r\n\tConfiguration is invalid...");
				PRINTF("\r\n\tPress Enter to proceed ...");
				PRINTF("\r\n\tPress Space to edit configuration ...");
				validation_flag = 1;
				break;
			}

		} else if (ui_current_values[MODE] == 3) {
			if ((ui_current_values[RED_START_VALUE]
					< ui_current_values[RED_END_VALUE])
					&& (ui_current_values[GREEN_START_VALUE]
							< ui_current_values[GREEN_END_VALUE])
					&& (ui_current_values[BLUE_START_VALUE]
							< ui_current_values[BLUE_END_VALUE])) {
				break;
			} else {
				PRINTF("\r\n\tConfiguration is invalid...");
				PRINTF("\r\n\tPress Enter to proceed ...");
				PRINTF("\r\n\tPress Space to edit configuration ...");
				validation_flag = 1;
				break;
			}
		} else if (ui_current_values[MODE] == 4) {
			break;
		} else {
			PRINTF("\r\n\tInvalid Data");
			break;
		}
	}

	return validation_flag;
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
