#include "EventLoop.hpp"
#include "OLED.h"
#include "Timer.h"
#include "Motor.h"
#include "Key.h"

uint8_t keyNum;
int8_t speed;

void EventLoopCpp() {

	OLED_Init();
	Motor_Init();
	Key_Init();
	Motor_SetSpeed(-100);
	OLED_ShowString(1, 1, "Speed: ");

	while(1) {
		keyNum = Key_GetNum();
		if(keyNum == 1) {
			speed += 20;
			if(speed > 100) speed = -100;
		}
		Motor_SetSpeed(speed);
		OLED_ShowSignedNum(1, 7, speed, 3);
	}
}

extern "C"
{
	void EventLoopC() {
		EventLoopCpp();
	}
}
