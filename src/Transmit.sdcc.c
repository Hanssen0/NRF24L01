#include "Transmit.sdcc.h"
#include "aes.sdcc.h"

// TODO: Decoupling
#include "Wireless.sdcc.h"

const unsigned char iv[] = {
  0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
  0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
};
const uint16_t kMaxWaitingTime = 60000;
enum Transmission kTransmitStatus = Idling;

inline void SendPacket(union Packet* packet, uint8_t* buffer) {
  for (uint8_t i = 0; i < kDataLengthUnit; ++i) buffer[i] = packet->raw[i];
  AESSetData(buffer);
  AES_CBC_encrypt_buffer(iv, 16);
  TransmitSendData(buffer);
}

inline void ReceivePacket(union Packet* packet) {
  TransmitReceiveData(packet->raw);
  AESSetData(packet->raw);
  AES_CBC_decrypt_buffer(iv, 16);
}

uint16_t kWaitingCountdown;
void Transmit(union Packet* packet, uint8_t* buffer) {
  if (kTransmitStatus == Idling ||
      kTransmitStatus == EstablishedTX ||
      kTransmitStatus == SyncReceived ||
      kTransmitStatus == EstablishedReceived ||
      kTransmitStatus == ACKReceived) return;
  if (kTransmitStatus == SyncPreparing ||
      kTransmitStatus == EstablishmentPreparing ||
      kTransmitStatus == EstablishedPreparing ||
      kTransmitStatus == ACKPreparing) {
    kWaitingCountdown = 0;
    SendPacket(packet, buffer);
  }
  if (kTransmitStatus == SyncSent ||
      kTransmitStatus == Listening ||
      kTransmitStatus == ACKWaiting ||
      kTransmitStatus == EstablishedRX) {
    if (!WirelessIsReceived(buffer)) {
      if (kTransmitStatus == Listening ||
          kTransmitStatus == EstablishedRX ||
          ++kWaitingCountdown <= kMaxWaitingTime) return;
      kTransmitStatus -= 3;  // Minus 2 minus 1 plus 1 (at the end of funciton)
    } else {
      ReceivePacket(packet);
    }
    WirelessTXMode();
  }
  if (kTransmitStatus == SyncSending ||
      kTransmitStatus == EstablishmentSending ||
      kTransmitStatus == EstablishedSending ||
      kTransmitStatus == ACKSending) {
    if (!WirelessIsSent(buffer)) return;
    WirelessResetStatus();
    WirelessRXMode();
    if (kTransmitStatus == ACKSending) {  // Reduce time
      kTransmitStatus = EstablishmentSending;  // EstablishedRX - 1
    }
  }
  ++kTransmitStatus;
  /*switch (kTransmitStatus) {
   case Idling: break;
   case SyncPreparing:
    kTransmitStatus = SyncSending;
    break;
   case SyncSending:
    kTransmitStatus = SyncSent;
    break;
   case SyncSent:
    kTransmitStatus = EstablishedTX;
    break;
   case EstablishedTX: break;
   case Listening:
    kTransmitStatus = SyncReceived;
    break;
   case SyncReceived: break;
   case EstablishmentPreparing:
    kTransmitStatus = EstablishmentSending;
    break;
   case EstablishmentSending:
    kTransmitStatus = EstablishedRX;
    break;
   case EstablishedRX:
    kTransmitStatus = EstablishedReceived;
    break;
   case EstablishedReceived: break;
   case EstablishedPreparing:
    kTransmitStatus = EstablishedSending;
    break;
   case EstablishedSending:
    kTransmitStatus = ACKWaiting;
    break;
   case ACKWaiting:
    kTransmitStatus = ACKReceived;
    break;
   case ACKReceived: break;
   case ACKPreparing:
    kTransmitStatus = ACKSending;
    break;
   case ACKSending:
    kTransmitStatus = EstablishedRX;
    break;
  }*/
}
