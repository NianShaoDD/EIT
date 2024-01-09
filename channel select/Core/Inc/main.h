/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define A2_Pin GPIO_PIN_0
#define A2_GPIO_Port GPIOD
#define A3_Pin GPIO_PIN_1
#define A3_GPIO_Port GPIOD
#define B3_Pin GPIO_PIN_10
#define B3_GPIO_Port GPIOE
#define B2_Pin GPIO_PIN_9
#define B2_GPIO_Port GPIOE
#define LED_Pin GPIO_PIN_11
#define LED_GPIO_Port GPIOE
#define A1_Pin GPIO_PIN_15
#define A1_GPIO_Port GPIOD
#define A0_Pin GPIO_PIN_14
#define A0_GPIO_Port GPIOD
#define B1_Pin GPIO_PIN_8
#define B1_GPIO_Port GPIOE
#define B0_Pin GPIO_PIN_7
#define B0_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
