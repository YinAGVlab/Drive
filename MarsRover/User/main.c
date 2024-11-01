#include "stm32f10x.h"           // Device header
#include "Delay.h"
#include "Motor.h"
#include "PWM.h"
#include "Key.h"
#include "LED.h"
#include "Encoder.h"
#include "Slover.h"
#include "Timer.h"
#include <math.h>

int8_t Speed1, Speed2;
int8_t Aim1, Aim2;
int8_t Aim_Set1, Aim_Set2;
int8_t Flag1, Flag2;
int32_t i, temp1, temp2;
PID PID_L, PID_R;

int main(void)
{
	LED_Init();
	Key_Init();
	Motor_Init();
	I2C1_Init();
	Encoder_Init();
	Timer_Init();
	PID_Init(&PID_L, &PID_R);
	
	LED_ON(Blue | Green | Red);
	
	while(1)
	{
//		Flag1 = I2C1_Buffer_Rx[0];
//		Aim1 = I2C1_Buffer_Rx[1];
//		Flag2 = I2C1_Buffer_Rx[2];
//		Aim2 = I2C1_Buffer_Rx[3];
//		
//		Aim1 = Zhengfu(Flag1, Xianfu(Aim1));
//		Aim2 = Zhengfu(Flag2, Xianfu(Aim2));
		Aim1 = 40;
		Aim2 = 40;
		
		Aim_Set1 = addPID_realize(&PID_L, Aim1, Speed1);
		Aim_Set2 = addPID_realize(&PID_R, Aim2, Speed2);
		
		Motor1_SetSpeed(Aim_Set1);
		Motor2_SetSpeed(Aim_Set2);
		
		I2C1_Buffer_Tx[0] = Speed1;
		I2C1_Buffer_Tx[1] = Speed2;
		
		switch(Key_GetNum())
		{
			case 1: LED_TURN(Blue);break;
			case 2:	LED_TURN(Green);break;
			case 3:	LED_TURN(Red);break;
			default:break;
		}
	}
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		temp1 += Encoder_Get1();
		temp2 += Encoder_Get2();
		i++;
		if(i == 10)
		{
			Speed1 = temp1 / 10;
			Speed2 = temp2 / 10;
			temp1 = 0;
			temp2 = 0;
			i = 0;
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
