#ifndef __LED_H
#define __LED_H

#define Blue GPIO_Pin_3
#define Green GPIO_Pin_4
#define Red GPIO_Pin_5

void LED_Init(void);
void LED_ON(uint16_t Color);
void LED_OFF(uint16_t Color);
void LED_TURN(uint16_t Color);

#endif
