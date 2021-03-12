/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DEBUG 1

#if DEBUG
  #define D(x)  x
#else
  #define D(x)
#endif


typedef uint8_t			u8;
typedef uint16_t		u16;
typedef uint32_t		u32;
typedef uint64_t		u64;
typedef unsigned int 	uint;

typedef int8_t		s8;
typedef int16_t		s16;
typedef int32_t		s32;


typedef union{
	struct{
		u8 isIrqTx:		1;
		u8 isIrqRx: 	1;
		u8 isIrqIdle:	3;
	};
	u8 regIrq;
}IrqFlags;

u8 waitRx(char* waitStr, IrqFlags* pFlags, u16 pause, u16 timeout);
u8 waitTx(char* waitStr, IrqFlags* pFlags, u16 pause, u16 timeout);
u8 waitIdle(char* waitStr, IrqFlags* pFlags, u16 pause, u16 timeout);
u8 waitIdleCnt(char* waitStr, IrqFlags* pFlags, u8 cnt, u16 pause, u16 timeout);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
