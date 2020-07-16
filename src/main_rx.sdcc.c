#include "UART.sdcc.h"
#include "Wireless.sdcc.h"
#include "Logger.sdcc.h"
#include "aes.sdcc.h"
#include "Transmit.sdcc.h"

inline void EnableInterruption() {EA = 1;}
unsigned char buf[16];
union Packet packet;

inline void TransmitSendData(uint8_t* buffer) {
  WirelessWrite(0xA0, buffer, 16);
  WirelessWait();
}
inline void TransmitReceiveData(uint8_t* buffer) {
  WirelessRead(0x61, buffer, 16);
  WirelessWait();
}
inline void CopyTo(const uint8_t* src, uint8_t* dst, uint8_t length) {
  for (uint8_t i = 0; i < length; ++i) dst[i] = src[i];
}

uint8_t kToken[] = {0xaa, 0x77, 0x33, 0x11};

const unsigned char key[] = {
  0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
  0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
};

int main() {
  EnableInterruption();
  UARTInit();
  LogString("UART init\r\n");
  SPIInit();
  LogString("SPI init\r\n");
  WirelessInit();
  LogString("Wireless module init\r\n");
  AESSetKey(key);
  while (1) {
    if (kReceived != 0) {
      LogString("UART: ");
      LogChar(kReceived);
      LogString("\r\n");
      LogHEX(kTransmitStatus);
      LogString("\r\n");
      kReceived = 0;
    }
    Transmit(&packet, buf);
    switch (kTransmitStatus) {
     case Idling:
      WirelessRXMode();
      kTransmitStatus = Listening;
      break;
     case SyncReceived:
      LogString("Sync: ");
      LogHEXs(packet.data.data.start.token, kTokenLength);
      LogString("\r\n");
      CopyTo(kToken, packet.data.data.switch_token.new_token, kTokenLength);
      for (unsigned char i = 0; i < kTokenLength; ++i) {
        kToken[i] ^= packet.data.data.switch_token.old_token[i];
      }
      packet.data.type = PacketEstablishment;
      kTransmitStatus = EstablishmentPreparing;
      break;
     case EstablishedReceived:
      for (unsigned char i = 0; i < kTokenLength; ++i) {
        if (kToken[i] != packet.data.data.transmit.token[i]) {
          LogString("Pattern mismatched:\r\n");
          LogString("Expected: ");
          LogHEXs(kToken, kTokenLength);
          LogString("\r\nReceived: ");
          LogHEXs(packet.data.data.transmit.token, kTokenLength);
          LogString("\r\n");
          break;
        }
      }
      LogString("Data: ");
      LogHEXs(packet.raw, 16);
      LogString("\r\n");
      kTransmitStatus = ACKPreparing;
      break;
    }
  }
}
