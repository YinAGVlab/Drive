#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
	
}

void LED_ON(uint16_t Color)
{
	GPIO_SetBits(GPIOB,Color);
}

void LED_OFF(uint16_t Color)
{
	GPIO_ResetBits(GPIOB,Color);
}

void LED_TURN(uint16_t Color)
{
	if (GPIO_ReadOutputDataBit(GPIOB, Color) == Bit_SET)
    {
        GPIO_ResetBits(GPIOB, Color);
    }
    else
    {
        GPIO_SetBits(GPIOB, Color);
    }
}
