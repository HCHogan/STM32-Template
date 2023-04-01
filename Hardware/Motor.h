#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

#ifdef __cplusplus
extern "C"
{
#endif


void Motor_Init(void);
void Motor_SetSpeed(int8_t);


#ifdef __cplusplus
}
#endif

#endif
