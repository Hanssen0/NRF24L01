#include "Wireless.sdcc.h"
uint8_t* kBufAddress;
uint8_t kLength;
uint8_t kCurrentPos;
extern const uint8_t kTXMode[] = {0x0A};
extern const uint8_t kRXMode[] = {0x0B};
extern const uint8_t kNoAutoACK[] = {0x00};
extern const uint8_t kPayloadLength[] = {0x10};
extern const uint8_t kResetStatus[] = {0x7E};
inline void WirelessTransmissionStart() {P10 = 0;}
inline void WirelessTransmissionEnd() {P10 = 1;}
void SPIInit() {
  SPDAT = 0;
  SPSTAT = 0x80 | 0x40;
  SPCTL = 0x40 | 0x10;
  IE2 |= 0x02;
}
__bit kIsWriting;
void WirelessRead(
    uint8_t address,
    uint8_t* buf,
    uint8_t length) {
  kBufAddress = buf;
  kLength = length;
  kCurrentPos = length;
  kIsWriting = 0;
  WirelessTransmissionStart();
  SPDAT = address;
}
const uint8_t WirelessWriteMark = 0x20;
void WirelessWrite(
    uint8_t address,
    uint8_t* buf,
    uint8_t length) {
  kBufAddress = buf;
  kLength = length;
  kCurrentPos = 0;
  kIsWriting = 1;
  WirelessTransmissionStart();
  SPDAT = WirelessWriteMark | address;
}
inline void WirelessFinishTransmission() {
  WirelessTransmissionEnd();
  kLength = 0;
  kCurrentPos = 1;
}
void SPI() __interrupt 9 {
  SPSTAT = 0x80 | 0x40;
  if (kCurrentPos == kLength) {
    if (kIsWriting == 1) {
      WirelessFinishTransmission();
      return;
    }
    kCurrentPos = 0;
    SPDAT = 0xff;
    return;
  }
  if (kIsWriting == 0) {
    kBufAddress[kCurrentPos] = SPDAT;
    if (kCurrentPos != kLength - 1) {
        ++kCurrentPos;
        SPDAT = 0xff;
    } else {
      WirelessFinishTransmission();
    }
  } else {
    SPDAT = kBufAddress[kCurrentPos++];
  }
}
void WirelessInit() {
  P11 = 0;
  P10 = 1;
  kLength = 0;
  kCurrentPos = 0;

  WirelessWriteRegister(0x01, kNoAutoACK);
  WirelessWriteRegister(0x11, kPayloadLength);

  WirelessTXMode();

  DelayHalfMs();
  DelayHalfMs();
  DelayHalfMs();
  DelayHalfMs();
}
