#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}

void Servo1_SetAngle(float Angle)
{
	PWM1_SetCompare2(Angle / 270 * 2120+500);
}

void Servo2_SetAngle(float Angle)
{
	PWM2_SetCompare2(Angle / 270 * 2120+500);
}
