/*
---------------------------
| Motor | In1 | In2 | PWM |
---------------------------
|   M1  | PC2 | PC3 | 1,1 |
---------------------------
|   M2  | PC0 |	PC1 | 1,2 |
---------------------------
|   M3  |PD12 | PD13| 1,3 |
---------------------------
|   M4  |PD14 | PD15| 1,4 |
---------------------------
*/
#include "motor_driver.h"
#include "main.h"

int M1 = 0;
int M2 = 0;
int M3 = 0;
int M4 = 0;


void Motor_Driver_Init(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
}


void Motor_Driver_Set(void)
{
	if(M1 >= 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, M1 * 5);
	}else if(M1 == 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	}else if(M1 <= 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, (-M1) * 5);
	}
	
	if(M2 >= 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, M2 * 5 * 1.1);
	}else if(M2 == 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	}else if(M2 <= 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, (-M2) * 5 * 1.1);
	}
	
	if(M3 >= 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, M3 * 5);
	}else if(M3 == 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	}else if(M3 <= 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, (-M3) * 5);
	}
	
	if(M4 >= 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, M4 * 5 * 7 / 6);
	}else if(M4 == 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	}else if(M4 <= 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, (-M4) * 5 * 7 / 6);
	}
	
}


void Motor_Driver_Stop(uint8_t num)
{
	switch(num)
  {
		case 1:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
	}
}

