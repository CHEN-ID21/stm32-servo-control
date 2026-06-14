#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"

void Servo_Init(void)
{
	Delay_ms(1000);
	PWM_Init();
}

//控制舵机1
void Servo_SetAngle1(float Angle)
{
	PWM_SetCompare1((uint16_t)(500 + (Angle / 180.0) * 2000));
}

//控制舵机2
void Servo_SetAngle2(float Angle)
{
	PWM_SetCompare2((uint16_t)(500 + (Angle / 180.0) * 2000));
}
