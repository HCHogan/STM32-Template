#include "EventLoop.hpp"
#include "OLED.h"
#include "Timer.h"
#include "PWM.h"
#include <vector>
#include "IC.h"

std::vector<int> a;

uint8_t i;

extern uint16_t Num;

void EventLoopCpp() {

	OLED_Init();
	PWM_Init();
	IC_Init();

	OLED_ShowString(1, 1, "Freq: 00000Hz");

	PWM_SetPrescaler(720 - 1);		// Freq = 72M / (PSC + 1) / 100
	PWM_SetCompare1(50);			// Duty = CCR / 100

	while(1) {
		OLED_ShowNum(1, 7, IC_GetFreq(), 5);
	}
}

extern "C"
{
	void EventLoopC() {
		EventLoopCpp();
	}
}
