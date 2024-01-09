#ifndef __CHANNEL_H
#define __CHANNEL_H
#include "stdint.h"

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

void Channel_Init(void);
void A_Addset(uint8_t Byte);
void B_Addset(uint8_t Byte);


#endif
