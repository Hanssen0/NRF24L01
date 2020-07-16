#ifndef NRF24L01_SRC_LOGGER_SDCC_H_
#define NRF24L01_SRC_LOGGER_SDCC_H_
#include "UART.sdcc.h"
#include <stdint.h>
inline void LogHandler(char s) {UARTSendByte(s);}
inline void LogString(char const* s) {while (*s != 0) LogHandler(*s++);}
inline void LogChar(char s) {LogHandler(s);}
void LogHEX(uint8_t s);
void LogHEXs(uint8_t*, uint8_t);
#endif  // NRF24L01_SRC_LOGGER_SDCC_H_
