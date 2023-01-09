/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS kernel includes. */
#include "../Peripherals/peripheral.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "fsl_i2c_edma.h"
#include "fsl_dmamux.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#include "clock_config.h"
#include "board.h"
#include "pin_mux.h"
/**
 * Status Flags
 */
#define IDLE 0
#define STOPPED 1
#define RUNNING 2
#define PAUSED 3
/***************************************/
/**
 * Colour Queue Data Format
 */
#define DATA_FLAG 0
#define RED_VALUE 1
#define GREEN_VALUE 2
#define BLUE_VALUE 3
/***************************************/
/**
 * Configuration Queue Data Format
 */
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
/***************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
//i2c_master_edma_handle_t g_m_dma_handle;
//edma_handle_t edmaHandle;
/* Task priorities. */
#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void pattern_task(void *pvParameters);
static void master_ui_task(void *pvParameters);
static void slave_ui_task(void *pvParameters);
void delay(float second)
{
	second = second * (42000000 / 20);
	while (second)
		second--;
}
//static void i2c_master_callback(I2C_Type *base,
//		i2c_master_edma_handle_t *handle, status_t status, void *userData)
//{
//	/* Signal transfer success when received success status. */
//	PRINTF("\r\nI2C Transfer Complete\r\n");
//}

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */

static QueueHandle_t config_queue = NULL;
static QueueHandle_t color_queue = NULL;
//i2c_master_edma_handle_t g_m_dma_handle;
//edma_handle_t edmaHandle;
//uint8_t g_master_txBuff[I2C_FRAME_WIDTH] = "MASTER";

char con_q_vals[15][30] =
{ "Refresh Rate", "RGB Scheme", "Red Start Value", "Green Start Value",
		"Blue Start Value", "Red End Value", "Green End Value",
		"Blue End Value", "Red Resolution Value", "Green Resolution Value",
		"Blue Resolution Value", "Change Rate", "Mode", "Cycles" };
char col_q_vals[4][30] =
{ "Data Flag", "Red Value", "Blue Value", "Green Value" };
char master_handshake[10] = "MASTER";
char slave_handshake[10] = "SLAVE";

