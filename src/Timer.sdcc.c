#include "Timer.sdcc.h"
void DelayHalfMs() {
  for (unsigned char i = 0; i < 7; ++i) {
    for (unsigned char i = 0; i < 125; ++i) {}
  }
}
