#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	//开启时钟
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
  //配置GPIOA（PA0和PA7为复用推挽输出）
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//配置时钟源
	//TIM_InternalClockConfig(TIM2);
	TIM_InternalClockConfig(TIM3);
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimerBaseInitStructure;
	TIM_TimerBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimerBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimerBaseInitStructure.TIM_Period = 20000 - 1; //20s周期
	TIM_TimerBaseInitStructure.TIM_Prescaler = 72 - 1; //1MHz计数频率
	TIM_TimerBaseInitStructure.TIM_RepetitionCounter = 0;
	//TIM_TimeBaseInit(TIM2,&TIM_TimerBaseInitStructure);
	TIM_TimeBaseInit(TIM3,&TIM_TimerBaseInitStructure);
	//配置输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//TIM_OCStructInit(&TIM_InitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;//CCR
	
	//初始化通道
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	
	//使能定时器
	//TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM3,Compare);
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM3,Compare);
}

