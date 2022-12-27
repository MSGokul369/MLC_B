#include "../UI/user_interface.h"
#include <stdio.h>
#include "fsl_debug_console.h"
void ui_homescreen(void) {
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
	PRINTF("\t\t\t\t Refresh Rate\t\t:\txxxxx Hz \r\n");
	PRINTF("\t\t\t\t Start Color Code\t:\tx x x True Color \r\n");
	PRINTF("\t\t\t\t End Color Code\t\t:\tx x x True Color \r\n");
	PRINTF("\t\t\t\t Color Change Rate\t:\txxx\r\n");
	PRINTF("\t\t\t\t Mode\t\t\t:\tAuto-UP \r\n");
	PRINTF("\t\t\t\t Resolution\t\t:\t \r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Current RGB Code : x x x \r\n");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t 1.\tConfigure RGB LED \r\n");
	PRINTF("\t\t\t\t 2.\tConfigure Color Pattern \r\n");
	PRINTF("\t\t\t\t s.\tStart/Stop \r\n");
	PRINTF("\t\t\t\t p.\tPause \r\n");
	PRINTF("\t\t\t\t  \r\n");
	PRINTF("\t Type index and press Enter \r\n");
}

void ui_rgb_code_scheme(int curent_rgb_scheme_index) {
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Palette       Version 1.0 \r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	PRINTF("\t Select color code Scheme \r\n");
	PRINTF("\r\n");
	PRINTF("\t1.\t332 RGB \r\n");
	PRINTF("\t2.\t444 RGB \r\n");
	PRINTF("\t3.\t888 RGB \r\n");
	PRINTF("\t4.\tHome \r\n");
	PRINTF("\r\n");
	switch (curent_rgb_scheme_index) {
		case 1:
			PRINTF("\tCurrent color scheme - 332 RGB\r\n");
			break;
		case 2:
			PRINTF("\tCurrent color scheme - 444 RGB\r\n");
			break;
		case 3:
			PRINTF("\tCurrent color scheme - 888 RGB\r\n");
			break;
		default:
			PRINTF("Data invalid\r\n");
			break;
	}
	PRINTF("\r\n");
	PRINTF("\t Type index and press Enter \r\n");

}

void ui_configure_colour_pattern(void) {
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Palette       Version 1.0 \r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	PRINTF("\t Configure Color Pattern \r\n");
	PRINTF("\r\n");
	PRINTF("\t1.\tStart color \r\n");
	PRINTF("\t2.\tEnd color \r\n");
	PRINTF("\t3.\tColor change resolution \r\n");
	PRINTF("\t4.\tColor change rate \r\n");
	PRINTF("\t5.\tLED refresh rate \r\n");
	PRINTF("\t6.\tMode \r\n");
	PRINTF("\t7.\tHome \r\n");
	PRINTF("\t Type index and press Enter \r\n");

}

