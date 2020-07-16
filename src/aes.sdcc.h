#ifndef NRF24L01_SRC_AES_SDCC_H_
#define NRF24L01_SRC_AES_SDCC_H_

#include <stdint.h>

extern uint8_t* kState;
extern const uint8_t* kKey;

void AES_CBC_encrypt_buffer(const uint8_t* iv, uint8_t length);
void AES_CBC_decrypt_buffer(const uint8_t* iv, uint8_t length);
inline void AESSetData(uint8_t* buf) {kState = buf;}
inline void AESSetKey(const uint8_t* key) {kKey = key;}
#endif  // NRF24L01_SRC_AES_SDCC_H_
