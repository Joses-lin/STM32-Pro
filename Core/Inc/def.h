#ifndef _def_
#define _def_
    #define LED1_On     HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
    #define LED1_Off    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
    #define LED2_On     HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)
    #define LED2_Off    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
    #define LED3_On     HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET)
    #define LED3_Off    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET)
    #define LED4_On     HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET)
    #define LED4_Off    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET)
    #define LED1_Toggle HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)
    #define LED2_Toggle HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin)
    #define LED3_Toggle HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin)
    #define LED4_Toggle HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin)
#endif