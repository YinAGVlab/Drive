#include "Slover.h"

#define I2CSLAVE_ADDR           0x40    // 从机地址0x40
#define I2C1_CLOCK_FRQ          100000     // I2C速度

int8_t Tx_Idx = 0, Rx_Idx = 0;
int8_t I2C1_Buffer_Rx[I2C1_RAM_SIZE];		//存储目标的数组	
int8_t I2C1_Buffer_Tx[I2C1_RAM_SIZE] = {0, 0, 100, 100};		//存储速度的数组

void I2C1_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // 开漏模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_ClockSpeed = I2C1_CLOCK_FRQ; // 设置I2C时钟频率
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2CSLAVE_ADDR; 			// 从机地址
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_Init(I2C1, &I2C_InitStructure);

    I2C_Cmd(I2C1, ENABLE); 				// 使能I2C1	
	I2C_AcknowledgeConfig(I2C1, ENABLE); // 使能I2C1的应答功能
	
	I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE);
    I2C_ITConfig(I2C1, I2C_IT_BUF, ENABLE);
    I2C_ITConfig(I2C1, I2C_IT_ERR, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init(&NVIC_InitStructure);
}

void I2C1_EV_IRQHandler(void) 
{
	switch(I2C_GetLastEvent(I2C1))
	{
		case I2C_EVENT_SLAVE_BYTE_TRANSMITTED:			//发送
			I2C_SendData(I2C1, I2C1_Buffer_Tx[Tx_Idx++]);
			break;
		case I2C_EVENT_SLAVE_BYTE_TRANSMITTING:
			I2C_SendData(I2C1, I2C1_Buffer_Tx[Tx_Idx++]);
			break;
		
		case I2C_EVENT_SLAVE_BYTE_RECEIVED:			//接收
			I2C1_Buffer_Rx[Rx_Idx++] = I2C_ReceiveData(I2C1);
			break;
		case I2C_EVENT_SLAVE_STOP_DETECTED:
			I2C_Cmd(I2C1, ENABLE);
			Rx_Idx=0; 
			break; 
		default: 
			break;
	}
}

void I2C1_ER_IRQHandler(void) 				//	响应失败中断
{
    if (I2C_GetITStatus(I2C1, I2C_IT_AF)) 
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
		Tx_Idx = 0;
    }
	if (I2C_GetITStatus(I2C1, I2C_IT_BERR))   //起始和停止条件出错
	{ 
		I2C_ClearITPendingBit(I2C1, I2C_IT_BERR);
	}
}
