#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

int main() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	while(1) {

	}
}
