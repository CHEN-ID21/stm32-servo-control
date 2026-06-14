#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; //GPIO_Pin_15
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimerBaseInitStructure;
	TIM_TimerBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimerBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimerBaseInitStructure.TIM_Period = 20000 - 1;
	TIM_TimerBaseInitStructure.TIM_Prescaler = 72 - 1;
	TIM_TimerBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimerBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_InitStructure;
	TIM_OCStructInit(&TIM_InitStructure);
	TIM_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_InitStructure.TIM_Pulse = 0;//CCR
	TIM_OC2Init(TIM2,&TIM_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2,Compare);
}
