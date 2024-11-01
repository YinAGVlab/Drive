#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);
void Motor1_SetSpeed(int8_t Speed);
void Motor2_SetSpeed(int8_t Speed);
int16_t Xianfu(int16_t Aim);
int16_t Zhengfu(int8_t Flag, int16_t Aim);

#endif
