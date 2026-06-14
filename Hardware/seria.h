#ifndef __SERIA_H
#define __SERIA_H

#include "stm32f10x.h"

#define SERIAL_RX_BUFFER_SIZE 17

extern uint8_t Serial_RxBuffer[SERIAL_RX_BUFFER_SIZE];
extern uint8_t Serial_RxCounter;
extern uint8_t Serial_CommandReady;

void Serial_Init(void);
void Serial_SendString(char *str);

#endif
