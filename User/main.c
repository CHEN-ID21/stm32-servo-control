#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "seria.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
int Angle1 = 90; // 舵机1初始角度
int Angle2 = 90; // 舵机2初始角度


int main(void) {
    Serial_Init();
    Servo_Init();
    
    Servo_SetAngle1(90);
    Servo_SetAngle2(90);
    
    while (1) {
        if (Serial_CommandReady == 1) {
            Serial_CommandReady = 0; // 先清零防止重入
            
            // 查找'A'和'B'的位置
            char *posA = strchr((char*)Serial_RxBuffer, 'A');
            char *posB = strchr((char*)Serial_RxBuffer, 'B');
            
            if (posA != NULL && posB != NULL) {
                // 同时包含A和B，一次控制两个舵机
                int angle1 = atoi(posA + 1);
                int angle2 = atoi(posB + 1);
                
                if (angle1 >= 0 && angle1 <= 180)
                    Servo_SetAngle1(angle1);
                if (angle2 >= 0 && angle2 <= 180)
                    Servo_SetAngle2(angle2);
                    
            } else if (posA != NULL) {
                // 只有A，单独控制舵机1
                int angle1 = atoi(posA + 1);
                if (angle1 >= 0 && angle1 <= 180)
                    Servo_SetAngle1(angle1);
                    
            } else if (posB != NULL) {
                // 只有B，单独控制舵机2
                int angle2 = atoi(posB + 1);
                if (angle2 >= 0 && angle2 <= 180)
                    Servo_SetAngle2(angle2);
            }
            
            Serial_RxCounter = 0;
            memset(Serial_RxBuffer, 0, sizeof(Serial_RxBuffer));
        }
    }
}