int main(void)
{
	/* Init board hardware. */
//	i2c_master_config_t masterConfig;
//	uint32_t sourceClock;
//	i2c_master_transfer_t masterXfer;
//	edma_config_t config;
//	uint8_t master_mode = 1;
	config_queue = xQueueCreate(1, sizeof(int) * 15);
	color_queue = xQueueCreate(1, sizeof(int) * 4);
	int master_mode =1;

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();
	//BOARD_InitI2CPeripherals();

	vQueueAddToRegistry(config_queue, "Configuration Queue");
	vQueueAddToRegistry(color_queue, "Color Value Queue");
	if (master_mode)
	{
//		DMAMUX_Init(I2C_DMAMUX_BASEADDR);
//		EDMA_GetDefaultConfig(&config);
//		EDMA_Init(I2C_DMA_BASEADDR, &config);
//		I2C_MasterGetDefaultConfig(&masterConfig);
//		masterConfig.baudRate_Bps = I2C_BAUDRATE;
//		sourceClock = I2C_MASTER_CLK_FREQ;
//		I2C_MasterInit(I2C_MASTER_BASEADDR, &masterConfig, sourceClock);
//		memset(&g_m_dma_handle, 0, sizeof(g_m_dma_handle));
//		memset(&masterXfer, 0, sizeof(masterXfer));
//		//uint8_t g_master_txBuff[I2C_FRAME_WIDTH] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
//		uint8_t deviceAddress = 0x01U;
//		masterXfer.slaveAddress = I2C_MASTER_SLAVE_ADDR;
//		masterXfer.direction = kI2C_Write;
//		masterXfer.subaddress = (uint32_t) deviceAddress;
//		masterXfer.subaddressSize = 1;
//		masterXfer.data = g_master_txBuff;
//		masterXfer.dataSize = I2C_FRAME_WIDTH;
//		masterXfer.flags = kI2C_TransferDefaultFlag;
//		DMAMUX_SetSource(I2C_DMAMUX_BASEADDR, I2C_DMA_CHANNEL, DMA_REQUEST_SRC);
//		EDMA_CreateHandle(&edmaHandle, I2C_DMA_BASEADDR, I2C_DMA_CHANNEL);
//		DMAMUX_EnableChannel(I2C_DMAMUX_BASEADDR, I2C_DMA_CHANNEL);
//
//		I2C_MasterCreateEDMAHandle(I2C_MASTER_BASEADDR, &g_m_dma_handle,
//				i2c_master_callback, NULL, &edmaHandle);
////
		if (xTaskCreate(master_ui_task, "User Interface",
		configMINIMAL_STACK_SIZE + 100,
		NULL, hello_task_PRIORITY, NULL) !=
		pdPASS)
		{
			PRINTF("Task creation failed!.\r\n");
			while (1)
				;
		}
	}
	else
	{
		if (xTaskCreate(slave_ui_task, "User Interface",
		configMINIMAL_STACK_SIZE + 100,
		NULL, hello_task_PRIORITY, NULL) !=
		pdPASS)
		{
			PRINTF("Task creation failed!.\r\n");
			while (1)
				;
		}
	}

	if (xTaskCreate(pattern_task, "Pattern Generator",
	configMINIMAL_STACK_SIZE + 100, NULL, hello_task_PRIORITY, NULL) !=
	pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	vTaskStartScheduler();
	for (;;)
		;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void slave_ui_task(void *pvParameters)
{
	PRINTF("Slave\r\n");
}
static void master_ui_task(void *pvParameters)
{
	int config_arr[] =
	{ 1000, 0, 0, 0, 0, 7, 7, 3, 1, 1, 1, 100, 1, 2 };
	int color_arr[4];
	int status = RUNNING;
	for (;;)
	{
		//PRINTF("\e[1;1H\e[2J");
		PRINTF("User Interface\r\n");
		PRINTF("\t\tMulticolor LED Controller\n");
		PRINTF("Device Mode\t\t: Master\r\n");
		PRINTF("Slave Status\t\t: Online\r\n\n");
		PRINTF("Current Configuration:-\r\n");
		PRINTF("Refresh Rate\t\t: %d Hz\r\n", config_arr[REFRESH_RATE]);
		PRINTF("Start Color\t\t: %d %d %d True color\r\n", config_arr[2],
				config_arr[3], config_arr[4]);
		PRINTF("End Color\t\t: %d %d %d True color\r\n", config_arr[5],
				config_arr[6], config_arr[7]);
		PRINTF("Color Change Rate\t: %d ms\r\n", config_arr[11] * 10);
		PRINTF("Resolution \t\t: %d %d %d\r\n", config_arr[8], config_arr[9],
				config_arr[10]);
		xQueueSendToFront(config_queue, config_arr, 10);
		while (status == RUNNING)
			if (xQueueReceive(color_queue, color_arr, 0) == pdPASS)
			{
				PRINTF("\rCurrent Color\t\t:%d %d %d True color", color_arr[1],
						color_arr[2], color_arr[3]);
			}
		//vTaskSuspend(NULL);
	}
}
static void pattern_task(void *pvParameters)
{
	int config_arr[15];
	int color_arr[4];
	int i, j, k, cur_red, cur_green, cur_blue;
	for (;;)
	{
		//PRINTF("Pattern generator\r\n");
		if (xQueueReceive(config_queue, config_arr, 0) == pdPASS)
		{
			color_arr[DATA_FLAG] = 1;
			color_arr[RED_VALUE] = config_arr[RED_START_VALUE];
			color_arr[GREEN_VALUE] = config_arr[GREEN_START_VALUE];
			color_arr[BLUE_VALUE] = config_arr[BLUE_START_VALUE];
			for (i = 0; +i <= config_arr[RED_END_VALUE]; i +=
					config_arr[RED_RESOLUTION_VALUE])
			{
				cur_red = config_arr[RED_START_VALUE] + i;
				for (j = 0;
						(config_arr[GREEN_START_VALUE] + j)
								<= config_arr[GREEN_END_VALUE]; j +=
								config_arr[GREEN_RESOLUTION_VALUE])
				{
					cur_green = config_arr[GREEN_START_VALUE] + j;
					for (k = 0;
							(config_arr[BLUE_START_VALUE] + k)
									<= config_arr[BLUE_END_VALUE]; k +=
									config_arr[BLUE_RESOLUTION_VALUE])
					{
						cur_blue = config_arr[BLUE_START_VALUE] + k;
						color_arr[DATA_FLAG] = 1;
						color_arr[RED_VALUE] = cur_red;
						color_arr[GREEN_VALUE] = cur_green;
						color_arr[BLUE_VALUE] = cur_blue;
						while (1)
						{

							if (xQueueSendToFront(color_queue, color_arr,
									0) == pdPASS)
							{
								break;
							}
						}
						delay(0.01 * config_arr[CHANGE_RATE]);
						if (config_arr[BLUE_RESOLUTION_VALUE] == 0)
							break;
					}
					if (config_arr[GREEN_RESOLUTION_VALUE] == 0)
						break;
				}
				if (config_arr[RED_RESOLUTION_VALUE] == 0)
					break;
			}
		}
		//vTaskSuspend(NULL);
	}
}

//status_t Handshake(void)
//{
//	masterXfer.direction = kI2C_Write;
//	status_t i2c_status = I2C_MasterTransferEDMA(I2C_MASTER_BASEADDR,
//			&g_m_dma_handle, &masterXfer);
//	PRINTF("\r\nI2C Transfer Status: %d\r\n", i2c_status);
//}
