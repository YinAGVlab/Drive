#ifndef __SLOVER_H
#define __SLOVER_H

#include "stm32f10x.h"                  // Device header
#define I2C1_RAM_SIZE           4        // 缓存区长度

extern int8_t Rx_Idx;
extern int8_t Tx_Idx;
extern int8_t I2C1_Buffer_Rx[I2C1_RAM_SIZE];			
extern int8_t I2C1_Buffer_Tx[I2C1_RAM_SIZE];	

void I2C1_Init(void);

#endif
