/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define delayUS_ASM(us) do {						   	   \
	asm volatile ("MOV R0,%[loops]\n				   	   \
				   1: \n								   \
			       SUB R0, #1\n						   	   \
				   CMP R0, #0\n						   	   \
				   BNE 1b \t"						   	   \
				   : : [loops] "r" (6*us) : "memory" \
				 );									       \
} while(0)
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void ST7789_TransmitSPI(uint8_t *data, uint8_t dataSize);
void setPinToInput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void setPinToOutput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ST7789_SCK_Pin GPIO_PIN_5
#define ST7789_SCK_GPIO_Port GPIOA
#define ST7789_MOSI_Pin GPIO_PIN_7
#define ST7789_MOSI_GPIO_Port GPIOA
#define ST7789_RES_Pin GPIO_PIN_0
#define ST7789_RES_GPIO_Port GPIOB
#define ST7789_DC_Pin GPIO_PIN_1
#define ST7789_DC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
