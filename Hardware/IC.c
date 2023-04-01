#include "stm32f10x.h"

#ifdef __cplusplus
extern "C"
{
#endif

void IC_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	// open the clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		// reuse output, source from time
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_InternalClockConfig(TIM3);		// choose the internal tim

	// Initialize the timebase unit
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;		// ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		// PSC
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

	// then Initialize the input capture
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;		// which channel
	TIM_ICInitStructure.TIM_ICFilter = 0xF;						// filter
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;		// direct link
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);

	TIM_Cmd(TIM3, ENABLE);
}

uint32_t IC_GetFreq(void) {
	return 1000000 / TIM_GetCapture1(TIM3);
}





#ifdef __cplusplus
}
#endif
