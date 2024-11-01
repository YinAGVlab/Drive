#include "stm32f10x.h"           // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "MyI2C.h"
#include "Timer.h"
#include <math.h>
#include "MPU6050.h"
#include "Encoder.h"

int16_t Speed1, Speed2, Speed3, Speed4;
int8_t Aim1, Aim2;
int8_t Flag1, Flag2;

int main(void)
{
	Serial_Init();
	OLED_Init();
	MyI2C_Init();
//	Encoder_Init();
//	Timer_Init();
		
	while(1)
	{
		Flag1 = (Serial_RxPacket[0] - 48);
		Aim1 = (Serial_RxPacket[1] - 48) * 100 + (Serial_RxPacket[2] - 48) * 10 + (Serial_RxPacket[3] - 48);
		Flag2 = (Serial_RxPacket[5] - 48);
		Aim2 = (Serial_RxPacket[6] - 48) * 100 + (Serial_RxPacket[7] - 48) * 10 + (Serial_RxPacket[8] - 48);
	
		MyI2C_Start();
		MyI2C_SendByte(0x40);
		MyI2C_ReceiveAck();
		MyI2C_SendByte(Flag1);
		MyI2C_SendAck(0);
		MyI2C_SendByte(Aim1);
		MyI2C_SendAck(0);
		MyI2C_SendByte(Flag2);
		MyI2C_SendAck(0);
		MyI2C_SendByte(Aim2);
		MyI2C_SendAck(1);
		MyI2C_Stop();
		
		MyI2C_Start();
		MyI2C_SendByte(0x40 | 0x01);
		MyI2C_ReceiveAck();
		Speed1 = MyI2C_ReceiveByte();
		MyI2C_SendAck(0);
		Speed2 = MyI2C_ReceiveByte();
		MyI2C_SendAck(1);
		MyI2C_Stop();
		
//		Speed1 = 10;
//		Speed3 =(Speed1 << 8) | 10;
		
		
				
//		Delay_ms(50);
		OLED_ShowChar(0, 0, 'M', OLED_8X16);
		OLED_ShowChar(0, 32, 'S', OLED_8X16);
		OLED_ShowFloatNum(24, 0, Aim1, 4, 2, OLED_8X16);
		OLED_ShowFloatNum(24, 16, Aim2, 4, 2, OLED_8X16);
		OLED_ShowFloatNum(24, 32, Speed1, 4, 2, OLED_8X16);
		OLED_ShowFloatNum(24, 48, Speed2, 4, 2, OLED_8X16);
		OLED_Update();
		
		Serial_RxFlag = 0;
	}
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		Speed1 = Encoder_Get1();
		Speed2 = Encoder_Get2();
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
