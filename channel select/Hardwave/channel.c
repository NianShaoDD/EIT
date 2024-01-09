#include "stm32h7xx.h"                  // Device header
#include "gpio.h"

/**************************
      通道代码初始化
***************************/
void Channel_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, A2_Pin|A3_Pin|A1_Pin|A0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, B3_Pin|B2_Pin|LED_Pin|B1_Pin
                          |B0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = A2_Pin|A3_Pin|A1_Pin|A0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin */
  GPIO_InitStruct.Pin = B3_Pin|B2_Pin|LED_Pin|B1_Pin
                          |B0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/**************************
      使用gpio传输地址
***************************/

void A_Addset(uint8_t Byte)
{
	HAL_GPIO_WritePin(A0_GPIO_Port,A0_Pin,(0X01&Byte));
	HAL_GPIO_WritePin(A1_GPIO_Port,A1_Pin,(0X02&Byte));
	HAL_GPIO_WritePin(A2_GPIO_Port,A2_Pin,(0X04&Byte));
	HAL_GPIO_WritePin(A3_GPIO_Port,A3_Pin,(0X08&Byte));
}

void B_Addset(uint8_t Byte)
{
	HAL_GPIO_WritePin(B0_GPIO_Port,B0_Pin,(0X01&Byte));
	HAL_GPIO_WritePin(B1_GPIO_Port,B1_Pin,(0X02&Byte));
	HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,(0X04&Byte));
	HAL_GPIO_WritePin(B3_GPIO_Port,B3_Pin,(0X08&Byte));
}