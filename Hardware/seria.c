#include "seria.h"
#include "string.h"

uint8_t Serial_RxBuffer[SERIAL_RX_BUFFER_SIZE];
uint8_t Serial_RxCounter = 0;
uint8_t Serial_CommandReady = 0;

// 串口初始化 PA9-TX, PA10-RX
void Serial_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    // PA9 TX
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PA10 RX
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = 9600;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

// 发送字符串
void Serial_SendString(char *str) {
    while (*str != '\0') {
        USART_SendData(USART1, (uint8_t)*str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

// 中断接收：以 \n 或 \r 结尾
void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        uint8_t RxData = USART_ReceiveData(USART1);

        if (RxData == '\n' || RxData == '\r') {
            // 收到结束符，有数据才标记Ready
            if (Serial_RxCounter > 0) {
                Serial_RxBuffer[Serial_RxCounter] = '\0';
                Serial_CommandReady = 1;
            }
        } else {
            // 普通数据，防溢出
            if (Serial_RxCounter < SERIAL_RX_BUFFER_SIZE - 1) {
                Serial_RxBuffer[Serial_RxCounter++] = RxData;
							  Serial_RxBuffer[Serial_RxCounter] = '\0';
            }
        }

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
