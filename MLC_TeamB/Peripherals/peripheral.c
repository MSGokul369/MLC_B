/*
 * peripherals.c
 *
 *  Created on: Jan 5, 2023
 *      Author: sreehari
 */
#include "peripheral.h"

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

void BOARD_InitI2CPeripherals(void)
{
	CLOCK_EnableClock(kCLOCK_PortE);
	const port_pin_config_t porte24_pin31_config = {/* Internal pull-up resistor is enabled */
	kPORT_PullUp,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is enabled */
	kPORT_OpenDrainEnable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as I2C0_SCL */
	kPORT_MuxAlt5,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE24 (pin 31) is configured as I2C0_SCL */
	PORT_SetPinConfig(PORTE, 24U, &porte24_pin31_config);

	const port_pin_config_t porte25_pin32_config = {/* Internal pull-up resistor is enabled */
	kPORT_PullUp,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is enabled */
	kPORT_OpenDrainEnable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as I2C0_SDA */
	kPORT_MuxAlt5,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE25 (pin 32) is configured as I2C0_SDA */
	PORT_SetPinConfig(PORTE, 25U, &porte25_pin32_config);
}

