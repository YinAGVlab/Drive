#ifndef __PWM_H
#define __PWM_H

typedef struct
{
	int16_t target_val;   //目标值
	int16_t Error;          /*第 k 次偏差 */
	int16_t LastError;     /* Error[-1],第 k-1 次偏差 */
	int16_t PrevError;    /* Error[-2],第 k-2 次偏差 */
	float Kp,Ki,Kd;     //比例、积分、微分系数
//	float integral;     //积分值
	int16_t output_val;   //输出值
}PID;

void PID_Init(PID *pidl, PID *pidr);
float addPID_realize(PID *pid,float target_val, float actual_val);
void PWM_Init(void);
void PWM_SetCompare1(int16_t Compare);
void PWM_SetCompare2(int16_t Compare);

#endif
