#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"

#ifdef __cplusplus
extern "C"
{
#endif

void PWM_Init(void);
void PWM_SetCompare1(uint16_t);


#ifdef __cplusplus
}
#endif

#endif
