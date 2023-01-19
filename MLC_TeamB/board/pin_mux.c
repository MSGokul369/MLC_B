/*
 * Copyright 2018-2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 !!GlobalInfo
 product: Pins v5.0
 processor: MK64FN1M0xxx12
 package_id: MK64FN1M0VLL12
 mcu_data: ksdk2_0
 processor_version: 4.0.0
 board: FRDM-K64F
 pin_labels:
 - {pin_num: '90', pin_signal: PTC16/UART3_RX/ENET0_1588_TMR0/FB_CS5_b/FB_TSIZ1/FB_BE23_16_BLS15_8_b, label: 'J1[2]', identifier: TMR_1588_0}
 - {pin_num: '91', pin_signal: PTC17/UART3_TX/ENET0_1588_TMR1/FB_CS4_b/FB_TSIZ0/FB_BE31_24_BLS7_0_b, label: 'J1[4]', identifier: TMR_1588_1}
 - {pin_num: '57', pin_signal: PTB9/SPI1_PCS1/UART3_CTS_b/FB_AD20, label: 'J1[6]'}
 - {pin_num: '35', pin_signal: PTA1/UART0_RX/FTM0_CH6/JTAG_TDI/EZP_DI, label: 'J1[8]'}
 - {pin_num: '69', pin_signal: PTB23/SPI2_SIN/SPI0_PCS5/FB_AD28, label: 'J1[10]'}
 - {pin_num: '36', pin_signal: PTA2/UART0_TX/FTM0_CH7/JTAG_TDO/TRACE_SWO/EZP_DO, label: 'J1[12]/J9[6]/TRACE_SWO'}
 - {pin_num: '72', pin_signal: ADC0_SE4b/CMP1_IN0/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FB_AD12/I2S0_TX_FS, label: 'J1[14]'}
 - {pin_num: '73', pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/I2S0_TX_BCLK, label: 'J1[16]'}
 - {pin_num: '64', pin_signal: PTB18/CAN0_TX/FTM2_CH0/I2S0_TX_BCLK/FB_AD15/FTM2_QD_PHA, label: 'J1[1]'}
 - {pin_num: '65', pin_signal: PTB19/CAN0_RX/FTM2_CH1/I2S0_TX_FS/FB_OE_b/FTM2_QD_PHB, label: 'J1[3]'}
 - {pin_num: '71', pin_signal: ADC0_SE15/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FB_AD13/I2S0_TXD0, label: 'J1[5]'}
 - {pin_num: '80', pin_signal: ADC1_SE4b/CMP0_IN2/PTC8/FTM3_CH4/I2S0_MCLK/FB_AD7, label: 'J1[7]'}
 - {pin_num: '81', pin_signal: ADC1_SE5b/CMP0_IN3/PTC9/FTM3_CH5/I2S0_RX_BCLK/FB_AD6/FTM2_FLT0, label: 'J1[9]'}
 - {pin_num: '77', pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/FB_AD10/CMP0_OUT/FTM0_CH2, label: 'J1[15]'}
 - {pin_num: '79', pin_signal: CMP0_IN1/PTC7/SPI0_SIN/USB_SOF_OUT/I2S0_RX_FS/FB_AD8, label: 'J1[13]', identifier: CMP0_IN1}
 - {pin_num: '70', pin_signal: ADC0_SE14/PTC0/SPI0_PCS4/PDB0_EXTRG/USB_SOF_OUT/FB_AD14/I2S0_TXD1, label: 'J1[11]'}
 - {pin_num: '84', pin_signal: PTC12/UART4_RTS_b/FB_AD27/FTM3_FLT0, label: 'J2[2]'}
 - {pin_num: '76', pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/FB_AD11/CMP1_OUT, label: 'J2[4]'}
 - {pin_num: '93', pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b, label: 'J2[6]'}
 - {pin_num: '95', pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/I2C0_SCL, label: 'J2[8]', identifier: UART2_RX}
 - {pin_num: '96', pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/I2C0_SDA, label: 'J2[10]', identifier: UART2_TX}
 - {pin_num: '94', pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b, label: 'J2[12]'}
 - {pin_num: '32', pin_signal: ADC0_SE18/PTE25/UART4_RX/I2C0_SDA/EWM_IN, label: 'J2[18]/U8[6]/I2C0_SDA', identifier: ACCEL_SDA}
 - {pin_num: '31', pin_signal: ADC0_SE17/PTE24/UART4_TX/I2C0_SCL/EWM_OUT_b, label: 'J2[20]/U8[4]/I2C0_SCL', identifier: ACCEL_SCL}
 - {pin_num: '26', pin_signal: VREF_OUT/CMP1_IN5/CMP0_IN5/ADC1_SE18, label: 'J2[17]'}
 - {pin_num: '21', pin_signal: ADC1_DM0/ADC0_DM3, label: 'J2[13]'}
 - {pin_num: '18', pin_signal: ADC0_DP0/ADC1_DP3, label: 'J2[5]'}
 - {pin_num: '19', pin_signal: ADC0_DM0/ADC1_DM3, label: 'J2[7]'}
 - {pin_num: '20', pin_signal: ADC1_DP0/ADC0_DP3, label: 'J2[11]'}
 - {pin_num: '33', pin_signal: PTE26/ENET_1588_CLKIN/UART4_CTS_b/RTC_CLKOUT/USB_CLKIN, label: 'J2[1]/D12[4]/LEDRGB_GREEN', identifier: LED_GREEN}
 - {pin_num: '27', pin_signal: DAC0_OUT/CMP1_IN3/ADC0_SE23, label: 'J4[11]', identifier: DAC0_OUT}
 - {pin_num: '66', pin_signal: PTB20/SPI2_PCS0/FB_AD31/CMP0_OUT, label: 'J6[3]/J4[9]/RF_WIFI_CE', identifier: RF_WIFI_CE}
 - {pin_num: '17', pin_signal: ADC1_DM1, label: 'J4[7]'}
 - {pin_num: '16', pin_signal: ADC1_DP1, label: 'J4[5]'}
 - {pin_num: '15', pin_signal: ADC0_DM1, label: 'J4[3]'}
 - {pin_num: '14', pin_signal: ADC0_DP1, label: 'J4[1]'}
 - {pin_num: '55', pin_signal: ADC0_SE12/PTB2/I2C0_SCL/UART0_RTS_b/ENET0_1588_TMR0/FTM0_FLT3, label: 'J4[2]', identifier: ADC0_SE12}
 - {pin_num: '56', pin_signal: ADC0_SE13/PTB3/I2C0_SDA/UART0_CTS_b/UART0_COL_b/ENET0_1588_TMR1/FTM0_FLT0, label: 'J4[4]'}
 - {pin_num: '58', pin_signal: ADC1_SE14/PTB10/SPI1_PCS0/UART3_RX/FB_AD19/FTM0_FLT1, label: 'J4[6]'}
 - {pin_num: '59', pin_signal: ADC1_SE15/PTB11/SPI1_SCK/UART3_TX/FB_AD18/FTM0_FLT2, label: 'J4[8]'}
 - {pin_num: '83', pin_signal: ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/I2S0_RXD1/FB_RW_b, label: 'J4[10]'}
 - {pin_num: '82', pin_signal: ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/I2S0_RX_FS/FB_AD5, label: 'J4[12]'}
 - {pin_num: '38', pin_signal: PTA4/LLWU_P3/FTM0_CH1/NMI_b/EZP_CS_b, label: SW3, identifier: SW3}
 - {pin_num: '78', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/I2S0_RX_BCLK/FB_AD9/I2S0_MCLK, label: 'U8[11]/SW2', identifier: SW2;ACCEL_INT1}
 - {pin_num: '52', pin_signal: RESET_b, label: 'J3[6]/J9[10]/D1/RESET', identifier: RESET}
 - {pin_num: '6', pin_signal: PTE5/SPI1_PCS2/UART3_RX/SDHC0_D2/FTM3_CH0, label: 'J15[P1]/SDHC0_D2', identifier: SDHC0_D2}
 - {pin_num: '5', pin_signal: PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/SDHC0_D3/TRACE_D0, label: 'J15[P2]/SDHC0_D3', identifier: SDHC0_D3}
 - {pin_num: '4', pin_signal: ADC0_DM2/ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SDHC0_CMD/TRACE_D1/SPI1_SOUT, label: 'J15[P3]/SDHC0_CMD', identifier: SDHC0_CMD}
 - {pin_num: '3', pin_signal: ADC0_DP2/ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b/SDHC0_DCLK/TRACE_D2, label: 'J15[P5]/SDHC0_DCLK', identifier: SDHC0_DCLK}
 - {pin_num: '2', pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/SDHC0_D0/TRACE_D3/I2C1_SCL/SPI1_SIN, label: 'J15[P7]/SDHC0_D0', identifier: SDHC0_D0}
 - {pin_num: '1', pin_signal: ADC1_SE4a/PTE0/SPI1_PCS1/UART1_TX/SDHC0_D1/TRACE_CLKOUT/I2C1_SDA/RTC_CLKOUT, label: 'J15[P8]/SDHC0_D1', identifier: SDHC0_D1}
 - {pin_num: '7', pin_signal: PTE6/SPI1_PCS3/UART3_CTS_b/I2S0_MCLK/FTM3_CH1/USB_SOF_OUT, label: 'J15[G1]/SD_CARD_DETECT', identifier: SDHC_CD}
 - {pin_num: '98', pin_signal: ADC0_SE6b/PTD5/SPI0_PCS2/UART0_CTS_b/UART0_COL_b/FTM0_CH5/FB_AD1/EWM_OUT_b/SPI1_SCK, label: 'J6[5]/RF_WIFI_SCK', identifier: WIFI_SCK}
 - {pin_num: '100', pin_signal: PTD7/CMT_IRO/UART0_TX/FTM0_CH7/FTM0_FLT1/SPI1_SIN, label: 'J6[7]/RF_WIFI_MISO', identifier: WIFI_MISO}
 - {pin_num: '97', pin_signal: PTD4/LLWU_P14/SPI0_PCS1/UART0_RTS_b/FTM0_CH4/FB_AD2/EWM_IN/SPI1_PCS0, label: 'J6[4]/RF_WIFI_CS', identifier: WIFI_CS}
 - {pin_num: '99', pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FB_AD0/FTM0_FLT0/SPI1_SOUT, label: 'J6[6]/RF_WIFI_MOSI', identifier: WIFI_MOSI}
 - {pin_num: '92', pin_signal: PTC18/UART3_RTS_b/ENET0_1588_TMR2/FB_TBST_b/FB_CS2_b/FB_BE15_8_BLS23_16_b, label: 'J6[8]/RF_WIFI_IRQ', identifier: WIFI_IRQ;TMR_1588_2}
 - {pin_num: '86', pin_signal: PTC14/UART4_RX/FB_AD25, label: 'J199[3]/BT_TX'}
 - {pin_num: '87', pin_signal: PTC15/UART4_TX/FB_AD24, label: 'J199[4]/BT_RX'}
 - {pin_num: '54', pin_signal: ADC0_SE9/ADC1_SE9/PTB1/I2C0_SDA/FTM1_CH1/RMII0_MDC/MII0_MDC/FTM1_QD_PHB, label: 'U13[11]/RMII0_MDC', identifier: RMII0_MDC}
 - {pin_num: '53', pin_signal: ADC0_SE8/ADC1_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/RMII0_MDIO/MII0_MDIO/FTM1_QD_PHA, label: 'U13[10]/RMII0_MDIO', identifier: RMII0_MDIO}
 - {pin_num: '50', pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0, label: 'U13[16]/RMII_RXCLK', identifier: EXTAL0;RMII_RXCLK}
 - {pin_num: '43', pin_signal: CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/I2C2_SDA/I2S0_TX_FS/FTM1_QD_PHB, label: 'U13[13]/RMII0_RXD_0', identifier: RMII0_RXD0}
 - {pin_num: '42', pin_signal: CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/I2C2_SCL/I2S0_TXD0/FTM1_QD_PHA, label: 'U13[12]/RMII0_RXD_1', identifier: RMII0_RXD1}
 - {pin_num: '39', pin_signal: PTA5/USB_CLKIN/FTM0_CH2/RMII0_RXER/MII0_RXER/CMP2_OUT/I2S0_TX_BCLK/JTAG_TRST_b, label: 'U13[17]/RMII0_RXER', identifier: RMII0_RXER}
 - {pin_num: '44', pin_signal: PTA14/SPI0_PCS0/UART0_TX/RMII0_CRS_DV/MII0_RXDV/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1, label: 'U13[15]/RMII0_CRS_DV', identifier: RMII0_CRS_DV}
 - {pin_num: '85', pin_signal: PTC13/UART4_CTS_b/FB_AD26, label: 'U8[9]', identifier: ACCEL_INT2}
 - {pin_num: '62', pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN, label: 'U7[4]/UART0_RX', identifier: DEBUG_UART_RX}
 - {pin_num: '63', pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b, label: 'U10[1]/UART0_TX', identifier: DEBUG_UART_TX}
 - {pin_num: '37', pin_signal: PTA3/UART0_RTS_b/FTM0_CH0/JTAG_TMS/SWD_DIO, label: 'J9[2]/SWD_DIO'}
 - {pin_num: '34', pin_signal: PTA0/UART0_CTS_b/UART0_COL_b/FTM0_CH5/JTAG_TCLK/SWD_CLK/EZP_CLK, label: 'J9[4]/SWD_CLK'}
 - {pin_num: '68', pin_signal: PTB22/SPI2_SOUT/FB_AD29/CMP2_OUT, label: 'D12[1]/LEDRGB_RED', identifier: LED_RED}
 - {pin_num: '67', pin_signal: PTB21/SPI2_SCK/FB_AD30/CMP1_OUT, label: 'D12[3]/LEDRGB_BLUE', identifier: LED_BLUE}
 - {pin_num: '13', pin_signal: VREGIN, label: VREGIN_K64}
 - {pin_num: '29', pin_signal: EXTAL32, label: 'Y3[2]/EXTAL32_RTC', identifier: ETAL32K}
 - {pin_num: '28', pin_signal: XTAL32, label: 'Y3[1]/XTAL32_RTC', identifier: XTAL32K}
 - {pin_num: '51', pin_signal: XTAL0/PTA19/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1, label: GND}
 - {pin_num: '30', pin_signal: VBAT, label: VBAT}
 - {pin_num: '8', pin_signal: VDD16, label: P3V3_K64F}
 - {pin_num: '22', pin_signal: VDDA, label: P3V3_K64F}
 - {pin_num: '12', pin_signal: VOUT33, label: VOUT33_K64}
 - {pin_num: '10', pin_signal: USB0_DP, label: 'J22[3]/K64_MICRO_USB_DP', identifier: USB_DP}
 - {pin_num: '11', pin_signal: USB0_DM, label: 'J22[2]/K64_MICRO_USB_DN', identifier: USB_DM}
 - {pin_num: '23', pin_signal: VREFH, label: VREFH}
 - {pin_num: '45', pin_signal: PTA15/SPI0_SCK/UART0_RX/RMII0_TXEN/MII0_TXEN/I2S0_RXD0, label: 'U13[19]/RMII0_TXEN', identifier: RMII0_TXEN}
 - {pin_num: '46', pin_signal: PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0/I2S0_RX_FS/I2S0_RXD1, label: 'U13[20]/RMII0_TXD0', identifier: RMII0_TXD0}
 - {pin_num: '47', pin_signal: ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1/I2S0_MCLK, label: 'U13[21]/RMII0_TXD1', identifier: RMII0_TXD1}
 - {pin_num: '24', pin_signal: VREFL, label: GND}
 - {pin_num: '9', pin_signal: VSS17, label: GND}
 - {pin_num: '40', pin_signal: VDD63, label: P3V3_K64F}
 - {pin_num: '25', pin_signal: VSSA, label: GND}
 - {pin_num: '41', pin_signal: VSS64, label: GND}
 - {pin_num: '48', pin_signal: VDD80, label: P3V3_K64F}
 - {pin_num: '49', pin_signal: VSS81, label: GND}
 - {pin_num: '61', pin_signal: VDD110, label: P3V3_K64F}
 - {pin_num: '75', pin_signal: VDD124, label: P3V3_K64F}
 - {pin_num: '89', pin_signal: VDD140, label: P3V3_K64F}
 - {pin_num: '60', pin_signal: VSS109, label: GND}
 - {pin_num: '74', pin_signal: VSS123, label: GND}
 - {pin_num: '88', pin_signal: VSS139, label: GND}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
	BOARD_InitPins();
	BOARD_InitDEBUG_UARTPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 BOARD_InitPins:
 - options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
 - pin_list:
 - {pin_num: '36', peripheral: TPIU, signal: SWO, pin_signal: PTA2/UART0_TX/FTM0_CH7/JTAG_TDO/TRACE_SWO/EZP_DO, drive_strength: low, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {
	/* Port A Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortD);

	/* PORTA2 (pin 36) is configured as TRACE_SWO */
	PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt7);
	PORT_SetPinMux(PORTD, 0U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, 1U, kPORT_MuxAlt4);
	PORT_SetPinMux(PORTD, 2U, kPORT_MuxAlt4);
	PORT_SetPinMux(PORTD, 3U, kPORT_MuxAlt4);

	PORTA->PCR[2] = ((PORTA->PCR[2]
			&
			/* Mask bits to zero which are setting */
			(~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK
					| PORT_PCR_ISF_MASK)))

	/* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
	 * corresponding PE field is set. */
	| PORT_PCR_PS(kPORT_PullDown)

	/* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
	| PORT_PCR_PE(kPORT_PullDisable)

	/* Drive Strength Enable: Low drive strength is configured on the corresponding pin, if pin
	 * is configured as a digital output. */
	| PORT_PCR_DSE(kPORT_LowDriveStrength));

	PORTD->PCR[0] = ((PORTD->PCR[0]
			&
			/* Mask bits to zero which are setting */
			(~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK
					| PORT_PCR_ISF_MASK)))

	/* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
	 * corresponding PE field is set. */
	| PORT_PCR_PS(kPORT_PullUp)

	/* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
	| PORT_PCR_PE(kPORT_PullUp)

	/* Drive Strength Enable: Low drive strength is configured on the corresponding pin, if pin
	 * is configured as a digital output. */
	| PORT_PCR_DSE(kPORT_LowDriveStrength));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 BOARD_InitButtonsPins:
 - options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
 - pin_list:
 - {pin_num: '78', peripheral: GPIOC, signal: 'GPIO, 6', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/I2S0_RX_BCLK/FB_AD9/I2S0_MCLK, identifier: SW2,
 direction: INPUT, gpio_interrupt: kPORT_InterruptFallingEdge, slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: up, pull_enable: enable,
 passive_filter: disable}
 - {pin_num: '38', peripheral: GPIOA, signal: 'GPIO, 4', pin_signal: PTA4/LLWU_P3/FTM0_CH1/NMI_b/EZP_CS_b, direction: INPUT, gpio_interrupt: kPORT_InterruptFallingEdge,
 slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitButtonsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitButtonsPins(void) {
	/* Port A Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortA);
	/* Port C Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortC);

	gpio_pin_config_t SW3_config = { .pinDirection = kGPIO_DigitalInput,
			.outputLogic = 0U };
	/* Initialize GPIO functionality on pin PTA4 (pin 38)  */
	GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_PIN, &SW3_config);

	gpio_pin_config_t SW2_config = { .pinDirection = kGPIO_DigitalInput,
			.outputLogic = 0U };
	/* Initialize GPIO functionality on pin PTC6 (pin 78)  */
	GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_PIN, &SW2_config);

	const port_pin_config_t SW3 = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as PTA4 */
	kPORT_MuxAsGpio,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTA4 (pin 38) is configured as PTA4 */
	PORT_SetPinConfig(BOARD_SW3_PORT, BOARD_SW3_PIN, &SW3);

	/* Interrupt configuration on PORTA4 (pin 38): Interrupt on falling edge */
	PORT_SetPinInterruptConfig(BOARD_SW3_PORT, BOARD_SW3_PIN,
			kPORT_InterruptFallingEdge);

	const port_pin_config_t SW2 = {/* Internal pull-up resistor is enabled */
	kPORT_PullUp,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as PTC6 */
	kPORT_MuxAsGpio,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTC6 (pin 78) is configured as PTC6 */
	PORT_SetPinConfig(BOARD_SW2_PORT, BOARD_SW2_PIN, &SW2);

	/* Interrupt configuration on PORTC6 (pin 78): Interrupt on falling edge */
	PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_PIN,
			kPORT_InterruptFallingEdge);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 BOARD_InitLEDsPins:
 - options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
 - pin_list:
 - {pin_num: '67', peripheral: GPIOB, signal: 'GPIO, 21', pin_signal: PTB21/SPI2_SCK/FB_AD30/CMP1_OUT, direction: OUTPUT, gpio_init_state: 'true', slew_rate: slow,
 open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '68', peripheral: GPIOB, signal: 'GPIO, 22', pin_signal: PTB22/SPI2_SOUT/FB_AD29/CMP2_OUT, direction: OUTPUT, gpio_init_state: 'true', slew_rate: slow,
 open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '33', peripheral: GPIOE, signal: 'GPIO, 26', pin_signal: PTE26/ENET_1588_CLKIN/UART4_CTS_b/RTC_CLKOUT/USB_CLKIN, direction: OUTPUT, gpio_init_state: 'true',
 slew_rate: slow, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLEDsPins(void) {
	/* Port B Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortB);
	/* Port E Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortE);

	gpio_pin_config_t LED_BLUE_config = { .pinDirection = kGPIO_DigitalOutput,
			.outputLogic = 1U };
	/* Initialize GPIO functionality on pin PTB21 (pin 67)  */
	GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, &LED_BLUE_config);

	gpio_pin_config_t LED_RED_config = { .pinDirection = kGPIO_DigitalOutput,
			.outputLogic = 1U };
	/* Initialize GPIO functionality on pin PTB22 (pin 68)  */
	GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, &LED_RED_config);

	gpio_pin_config_t LED_GREEN_config = { .pinDirection = kGPIO_DigitalOutput,
			.outputLogic = 1U };
	/* Initialize GPIO functionality on pin PTE26 (pin 33)  */
	GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, &LED_GREEN_config);

	const port_pin_config_t LED_BLUE = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Slow slew rate is configured */
	kPORT_SlowSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as PTB21 */
	kPORT_MuxAsGpio,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTB21 (pin 67) is configured as PTB21 */
	PORT_SetPinConfig(BOARD_LED_BLUE_PORT, BOARD_LED_BLUE_PIN, &LED_BLUE);

	const port_pin_config_t LED_RED = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Slow slew rate is configured */
	kPORT_SlowSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as PTB22 */
	kPORT_MuxAsGpio,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTB22 (pin 68) is configured as PTB22 */
	PORT_SetPinConfig(BOARD_LED_RED_PORT, BOARD_LED_RED_PIN, &LED_RED);

	const port_pin_config_t LED_GREEN = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Slow slew rate is configured */
	kPORT_SlowSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as PTE26 */
	kPORT_MuxAsGpio,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE26 (pin 33) is configured as PTE26 */
	PORT_SetPinConfig(BOARD_LED_GREEN_PORT, BOARD_LED_GREEN_PIN, &LED_GREEN);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 BOARD_InitDEBUG_UARTPins:
 - options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
 - pin_list:
 - {pin_num: '63', peripheral: UART0, signal: TX, pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b, direction: OUTPUT, slew_rate: fast, open_drain: disable,
 drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '62', peripheral: UART0, signal: RX, pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN, slew_rate: fast, open_drain: disable, drive_strength: low,
 pull_select: down, pull_enable: disable, passive_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitDEBUG_UARTPins(void) {
	/* Port B Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortB);

	const port_pin_config_t DEBUG_UART_RX = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as UART0_RX */
	kPORT_MuxAlt3,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTB16 (pin 62) is configured as UART0_RX */
	PORT_SetPinConfig(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN,
			&DEBUG_UART_RX);

	const port_pin_config_t DEBUG_UART_TX = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as UART0_TX */
	kPORT_MuxAlt3,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTB17 (pin 63) is configured as UART0_TX */
	PORT_SetPinConfig(BOARD_DEBUG_UART_TX_PORT, BOARD_DEBUG_UART_TX_PIN,
			&DEBUG_UART_TX);

	SIM->SOPT5 = ((SIM->SOPT5 &
	/* Mask bits to zero which are setting */
	(~(SIM_SOPT5_UART0TXSRC_MASK)))

	/* UART 0 transmit data source select: UART0_TX pin. */
	| SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 BOARD_InitOSCPins:
 - options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
 - pin_list:
 - {pin_num: '50', peripheral: OSC, signal: EXTAL0, pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0, identifier: EXTAL0, slew_rate: no_init, open_drain: no_init, drive_strength: no_init,
 pull_select: no_init, pull_enable: no_init, passive_filter: no_init}
 - {pin_num: '29', peripheral: RTC, signal: EXTAL32, pin_signal: EXTAL32}
 - {pin_num: '28', peripheral: RTC, signal: XTAL32, pin_signal: XTAL32}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitOSCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitOSCPins(void) {
	/* Port A Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortA);

	/* PORTA18 (pin 50) is configured as EXTAL0 */
	PORT_SetPinMux(BOARD_EXTAL0_PORT, BOARD_EXTAL0_PIN,
			kPORT_PinDisabledOrAnalog);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 BOARD_InitACCELPins:
 - options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
 - pin_list:
 - {pin_num: '32', peripheral: I2C0, signal: SDA, pin_signal: ADC0_SE18/PTE25/UART4_RX/I2C0_SDA/EWM_IN, slew_rate: fast, open_drain: enable, drive_strength: low,
 pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '31', peripheral: I2C0, signal: SCL, pin_signal: ADC0_SE17/PTE24/UART4_TX/I2C0_SCL/EWM_OUT_b, slew_rate: fast, open_drain: enable, drive_strength: low,
 pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '78', peripheral: GPIOC, signal: 'GPIO, 6', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/I2S0_RX_BCLK/FB_AD9/I2S0_MCLK, identifier: ACCEL_INT1,
 direction: INPUT, slew_rate: fast, open_drain: enable, drive_strength: low, pull_select: up, pull_enable: enable, passive_filter: disable}
 - {pin_num: '85', peripheral: GPIOC, signal: 'GPIO, 13', pin_signal: PTC13/UART4_CTS_b/FB_AD26, direction: INPUT, slew_rate: fast, open_drain: enable, drive_strength: low,
 pull_select: up, pull_enable: enable, passive_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitACCELPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitACCELPins(void) {
	/* Port C Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortC);
	/* Port E Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortE);

	gpio_pin_config_t ACCEL_INT1_config = { .pinDirection = kGPIO_DigitalInput,
			.outputLogic = 0U };
	/* Initialize GPIO functionality on pin PTC6 (pin 78)  */
	GPIO_PinInit(BOARD_ACCEL_INT1_GPIO, BOARD_ACCEL_INT1_PIN,
			&ACCEL_INT1_config);

	gpio_pin_config_t ACCEL_INT2_config = { .pinDirection = kGPIO_DigitalInput,
			.outputLogic = 0U };
	/* Initialize GPIO functionality on pin PTC13 (pin 85)  */
	GPIO_PinInit(BOARD_ACCEL_INT2_GPIO, BOARD_ACCEL_INT2_PIN,
			&ACCEL_INT2_config);

	const port_pin_config_t ACCEL_INT2 = {/* Internal pull-up resistor is enabled */
	kPORT_PullUp,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is enabled */
	kPORT_OpenDrainEnable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as PTC13 */
	kPORT_MuxAsGpio,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTC13 (pin 85) is configured as PTC13 */
	PORT_SetPinConfig(BOARD_ACCEL_INT2_PORT, BOARD_ACCEL_INT2_PIN, &ACCEL_INT2);

	const port_pin_config_t ACCEL_INT1 = {/* Internal pull-up resistor is enabled */
	kPORT_PullUp,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is enabled */
	kPORT_OpenDrainEnable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as PTC6 */
	kPORT_MuxAsGpio,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTC6 (pin 78) is configured as PTC6 */
	PORT_SetPinConfig(BOARD_ACCEL_INT1_PORT, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1);

	const port_pin_config_t ACCEL_SCL = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
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
	PORT_SetPinConfig(BOARD_ACCEL_SCL_PORT, BOARD_ACCEL_SCL_PIN, &ACCEL_SCL);

	const port_pin_config_t ACCEL_SDA = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
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
	PORT_SetPinConfig(BOARD_ACCEL_SDA_PORT, BOARD_ACCEL_SDA_PIN, &ACCEL_SDA);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 BOARD_InitENETPins:
 - options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
 - pin_list:
 - {pin_num: '54', peripheral: ENET, signal: RMII_MDC, pin_signal: ADC0_SE9/ADC1_SE9/PTB1/I2C0_SDA/FTM1_CH1/RMII0_MDC/MII0_MDC/FTM1_QD_PHB, slew_rate: fast, open_drain: disable,
 drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '53', peripheral: ENET, signal: RMII_MDIO, pin_signal: ADC0_SE8/ADC1_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/RMII0_MDIO/MII0_MDIO/FTM1_QD_PHA, slew_rate: fast,
 open_drain: enable, drive_strength: low, pull_select: up, pull_enable: enable, passive_filter: disable}
 - {pin_num: '43', peripheral: ENET, signal: RMII_RXD0, pin_signal: CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/I2C2_SDA/I2S0_TX_FS/FTM1_QD_PHB,
 slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '42', peripheral: ENET, signal: RMII_RXD1, pin_signal: CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/I2C2_SCL/I2S0_TXD0/FTM1_QD_PHA, slew_rate: fast,
 open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '39', peripheral: ENET, signal: RMII_RXER, pin_signal: PTA5/USB_CLKIN/FTM0_CH2/RMII0_RXER/MII0_RXER/CMP2_OUT/I2S0_TX_BCLK/JTAG_TRST_b, slew_rate: fast,
 open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '46', peripheral: ENET, signal: RMII_TXD0, pin_signal: PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0/I2S0_RX_FS/I2S0_RXD1, slew_rate: fast,
 open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '47', peripheral: ENET, signal: RMII_TXD1, pin_signal: ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1/I2S0_MCLK, slew_rate: fast, open_drain: disable,
 drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '45', peripheral: ENET, signal: RMII_TXEN, pin_signal: PTA15/SPI0_SCK/UART0_RX/RMII0_TXEN/MII0_TXEN/I2S0_RXD0, slew_rate: fast, open_drain: disable,
 drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '44', peripheral: ENET, signal: RMII_CRS_DV, pin_signal: PTA14/SPI0_PCS0/UART0_TX/RMII0_CRS_DV/MII0_RXDV/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1, slew_rate: fast,
 open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '50', peripheral: ENET, signal: RMII_CLKIN, pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0, identifier: RMII_RXCLK, slew_rate: fast, open_drain: disable,
 drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitENETPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitENETPins(void) {
	/* Port A Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortA);
	/* Port B Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortB);

	const port_pin_config_t RMII0_RXD1 = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as RMII0_RXD1 */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTA12 (pin 42) is configured as RMII0_RXD1 */
	PORT_SetPinConfig(BOARD_RMII0_RXD1_PORT, BOARD_RMII0_RXD1_PIN, &RMII0_RXD1);

	const port_pin_config_t RMII0_RXD0 = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as RMII0_RXD0 */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTA13 (pin 43) is configured as RMII0_RXD0 */
	PORT_SetPinConfig(BOARD_RMII0_RXD0_PORT, BOARD_RMII0_RXD0_PIN, &RMII0_RXD0);

	const port_pin_config_t RMII0_CRS_DV = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as RMII0_CRS_DV */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTA14 (pin 44) is configured as RMII0_CRS_DV */
	PORT_SetPinConfig(BOARD_RMII0_CRS_DV_PORT, BOARD_RMII0_CRS_DV_PIN,
			&RMII0_CRS_DV);

	const port_pin_config_t RMII0_TXEN = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as RMII0_TXEN */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTA15 (pin 45) is configured as RMII0_TXEN */
	PORT_SetPinConfig(BOARD_RMII0_TXEN_PORT, BOARD_RMII0_TXEN_PIN, &RMII0_TXEN);

	const port_pin_config_t RMII0_TXD0 = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as RMII0_TXD0 */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTA16 (pin 46) is configured as RMII0_TXD0 */
	PORT_SetPinConfig(BOARD_RMII0_TXD0_PORT, BOARD_RMII0_TXD0_PIN, &RMII0_TXD0);

	const port_pin_config_t RMII0_TXD1 = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as RMII0_TXD1 */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTA17 (pin 47) is configured as RMII0_TXD1 */
	PORT_SetPinConfig(BOARD_RMII0_TXD1_PORT, BOARD_RMII0_TXD1_PIN, &RMII0_TXD1);

	const port_pin_config_t RMII_RXCLK = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as EXTAL0 */
	kPORT_PinDisabledOrAnalog,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTA18 (pin 50) is configured as EXTAL0 */
	PORT_SetPinConfig(BOARD_RMII_RXCLK_PORT, BOARD_RMII_RXCLK_PIN, &RMII_RXCLK);

	const port_pin_config_t RMII0_RXER = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as RMII0_RXER */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTA5 (pin 39) is configured as RMII0_RXER */
	PORT_SetPinConfig(BOARD_RMII0_RXER_PORT, BOARD_RMII0_RXER_PIN, &RMII0_RXER);

	const port_pin_config_t RMII0_MDIO = {/* Internal pull-up resistor is enabled */
	kPORT_PullUp,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is enabled */
	kPORT_OpenDrainEnable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as RMII0_MDIO */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTB0 (pin 53) is configured as RMII0_MDIO */
	PORT_SetPinConfig(BOARD_RMII0_MDIO_PORT, BOARD_RMII0_MDIO_PIN, &RMII0_MDIO);

	const port_pin_config_t RMII0_MDC = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as RMII0_MDC */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTB1 (pin 54) is configured as RMII0_MDC */
	PORT_SetPinConfig(BOARD_RMII0_MDC_PORT, BOARD_RMII0_MDC_PIN, &RMII0_MDC);

	SIM->SOPT2 = ((SIM->SOPT2 &
	/* Mask bits to zero which are setting */
	(~(SIM_SOPT2_RMIISRC_MASK)))

	/* RMII clock source select: EXTAL clock. */
	| SIM_SOPT2_RMIISRC(SOPT2_RMIISRC_EXTAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 BOARD_InitSDHCPins:
 - options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
 - pin_list:
 - {pin_num: '1', peripheral: SDHC, signal: 'DATA, 1', pin_signal: ADC1_SE4a/PTE0/SPI1_PCS1/UART1_TX/SDHC0_D1/TRACE_CLKOUT/I2C1_SDA/RTC_CLKOUT, slew_rate: fast,
 open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '2', peripheral: SDHC, signal: 'DATA, 0', pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/SDHC0_D0/TRACE_D3/I2C1_SCL/SPI1_SIN, slew_rate: fast,
 open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '3', peripheral: SDHC, signal: DCLK, pin_signal: ADC0_DP2/ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b/SDHC0_DCLK/TRACE_D2, slew_rate: fast, open_drain: disable,
 drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '4', peripheral: SDHC, signal: CMD, pin_signal: ADC0_DM2/ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SDHC0_CMD/TRACE_D1/SPI1_SOUT, slew_rate: fast, open_drain: disable,
 drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '5', peripheral: SDHC, signal: 'DATA, 3', pin_signal: PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/SDHC0_D3/TRACE_D0, slew_rate: fast, open_drain: disable, drive_strength: low,
 pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '6', peripheral: SDHC, signal: 'DATA, 2', pin_signal: PTE5/SPI1_PCS2/UART3_RX/SDHC0_D2/FTM3_CH0, slew_rate: fast, open_drain: disable, drive_strength: low,
 pull_select: down, pull_enable: disable, passive_filter: disable}
 - {pin_num: '7', peripheral: GPIOE, signal: 'GPIO, 6', pin_signal: PTE6/SPI1_PCS3/UART3_CTS_b/I2S0_MCLK/FTM3_CH1/USB_SOF_OUT, direction: INPUT, slew_rate: slow,
 open_drain: disable, drive_strength: low, pull_select: down, pull_enable: enable, passive_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSDHCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitSDHCPins(void) {
	/* Port E Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortE);

	gpio_pin_config_t SDHC_CD_config = { .pinDirection = kGPIO_DigitalInput,
			.outputLogic = 0U };
	/* Initialize GPIO functionality on pin PTE6 (pin 7)  */
	GPIO_PinInit(BOARD_SDHC_CD_GPIO, BOARD_SDHC_CD_PIN, &SDHC_CD_config);

	const port_pin_config_t SDHC0_D1 = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as SDHC0_D1 */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE0 (pin 1) is configured as SDHC0_D1 */
	PORT_SetPinConfig(BOARD_SDHC0_D1_PORT, BOARD_SDHC0_D1_PIN, &SDHC0_D1);

	const port_pin_config_t SDHC0_D0 = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as SDHC0_D0 */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE1 (pin 2) is configured as SDHC0_D0 */
	PORT_SetPinConfig(BOARD_SDHC0_D0_PORT, BOARD_SDHC0_D0_PIN, &SDHC0_D0);

	const port_pin_config_t SDHC0_DCLK = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as SDHC0_DCLK */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE2 (pin 3) is configured as SDHC0_DCLK */
	PORT_SetPinConfig(BOARD_SDHC0_DCLK_PORT, BOARD_SDHC0_DCLK_PIN, &SDHC0_DCLK);

	const port_pin_config_t SDHC0_CMD = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as SDHC0_CMD */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE3 (pin 4) is configured as SDHC0_CMD */
	PORT_SetPinConfig(BOARD_SDHC0_CMD_PORT, BOARD_SDHC0_CMD_PIN, &SDHC0_CMD);

	const port_pin_config_t SDHC0_D3 = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as SDHC0_D3 */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE4 (pin 5) is configured as SDHC0_D3 */
	PORT_SetPinConfig(BOARD_SDHC0_D3_PORT, BOARD_SDHC0_D3_PIN, &SDHC0_D3);

	const port_pin_config_t SDHC0_D2 = {/* Internal pull-up/down resistor is disabled */
	kPORT_PullDisable,
	/* Fast slew rate is configured */
	kPORT_FastSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as SDHC0_D2 */
	kPORT_MuxAlt4,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE5 (pin 6) is configured as SDHC0_D2 */
	PORT_SetPinConfig(BOARD_SDHC0_D2_PORT, BOARD_SDHC0_D2_PIN, &SDHC0_D2);

	const port_pin_config_t SDHC_CD = {/* Internal pull-down resistor is enabled */
	kPORT_PullDown,
	/* Slow slew rate is configured */
	kPORT_SlowSlewRate,
	/* Passive filter is disabled */
	kPORT_PassiveFilterDisable,
	/* Open drain is disabled */
	kPORT_OpenDrainDisable,
	/* Low drive strength is configured */
	kPORT_LowDriveStrength,
	/* Pin is configured as PTE6 */
	kPORT_MuxAsGpio,
	/* Pin Control Register fields [15:0] are not locked */
	kPORT_UnlockRegister };
	/* PORTE6 (pin 7) is configured as PTE6 */
	PORT_SetPinConfig(BOARD_SDHC_CD_PORT, BOARD_SDHC_CD_PIN, &SDHC_CD);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
 BOARD_InitUSBPins:
 - options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
 - pin_list:
 - {pin_num: '10', peripheral: USB0, signal: DP, pin_signal: USB0_DP}
 - {pin_num: '11', peripheral: USB0, signal: DM, pin_signal: USB0_DM}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitUSBPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitUSBPins(void) {
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
