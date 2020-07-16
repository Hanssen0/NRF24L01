#include "UART.sdcc.h"
__bit kIsUARTBusy = 0;
void UARTSendByte(unsigned char c) {
  while (kIsUARTBusy) {}
  kIsUARTBusy = 1;
  SBUF = c;
}
unsigned char kReceived = 0;
void UART1_Interrupt() __interrupt 4 {
  if (RI) {
    RI = 0;
    kReceived = SBUF;
  }
  if (TI) {
    TI = 0;
    kIsUARTBusy = 0;
  }
}
