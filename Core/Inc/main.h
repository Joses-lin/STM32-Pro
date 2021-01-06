/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#define DB02_Pin GPIO_PIN_2
#define DB02_GPIO_Port GPIOE
#define DB03_Pin GPIO_PIN_3
#define DB03_GPIO_Port GPIOE
#define DB04_Pin GPIO_PIN_4
#define DB04_GPIO_Port GPIOE
#define DB05_Pin GPIO_PIN_5
#define DB05_GPIO_Port GPIOE
#define DB06_Pin GPIO_PIN_6
#define DB06_GPIO_Port GPIOE
#define Key_temper_Pin GPIO_PIN_13
#define Key_temper_GPIO_Port GPIOC
#define Wakeup_Pin GPIO_PIN_0
#define Wakeup_GPIO_Port GPIOA
#define Key2_Pin GPIO_PIN_4
#define Key2_GPIO_Port GPIOC
#define RMII_INT_Pin GPIO_PIN_5
#define RMII_INT_GPIO_Port GPIOC
#define DB07_Pin GPIO_PIN_7
#define DB07_GPIO_Port GPIOE
#define DB08_Pin GPIO_PIN_8
#define DB08_GPIO_Port GPIOE
#define DB09_Pin GPIO_PIN_9
#define DB09_GPIO_Port GPIOE
#define DB10_Pin GPIO_PIN_10
#define DB10_GPIO_Port GPIOE
#define DB11_Pin GPIO_PIN_11
#define DB11_GPIO_Port GPIOE
#define DB12_Pin GPIO_PIN_12
#define DB12_GPIO_Port GPIOE
#define DB13_Pin GPIO_PIN_13
#define DB13_GPIO_Port GPIOE
#define DB14_Pin GPIO_PIN_14
#define DB14_GPIO_Port GPIOE
#define DB15_Pin GPIO_PIN_15
#define DB15_GPIO_Port GPIOE
#define Key_Pin GPIO_PIN_10
#define Key_GPIO_Port GPIOB
#define LCD_WR_Pin GPIO_PIN_14
#define LCD_WR_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_11
#define SD_CS_GPIO_Port GPIOD
#define LCD_RS_Pin GPIO_PIN_13
#define LCD_RS_GPIO_Port GPIOD
#define LCD_WRError_Pin GPIO_PIN_14
#define LCD_WRError_GPIO_Port GPIOD
#define LCD_RD_Pin GPIO_PIN_15
#define LCD_RD_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_8
#define LCD_CS_GPIO_Port GPIOC
#define TP_CS_Pin GPIO_PIN_9
#define TP_CS_GPIO_Port GPIOC
#define MCO_Pin GPIO_PIN_8
#define MCO_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOD
#define LED3_Pin GPIO_PIN_4
#define LED3_GPIO_Port GPIOD
#define LED4_Pin GPIO_PIN_7
#define LED4_GPIO_Port GPIOD
#define USB_PWR_Pin GPIO_PIN_8
#define USB_PWR_GPIO_Port GPIOB
#define F_CS_Pin GPIO_PIN_9
#define F_CS_GPIO_Port GPIOB
#define DB00_Pin GPIO_PIN_0
#define DB00_GPIO_Port GPIOE
#define DB01_Pin GPIO_PIN_1
#define DB01_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

#define Set_Cs  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
#define Clr_Cs  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
 

#define Set_nWr  HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);
#define Clr_nWr  HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);

#define Set_Rs   HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
#define Clr_Rs   HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);

#define Set_nRd  HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET);
#define Clr_nRd  HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_RESET);

#define LCD_Write(LCD_DATA)  DB07_GPIO_Port->ODR = LCD_DATA;
#define LCD_Read()           DB07_GPIO_Port->IDR;

#define TP_CS()   HAL_GPIO_WritePin(TP_CS_GPIO_Port, TP_CS_Pin, GPIO_PIN_RESET)
#define TP_DCS()  HAL_GPIO_WritePin(TP_CS_GPIO_Port, TP_CS_Pin, GPIO_PIN_SET)


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
