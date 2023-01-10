/*
 * peripherals.h
 *
 *  Created on: Jan 5, 2023
 *      Author: sreehari
 */
//#include <peripheral.c>

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_
#endif /* PERIPHERALS_H_ */

void BOARD_InitI2CPeripherals(void);
void BOARD_InitFTMPeripheral(void);
void BOARD_InitUARTInterrupt(void);
void BOARD_InitGPIOPeripheral(void);


/*I2C Configuration***********************************************************/
#define I2C_MASTER_CLK_SRC          I2C0_CLK_SRC
#define I2C_MASTER_CLK_FREQ         CLOCK_GetFreq(I2C0_CLK_SRC)
#define I2C_MASTER_BASEADDR 		I2C0
#define DMA_REQUEST_SRC             kDmaRequestMux0I2C0
#define I2C_DMAMUX_BASEADDR			DMAMUX0
#define I2C_DMA_BASEADDR		    DMA0
#define I2C_DMA_CHANNEL             0U

#define I2C_MASTER_SLAVE_ADDR		0x7EU
#define I2C_BAUDRATE               	100000U
#define I2C_FRAME_WIDTH            	15U
/*****************************************************************************/



