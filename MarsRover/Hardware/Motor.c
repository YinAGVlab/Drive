#include "stm32f10x.h"                  // Device header
#include "PWM.h"

#define M1INA GPIO_Pin_1
#define M1INB GPIO_Pin_2
#define M2INA GPIO_Pin_5
#define M2INB GPIO_Pin_4

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	PWM_Init();
}

void Motor1_SetSpeed(int8_t Speed)
{
	if(Speed > 0)
	{
		GPIO_SetBits(GPIOA,M1INB);
		GPIO_ResetBits(GPIOA,M1INA);
		PWM_SetCompare1(Speed);
	}
	else if(Speed == 0)
	{
		PWM_SetCompare1(0);
	}
	else
	{
		GPIO_SetBits(GPIOA,M1INA);
		GPIO_ResetBits(GPIOA,M1INB);
		PWM_SetCompare1(-Speed);
	}
}

void Motor2_SetSpeed(int8_t Speed)
{
	if(Speed > 0)
	{
		GPIO_SetBits(GPIOA,M2INA);
		GPIO_ResetBits(GPIOA,M2INB);
		PWM_SetCompare2(Speed);
	}
	else if(Speed == 0)
	{
		PWM_SetCompare2(0);
	}
	else
	{
		GPIO_SetBits(GPIOA,M2INB);
		GPIO_ResetBits(GPIOA,M2INA);
		PWM_SetCompare2(-Speed);
	}
}

int16_t Xianfu(int16_t Aim)
{
	if(Aim >= 100)
	{
		Aim = 100;
	}
	if(Aim <= -100)
	{
		Aim = -100;
	}
	return Aim;
}

int16_t Zhengfu(int8_t Flag, int16_t Aim)
{
	int16_t Temp;
	if(Flag == 1)
	{
		Temp = -Aim;
	}
	else
		Temp = Aim;
	return Temp;
}
