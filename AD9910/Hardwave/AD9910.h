#ifndef __AD9910_H__
#define __AD9910_H__
#include "gpio.h"
#define AD9910_SDIO_Pin GPIO_PIN_1
#define AD9910_SDIO_GPIO_Port GPIOJ
#define MAS_REST_Pin GPIO_PIN_5
#define MAS_REST_GPIO_Port GPIOJ
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOB
#define SCLK_Pin GPIO_PIN_2
#define SCLK_GPIO_Port GPIOJ
#define CS_Pin GPIO_PIN_3
#define CS_GPIO_Port GPIOJ
#define UP_DAT_Pin GPIO_PIN_4
#define UP_DAT_GPIO_Port GPIOJ

#define AD9910_SDIO_LOW() HAL_GPIO_WritePin(AD9910_SDIO_GPIO_Port, AD9910_SDIO_Pin, GPIO_PIN_RESET)
#define AD9910_SDIO_HIGH() HAL_GPIO_WritePin(AD9910_SDIO_GPIO_Port, AD9910_SDIO_Pin, GPIO_PIN_SET)
#define SCLK_LOW() HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET)
#define SCLK_HIGH() HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET)
#define CS_LOW() HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)
#define CS_HIGH() HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)
#define UP_DAT_LOW() HAL_GPIO_WritePin(UP_DAT_GPIO_Port, UP_DAT_Pin, GPIO_PIN_RESET)
#define UP_DAT_HIGH() HAL_GPIO_WritePin(UP_DAT_GPIO_Port, UP_DAT_Pin, GPIO_PIN_SET)
#define MAS_REST_LOW() HAL_GPIO_WritePin(MAS_REST_GPIO_Port, MAS_REST_Pin, GPIO_PIN_RESET)
#define MAS_REST_HIGH() HAL_GPIO_WritePin(MAS_REST_GPIO_Port, MAS_REST_Pin, GPIO_PIN_SET)

#define uchar unsigned char
#define uint  unsigned int	
#define ulong  unsigned long int						



void AD9110_IOInit(void);
void Init_ad9910(void);
void Freq_convert(ulong Freq);										//写频率
void txd_8bit(uchar txdat);
void Txcfr(void);
void Write_Amplitude(uint Amp); //写幅度，输入范围：1-650 mV
void SweepFre(ulong SweepMinFre, ulong SweepMaxFre, ulong SweepStepFre, ulong SweepTime);//扫频波下限频率，上限频率，频率步进（单位：Hz），步进时间间隔（单位：ns，范围：4*(1~65536)ns）
void SW_9910(void);
#endif
