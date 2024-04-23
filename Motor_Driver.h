/*
---------------------------
| Motor | In1 | In2 | PWM |
---------------------------
|   M1  | PC2 | PC3 | 1,1 |
---------------------------
|   M2  | PA5 |	PA6 | 1,2 |
---------------------------
|   M3  | PC5 | PB0 | 2,2 |
---------------------------
|   M4  | PA7 | PC4 | 1,3 |
---------------------------
*/
#ifndef __MOTER_DRIVER_H__
#define __MOTER_DRIVER_H__

#include "gpio.h"
#include "tim.h"

extern int M1;
extern int M2;
extern int M3;
extern int M4;

void Motor_Driver_Set(void);
void Motor_Driver_Init(void);
void Motor_Driver_Stop(uint8_t num);


#endif
