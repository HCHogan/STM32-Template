#ifndef __EVENTLOOP_HPP
#define __EVENTLOOP_HPP
#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"

#ifdef __cplusplus
extern "C"
{
#endif
void EventLoopC();
#ifdef __cplusplus
}
#endif

void EventLoopCpp();

#endif
