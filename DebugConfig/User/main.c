#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"


uint8_t KeyNum;
float Angle;

int main(void)
{
	OLED_Init();
	Servo_Init();
	/*Key_Init();*/

	Angle = 90;
	Servo_SetAngle(Angle);
	Delay_ms(500);
	OLED_ShowString(1,1,"Angle:");
	
	while(1)
	{
		/*KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			Angle += 30;
			if(Angle >180)
			{
				Angle = 0;
			}
			Servo_SetAngle(Angle);
			Delay_ms(300);
			//OLED_ShowNum(1,7,Angle,3);
		}*/
		OLED_ShowNum(1,7,Angle,3);
		Delay_ms(500);
		Servo_SetAngle(180);
		Servo_Init();
		Servo_SetAngle(0);
		Delay_ms(500);
		OLED_ShowNum(1,7,Angle,3);
	}
}
