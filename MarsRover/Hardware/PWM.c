#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void PID_Init(PID *pidl, PID *pidr)
{
	pidl->target_val=0;
	pidl->output_val=0;
	pidl->Error=0;
	pidl->LastError=0;
	pidl->Kp = 2.0;
	pidl->Ki = 0.0;
	pidl->Kd = 0.0;

	pidr->target_val=0;	
	pidr->output_val=0.0;
	pidr->Error=0.0;
	pidr->LastError=0.0;
	pidr->Kp = 1.0;
	pidr->Ki = 0.0;
	pidr->Kd = 0.0;
}

float addPID_realize(PID *pid,float target_val, float actual_val)
{
	pid->target_val = target_val;
	pid->Error = pid->target_val - actual_val;
	
	pid->output_val += pid->Kp * (pid->Error - pid-> LastError) +
	                  pid->Ki * pid->Error +
	                  pid->Kd *(pid->Error -2*pid->LastError+pid->PrevError);
	pid-> PrevError = pid->LastError;
	pid-> LastError = pid->Error;

	return pid->output_val;
}

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3;		
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36-1;	//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;	//CCR
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC4Init(TIM2,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare1(int16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}

void PWM_SetCompare2(int16_t Compare)
{
	TIM_SetCompare4(TIM2,Compare);
}

