#include "EventLoop.hpp"
#include "OLED.h"
#include "Timer.h"
#include "PWM.h"
#include <vector>

std::vector<int> a;

uint8_t i;

extern uint16_t Num;

void EventLoopCpp() {

	OLED_Init();
	PWM_Init();

	while(1) {
		for(i = 0; i <= 100; i++) {
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for(i = 0; i <= 100; i++) {
			PWM_SetCompare1(100 - i);
			Delay_ms(10);
		}

	}
}

extern "C"
{
	void EventLoopC() {
		EventLoopCpp();
	}
}
