#include "EventLoop.hpp"
#include "OLED.h"
#include "Timer.h"
#include <vector>

std::vector<int> a;

extern uint16_t Num;

void EventLoopCpp() {

	OLED_Init();
	Timer_Init();

	OLED_ShowString(1, 1, "Num:");
	OLED_ShowString(2, 1, "CNT:");

	while(1) {
		OLED_ShowNum(1, 5, Num, 5);
		OLED_ShowNum(2, 5, TIM_GetCounter(TIM2), 5);
	}
}

extern "C"
{
	void EventLoopC() {
		EventLoopCpp();
	}
}
