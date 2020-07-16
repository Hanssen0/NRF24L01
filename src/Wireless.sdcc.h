#ifndef NRF24L01_SRC_WIRELESS_SDCC_H_
#define NRF24L01_SRC_WIRELESS_SDCC_H_
#include <stdint.h>
#include "STC15.sdcc.h"
#include "Timer.sdcc.h"
extern uint8_t kLength;
extern uint8_t kCurrentPos;
extern const uint8_t kTXMode[];
extern const uint8_t kRXMode[];
extern const uint8_t kNoAutoACK[];
extern const uint8_t kPayloadLength[];
extern const uint8_t kResetStatus[];
void SPIInit();
void WirelessRead(uint8_t, uint8_t*, uint8_t);
void WirelessWrite(uint8_t, uint8_t*, uint8_t);
void SPI() __interrupt 9;
void WirelessInit();
inline __bit IsWirelessReadingFinished() {return kCurrentPos > kLength;}
inline void WirelessWait() {while (!IsWirelessReadingFinished()) {}}
inline void WirelessReadRegister(uint8_t address, uint8_t* buf) {
  WirelessRead(address, buf, 1);
  WirelessWait();
}
inline void WirelessWriteRegister(uint8_t address, const uint8_t* buf) {
  WirelessWrite(address, (uint8_t*)(buf), 1);
  WirelessWait();
}
inline void WirelessTXMode() {
  P11 = 0;
  WirelessWriteRegister(0x00, kTXMode);
  P11 = 1;
}
inline void WirelessRXMode() {
  P11 = 0;
  WirelessWriteRegister(0x00, kRXMode);
  P11 = 1;
}
inline __bit WirelessIsSent(uint8_t* buffer) {
  WirelessReadRegister(0x07, buffer);
  return (*buffer) & 0x20;
}
inline __bit WirelessIsReceived(uint8_t* buffer) {
  WirelessReadRegister(0x17, buffer);
  return ((*buffer) & 0x01) != 0x01;
}
inline void WirelessResetStatus() {
  WirelessWriteRegister(0x07, kResetStatus);
}
inline void WirelessWaitSending(uint8_t* buffer) {
  while (!WirelessIsSent(buffer)) {}
}
#endif  // NRF24L01_SRC_WIRELESS_SDCC_H_
