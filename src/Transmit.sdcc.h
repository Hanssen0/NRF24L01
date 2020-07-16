#ifndef NRF24L01_SRC_TRANSMIT_SDCC_H_
#define NRF24L01_SRC_TRANSMIT_SDCC_H_

#include <stdint.h>

#define kTokenLength 4
#define kMaxDataLength 8
#define kDataLengthUnit 16

union Packet {
  uint8_t raw[kDataLengthUnit];
  struct {
    uint8_t length;
    uint8_t type;
    union {
      uint8_t raw[12];
      struct {
        uint8_t token[kTokenLength];
      } start;
      struct {
        uint8_t old_token[kTokenLength];
        uint8_t new_token[kTokenLength];
      } switch_token;
      struct {
        uint8_t token[kTokenLength];
        uint8_t data[kMaxDataLength];
      } transmit;
    } data;
    uint8_t unused[2];
  } data;
};

enum Transmission {
  Idling,
  SyncPreparing,
  SyncSending,
  SyncSent,
  EstablishedTX,
  Listening,
  SyncReceived,
  EstablishmentPreparing,
  EstablishmentSending,
  EstablishedRX,
  EstablishedReceived,
  EstablishedPreparing,
  EstablishedSending,
  ACKWaiting,
  ACKReceived,
  ACKPreparing,
  ACKSending
};
enum {
  PacketSync,
  PacketEstablishment,
  PacketEstablished
};

extern const unsigned char key[];
extern const unsigned char iv[];
extern enum Transmission kTransmitStatus;

void TransmitSendData(uint8_t*);
void TransmitReceiveData(uint8_t*);
void Transmit(union Packet*, uint8_t* buffer);
#endif  // NRF24L01_SRC_TRANSMIT_SDCC_H_
