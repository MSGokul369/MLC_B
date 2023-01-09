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
}

void ui_homescreen(int led_refresh_rate, int start_color[3], int end_color[3],
		int color_change_rate, int current_mode_index, int resolution[3],
		int up_down_count, int process_status) {
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
	PRINTF("\t\t\t\t Slave Status\t:\tOnline \r\n");
	switch (process_status) {
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
	PRINTF("\t\t\t\t Refresh Rate\t\t:\t%d Hz \r\n", led_refresh_rate);
	PRINTF("\t\t\t\t Start Color Code\t:\t%d %d %d True Color \r\n",
			start_color[0], start_color[1], start_color[2]);
	PRINTF("\t\t\t\t End Color Code\t\t:\t%d %d %d True Color \r\n",
			end_color[0], end_color[1], end_color[2]);
	PRINTF("\t\t\t\t Color Change Rate\t:\t%d\r\n", color_change_rate);

	switch (current_mode_index) {
	case 1:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP \r\n");
		break;
	case 2:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-DOWN \r\n");
		break;
	case 3:
		PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP/DOWN | Count : %d \r\n",
				up_down_count);
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
	PRINTF(
			"\t\t\t\t Current RGB Code :   \033[31mx \033[32mx \033[34mx \033[37m\r\n \033[0m");
	PRINTF("\r\n");
	PRINTF("\r\n");

}

void ui_homescreen_slave() {

	boot_screen();
	ui_delay(500000);

	int current_mode_index = 1;
	int color_change_rate = 1;
	int led_refresh_rate = 1;
	int start_color[3] = { 0, 0, 0 }, end_color[3] = { 0, 0, 0 },
			resolution[3] = { 1, 1, 1 };

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
	PRINTF("\t\t\t\t Master Status\t:\tOnline \r\n");
	PRINTF("\t\t\t\t Process Status\t:\tRunning \r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Current Configurations:- \r\n");
	PRINTF("\t\t\t\t Refresh Rate\t\t:\t%d Hz \r\n", led_refresh_rate);
	PRINTF("\t\t\t\t Start Color Code\t:\t%d %d %d True Color \r\n",
			start_color[0], start_color[1], start_color[2]);
	PRINTF("\t\t\t\t End Color Code\t\t:\t%d %d %d True Color \r\n",
			end_color[0], end_color[1], end_color[2]);
	PRINTF("\t\t\t\t Color Change Rate\t:\t%d\r\n", color_change_rate);

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

void ui_configure_color_pattern(int led_refresh_rate, int start_color[3],
		int end_color[3], int color_change_rate, int current_mode_index,
		int resolution[3], int up_down_count) {
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
	PRINTF("\t1.\t\t\t\t\t\t:\t%d %d %d RGB \r\n", start_color[0],
			start_color[1], start_color[2]);
	PRINTF("\t2.\t\t\t\t\t\t:\t%d %d %d RGB \r\n", end_color[0], end_color[1],
			end_color[2]);
	PRINTF("\t3.\t\t\t\t\t\t:\t%d %d %d RGB \r\n", resolution[0], resolution[1],
			resolution[2]);
	PRINTF("\t4.\t\t\t\t\t\t:\t%d \r\n", color_change_rate);
	PRINTF("\t5.\t\t\t\t\t\t:\t%d \r\n", led_refresh_rate);
	switch (current_mode_index) {
	case 1:
		PRINTF("\t\t\t\t\t\t\t:\tAuto-UP \r\n");
		break;
	case 2:
		PRINTF("\t\t\t\t\t\t\t:\tAuto-DOWN \r\n");
		break;
	case 3:
		PRINTF("\t\t\t\t\t\t\t:\tAuto-UP/DOWN | Count : %d\r\n", up_down_count);
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

void master_ui(void) {

	boot_screen();
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

	int input_index;
	int current_mode_index = 1;
	int curent_rgb_scheme_index = 1;
	int color_change_rate = 1;
	int led_refresh_rate = 1;
	int start_color[3] = { 0, 0, 0 }, end_color[3] = { 0, 0, 0 },
			resolution[3] = { 1, 1, 1 };
	int *start_pointer;
	int *end_pointer;
	int *resolution_pointer;
	int up_down_count;
	int process_status = 0;

	while (1) {
		ui_homescreen(led_refresh_rate, start_color, end_color,
				color_change_rate, current_mode_index, resolution,
				up_down_count, process_status);
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
		/*PRINTF("\r\n\tSelected Index : %c", input_index);
		 PRINTF("\r\n\tPlease wait...");
		 ui_delay(5000000);
		 */
		if (input_index == 1) {
			while (1) {
				ui_rgb_code_scheme(curent_rgb_scheme_index);

				char color_scheme_menu[4][30] = { "332 RGB", "444 RGB",
						"888 RGB", "Home" };
				input_index = arrow_key_navigate(color_scheme_menu, 4, 9, 10);

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
				ui_configure_color_pattern(led_refresh_rate, start_color,
						end_color, color_change_rate, current_mode_index,
						resolution, up_down_count);

				char color_scheme_menu[7][30] = { "Start color", "End color",
						"Color change resolution", "Color change rate",
						"LED refresh rate", "Mode", "Home", };
				input_index = arrow_key_navigate(color_scheme_menu, 7, 8, 10);
				UART_DisableInterrupts(UART,
						kUART_RxDataRegFullInterruptEnable
								| kUART_RxOverrunInterruptEnable);
				if (input_index == 1) {
					while (1) {
						start_pointer = start_color_read();
						for (int i = 0; i <= 2; i++) {
							start_color[i] = start_pointer[i];
						}
						UART_EnableInterrupts(UART,
								kUART_RxDataRegFullInterruptEnable
										| kUART_RxOverrunInterruptEnable);
						break;
					}
				} else if (input_index == 2) {
					while (1) {
						end_pointer = end_color_read();
						for (int i = 0; i <= 2; i++) {
							end_color[i] = end_pointer[i];
						}
						UART_EnableInterrupts(UART,
								kUART_RxDataRegFullInterruptEnable
										| kUART_RxOverrunInterruptEnable);
						break;
					}
				} else if (input_index == 3) {
					while (1) {
						resolution_pointer = resolution_read();
						for (int i = 0; i <= 2; i++) {
							resolution[i] = resolution_pointer[i];
						}
						UART_EnableInterrupts(UART,
								kUART_RxDataRegFullInterruptEnable
										| kUART_RxOverrunInterruptEnable);
						break;
					}
				} else if (input_index == 4) {
					while (1) {
						color_change_rate = color_change_rate_read();
						if (color_change_rate > 0 && color_change_rate <= 500) {
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
						ui_modes(current_mode_index, up_down_count);
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
								UART_DisableInterrupts(UART,
										kUART_RxDataRegFullInterruptEnable
												| kUART_RxOverrunInterruptEnable);
								up_down_count = up_down_count_read();
								ui_delay(1000000);
								UART_EnableInterrupts(UART,
										kUART_RxDataRegFullInterruptEnable
												| kUART_RxOverrunInterruptEnable);
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

					int status_check = 0;
					int uart_read;

					status_check = validation_warning(led_refresh_rate,
							start_color, end_color, color_change_rate,
							current_mode_index, resolution);

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
			process_status = start_stop(led_refresh_rate, start_color,
					end_color, color_change_rate, current_mode_index,
					resolution, process_status);

		} else if (input_index == 4) {
			process_status = play_pause(led_refresh_rate, start_color,
					end_color, color_change_rate, current_mode_index,
					resolution, process_status);
		} else {
			PRINTF("\r\n\tInvalid data received!");
			ui_delay(5000000);
		}

	}
}

int start_stop(int led_refresh_rate, int start_color[3], int end_color[3],
		int color_change_rate, int current_mode_index, int resolution[3],
		int process_status) {
	while (1) {
		if (current_mode_index == 1) {
			if ((start_color[0] < end_color[0])
					&& (start_color[1] < end_color[1])
					&& (start_color[2] < end_color[2])) {
				if (process_status == 0) {
					process_status = 1;
				} else if (process_status == 1) {
					process_status = 0;
				} else if (process_status == 2) {
					process_status = 1;
				}
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}
		} else if (current_mode_index == 2) {
			if ((start_color[0] > end_color[0])
					&& (start_color[1] > end_color[1])
					&& (start_color[2] > end_color[2])) {
				if (process_status == 0) {
					process_status = 1;
				} else if (process_status == 1) {
					process_status = 0;
				} else if (process_status == 2) {
					process_status = 1;
				}
				break;
			} else {
				//PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}

		} else if (current_mode_index == 3) {
			if ((start_color[0] < end_color[0])
					&& (start_color[1] < end_color[1])
					&& (start_color[2] < end_color[2])) {
				if (process_status == 0) {
					process_status = 1;
				} else if (process_status == 1) {
					process_status = 0;
				} else if (process_status == 2) {
					process_status = 1;
				}
				//PRINTF("\r\n\t%d", process_status);
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}

		} else if (current_mode_index == 4) {
			PRINTF("\r\n\tSuccess");
			ui_delay(5000000);
			process_status = 1;
			break;
		} else {
			PRINTF("\r\n\tInvalid Data");
			ui_delay(5000000);
			break;
		}
	}

	return process_status;
}

int play_pause(int led_refresh_rate, int start_color[3], int end_color[3],
		int color_change_rate, int current_mode_index, int resolution[3],
		int process_status) {
	while (1) {
		if (current_mode_index == 1) {
			if ((start_color[0] < end_color[0])
					&& (start_color[1] < end_color[1])
					&& (start_color[2] < end_color[2])) {
				if (process_status == 0) {
					process_status = 0;
				} else if (process_status == 1) {
					process_status = 2;
				} else if (process_status == 2) {
					process_status = 1;
				}
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}
		} else if (current_mode_index == 2) {
			if ((start_color[0] > end_color[0])
					&& (start_color[1] > end_color[1])
					&& (start_color[2] > end_color[2])) {
				if (process_status == 0) {
					process_status = 0;
				} else if (process_status == 1) {
					process_status = 2;
				} else if (process_status == 2) {
					process_status = 1;
				}
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}

		} else if (current_mode_index == 3) {
			if ((start_color[0] < end_color[0])
					&& (start_color[1] < end_color[1])
					&& (start_color[2] < end_color[2])) {
				if (process_status == 0) {
					process_status = 0;
				} else if (process_status == 1) {
					process_status = 2;
				} else if (process_status == 2) {
					process_status = 1;
				}
				break;
			} else {
				PRINTF("\r\n\tInvalid Configuration");
				ui_delay(5000000);
				break;
			}
		} else if (current_mode_index == 4) {
			PRINTF("\r\n\tSuccess");
			ui_delay(5000000);
			break;
		} else {
			PRINTF("\r\n\tInvalid Data");
			ui_delay(5000000);
			break;
		}
	}
	return process_status;
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

int* start_color_read() {
	static int start_color_read[3];

	while (1) {
		PRINTF("\n\r\tEdit Values :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_ R");
		PRINTF("\033[19;55H_ G");
		PRINTF("\033[19;60H_ B");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			start_color_read[0] = UART_ReadByte(UART0) - 48;
			if ((start_color_read[0] >= 0) && (start_color_read[0] <= 7)) {
				PRINTF("\033[19;50H%d", start_color_read[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			start_color_read[1] = UART_ReadByte(UART0) - 48;
			if ((start_color_read[1] >= 0) && (start_color_read[1] <= 7)) {
				PRINTF("\033[19;55H%d", start_color_read[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			start_color_read[2] = UART_ReadByte(UART0) - 48;
			if ((start_color_read[2] >= 0) && (start_color_read[2] <= 3)) {
				PRINTF("\033[19;60H%d", start_color_read[2]);
				break;
			} else {
				continue;
			}
		}
		ui_delay(1000000);
		break;
	}
	return start_color_read;
}

int* end_color_read() {
	static int end_color_read[3];

	while (1) {
		PRINTF("\n\r\tEdit Values :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_ R");
		PRINTF("\033[19;55H_ G");
		PRINTF("\033[19;60H_ B");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			end_color_read[0] = UART_ReadByte(UART0) - 48;
			if ((end_color_read[0] >= 0) && (end_color_read[0] <= 7)) {
				PRINTF("\033[19;50H%d", end_color_read[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			end_color_read[1] = UART_ReadByte(UART0) - 48;
			if ((end_color_read[1] >= 0) && (end_color_read[1] <= 7)) {
				PRINTF("\033[19;55H%d", end_color_read[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			end_color_read[2] = UART_ReadByte(UART0) - 48;
			if ((end_color_read[2] >= 0) && (end_color_read[2] <= 3)) {
				PRINTF("\033[19;60H%d", end_color_read[2]);
				break;
			} else {
				continue;
			}
		}
		ui_delay(1000000);
		break;
	}
	return end_color_read;
}

int* resolution_read() {
	static int resolution_read[3];

	while (1) {
		PRINTF("\n\r\tEdit Values :");
		PRINTF("\033[19;50H                                          ");
		PRINTF("\033[19;50H_ R");
		PRINTF("\033[19;55H_ G");
		PRINTF("\033[19;60H_ B");
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			resolution_read[0] = UART_ReadByte(UART0) - 48;
			if ((resolution_read[0] >= 0) && (resolution_read[0] <= 7)) {
				PRINTF("\033[19;50H%d", resolution_read[0]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			resolution_read[1] = UART_ReadByte(UART0) - 48;
			if ((resolution_read[1] >= 0) && (resolution_read[1] <= 7)) {
				PRINTF("\033[19;55H%d", resolution_read[1]);
				break;
			} else {
				continue;
			}
		}
		while (1) {
			while (!(kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0)))
				UART_ClearStatusFlags(UART0, kUART_RxDataRegFullFlag);
			resolution_read[2] = UART_ReadByte(UART0) - 48;
			if ((resolution_read[2] >= 0) && (resolution_read[2] <= 3)) {
				PRINTF("\033[19;60H%d", resolution_read[2]);
				break;
			} else {
				continue;
			}
		}
		ui_delay(1000000);
		break;
	}
	return resolution_read;
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

int validation_warning(int led_refresh_rate, int start_color[3],
		int end_color[3], int color_change_rate, int current_mode_index,
		int resolution[3]) {
	int validation_flag = 0;
	while (1) {
		if (current_mode_index == 1) {
			if ((start_color[0] < end_color[0])
					&& (start_color[1] < end_color[1])
					&& (start_color[2] < end_color[2])) {
				break;
			} else {
				PRINTF("\r\n\tConfiguration is invalid...");
				PRINTF("\r\n\tPress Enter to proceed ...");
				PRINTF("\r\n\tPress Space to edit configuration ...");
				validation_flag = 1;
				break;
			}
		} else if (current_mode_index == 2) {
			if ((start_color[0] > end_color[0])
					&& (start_color[1] > end_color[1])
					&& (start_color[2] > end_color[2])) {
				break;
			} else {
				PRINTF("\r\n\tConfiguration is invalid...");
				PRINTF("\r\n\tPress Enter to proceed ...");
				PRINTF("\r\n\tPress Space to edit configuration ...");
				validation_flag = 1;
				break;
			}

		} else if (current_mode_index == 3) {
			if ((start_color[0] < end_color[0])
					&& (start_color[1] < end_color[1])
					&& (start_color[2] < end_color[2])) {
				break;
			} else {
				PRINTF("\r\n\tConfiguration is invalid...");
				PRINTF("\r\n\tPress Enter to proceed ...");
				PRINTF("\r\n\tPress Space to edit configuration ...");
				validation_flag = 1;
				break;
			}
		} else if (current_mode_index == 4) {
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
