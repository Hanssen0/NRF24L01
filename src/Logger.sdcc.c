#include "Logger.sdcc.h"
#include <stdint.h>
inline char GetHEX(uint8_t s) {
  s = s + '0';
  if (s > '9') s += 'A' - '9';
  return s;
}
void LogHEX(uint8_t s) {
  LogHandler(GetHEX(s>>4));
  LogHandler(GetHEX(s&0x0f));
}
void LogHEXs(uint8_t* s, uint8_t length) {
  for (uint8_t i = 0; i < length; ++i) {
    LogHEX(s[i]);
    LogChar(' ');
  }
}
