#ifndef NRF24L01_SRC_UART_SDCC_H_
#define NRF24L01_SRC_UART_SDCC_H_
#include "STC15.sdcc.h"
#define FOSC 20000000L
#define BAUD 115200
void UARTSendByte(unsigned char c);
extern unsigned char kReceived;
void UART1_Interrupt() __interrupt 4;
inline void Timer2Init() {
  T2L = (unsigned char)((65536 - (FOSC/4/BAUD)));
  T2H = (unsigned char)((65536 - (FOSC/4/BAUD)) >> 8);
}
inline void UARTInit() {
  SCON = 0x50;
  Timer2Init();
  AUXR = 0x14;
  AUXR |= 0x01;  // Use timer 2
  ES = 1;
}
#endif  // NRF24L01_SRC_UART_SDCC_H_
