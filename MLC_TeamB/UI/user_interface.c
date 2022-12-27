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
	PRINTF("\t\t\t |_| /_/    \\_\\______|______|  |_|     |_|  |______| \tVersion 1.0\r\n");
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

void ui_rgb_code_scheme(void)	{
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
	PRINTF("\t Type index and press Enter \r\n");

}

void ui_configure_colour_pattern(void)	{
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

void ui_modes(void){
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
	PRINTF("\t Type index and press Enter \r\n");

}

void ui_delay(int delay){
	int j;
	for (int d = 0; d < delay; d++){
			j=j+1;
			j=j-1;
		}
}