void ui_modes(int current_mode_index) {

	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\n");
	PRINTF("\t\t\t\t Palette       Version 1.0 \r\n");
	PRINTF("\t\t\t\t Multicolor LED Controller \r\n");
	PRINTF("\t\t\t\t    ******************* \r\n");
	PRINTF("\r\n");
	PRINTF("\t Select Mode \r\n");
	PRINTF("\r\n");
	PRINTF("\t1.\tAuto UP\r\n");
	PRINTF("\t2.\tAuto DOWN\r\n");
	PRINTF("\t3.\tAuto UP/DOWN\r\n");
	PRINTF("\t4.\tManual\r\n");
	PRINTF("\t5.\tGo back\r\n");
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
	PRINTF("\t Type index and press Enter \r\n");

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

	while (1) {
		ui_homescreen();
		while (1) {
			SCANF("%d", &input_index);
			if (input_index > 0 && input_index < 3) {
				break;
			} else {
				PRINTF("\r\n\tInvalid Entry!\r\n\tTry again...");
				continue;
			}
		}
		PRINTF("\r\n\tSelected Index : %d", input_index);
		PRINTF("\r\n\tPlease wait...");
		ui_delay(5000000);

		if (input_index == 1) {
			while (1) {
				ui_rgb_code_scheme(curent_rgb_scheme_index);

				while (1) {
					SCANF("%d", &input_index);
					if (input_index > 0 && input_index < 5) {
						break;
					} else {
						PRINTF("\r\n\tInvalid Entry!\r\n\tTry again...");
						continue;
					}
				}
				if (input_index == 1) {
					while (1) {
						PRINTF("\r\n\t332 scheme selected...");
						PRINTF("\r\n\tPlease wait...");
						curent_rgb_scheme_index = 1;
						ui_delay(5000000);
						break;
					}
				} else if (input_index == 2) {
					while (1) {
						PRINTF("\r\n\t444 scheme unavailable!");
						PRINTF("\r\n\tPlease wait...");
						curent_rgb_scheme_index = 2;
						ui_delay(5000000);
						break;
					}
				} else if (input_index == 3) {
					while (1) {
						PRINTF("\r\n\t888 scheme unavailable!");
						PRINTF("\r\n\tPlease wait...");
						curent_rgb_scheme_index = 3;
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
				ui_configure_colour_pattern();

				while (1) {
					SCANF("%d", &input_index);
					if (input_index > 0 && input_index < 8) {
						break;
					} else {
						PRINTF("\r\n\tInvalid Entry!\r\n\tTry again...");
						continue;
					}
				}
				if (input_index == 1) {
					while (1) {
						PRINTF("\r\n\tStart Color...");
						PRINTF("\r\n\tPlease wait...");
						ui_delay(5000000);
						break;
					}
				} else if (input_index == 2) {
					while (1) {
						PRINTF("\r\n\tEnd Color");
						PRINTF("\r\n\tPlease wait...");
						ui_delay(5000000);
						break;
					}
				} else if (input_index == 3) {
					while (1) {
						PRINTF("\r\n\tResolution");
						PRINTF("\r\n\tPlease wait...");
						ui_delay(5000000);
						break;
					}

				} else if (input_index == 4) {
					while (1) {
						PRINTF("\r\n\tChange Rate");
						PRINTF("\r\n\tPlease wait...");
						ui_delay(5000000);
						break;
					}
				} else if (input_index == 5) {
					while (1) {
						PRINTF("\r\n\tRefresh Rate");
						PRINTF("\r\n\tPlease wait...");
						ui_delay(5000000);
						break;
					}
				} else if (input_index == 6) {
					PRINTF("\r\n\tMode");
					PRINTF("\r\n\tPlease wait...");
					ui_delay(5000000);
					while (1) {
						ui_modes(current_mode_index);
						while (1) {
							SCANF("%d", &input_index);
							if (input_index > 0 && input_index < 6) {
								break;
							} else {
								PRINTF(
										"\r\n\tInvalid Entry!\r\n\tTry again...");
								continue;
							}
						}
						if (input_index == 1) {
							while (1) {
								PRINTF("\r\n\tAuto: UP mode selected.");
								PRINTF("\r\n\tPlease wait...");
								current_mode_index = 1;
								ui_delay(5000000);
								break;
							}
						} else if (input_index == 2) {
							while (1) {
								PRINTF("\r\n\tAuto: DOWN mode selected.");
								PRINTF("\r\n\tPlease wait...");
								current_mode_index = 2;
								ui_delay(5000000);
								break;
							}
						} else if (input_index == 3) {
							while (1) {
								PRINTF("\r\n\tAuto: UP/DOWN mode selected.");
								PRINTF("\r\n\tPlease wait...");
								current_mode_index = 3;
								ui_delay(5000000);
								break;
							}

						} else if (input_index == 4) {
							while (1) {
								PRINTF("\r\n\tManual Mode selected");
								PRINTF("\r\n\tPlease wait...");
								current_mode_index = 4;
								ui_delay(5000000);
								break;
							}
						} else if (input_index == 5) {
							PRINTF("\r\n\tGoing back.");
							PRINTF("\r\n\tPlease wait...");
							ui_delay(5000000);
							break;
						} else {
							PRINTF("\r\n\tInvalid data received");
						}
					}
				} else if (input_index == 7) {
					PRINTF("\r\n\tLoading Home");
					PRINTF("\r\n\tPlease wait...");
					break;
				} else {
					PRINTF("\r\n\tInvalid data received");
				}
			}
		} else {
			PRINTF("\r\n\tInvalid data received!");
			ui_delay(5000000);
		}
	}
}
