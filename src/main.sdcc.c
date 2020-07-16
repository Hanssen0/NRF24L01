#include "UART.sdcc.h"
#include "Wireless.sdcc.h"
#include "Logger.sdcc.h"
#include "aes.sdcc.h"
#include "Transmit.sdcc.h"

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

inline void ArrayPlusOne(unsigned char* array) {
  unsigned char now = 0;
  while (now < kMaxDataLength) {
    if (array[now] != 0xff) {
      ++array[now];
      break;
    }
    array[now] = 0;
    ++now;
  }
}
inline void EnableInterruption() {EA = 1;}

inline void CopyTo(const uint8_t* src, uint8_t* dst, uint8_t length) {
  for (uint8_t i = 0; i < length; ++i) dst[i] = src[i];
}

uint8_t kToken[] = {0xff, 0x88, 0x44, 0x22};

void CheckPattern(uint8_t* expected, uint8_t* received) {
  for (unsigned char i = 0; i < kTokenLength; ++i) {
    if (expected[i] != received[i]) {
      LogString("Pattern mismatched:\r\n");
      LogString("Expected: ");
      LogHEXs(expected, kTokenLength);
      LogString("\r\nReceived: ");
      LogHEXs(received, kTokenLength);
      LogString("\r\n");
      break;
    }
  }
}

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
    if (kReceived != 0) {
      LogString("UART: ");
      LogChar(kReceived);
      LogString("\r\n");
      kReceived = 0;
    }
    Transmit(&packet, buf);
    switch (kTransmitStatus) {
     case Idling:
       packet.data.type = PacketSync;
       CopyTo(kToken, packet.data.data.start.token, kTokenLength);
       kTransmitStatus = SyncPreparing;
       break;
     case EstablishedTX:
      CheckPattern(kToken, packet.data.data.switch_token.old_token);
      LogString("Established: ");
      LogHEXs(packet.data.data.switch_token.old_token, 2*kTokenLength);
      LogString("\r\n");
      packet.data.type = PacketEstablished;
      for (uint8_t i = 0; i < kTokenLength; ++i) {
        packet.data.data.switch_token.old_token[i] =
        (kToken[i] ^= packet.data.data.switch_token.new_token[i]);
      }
      for (uint8_t i = 0; i < kMaxDataLength; ++i) {
        packet.data.data.transmit.data[i] = 0;
      }
      kTransmitStatus = EstablishedPreparing;
      break;
     case ACKReceived:
      CheckPattern(kToken, packet.data.data.transmit.token);
      ArrayPlusOne(packet.data.data.transmit.data);
      kTransmitStatus = EstablishedPreparing;
      break;
    }
  }
}
