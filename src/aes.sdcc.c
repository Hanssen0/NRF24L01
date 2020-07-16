#include "aes.sdcc.h"
const uint8_t kAESRoundNumber = 10;
#define kAESBlockLength 16
const uint8_t sbox[256] = {
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
  0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
  0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
  0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
  0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
  0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
  0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
  0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
  0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
  0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
  0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
  0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
  0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
  0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
  0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
  0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
  0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
const uint8_t rsbox[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
  0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
  0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
  0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
  0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
  0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
  0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
  0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
  0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
  0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
  0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
  0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
  0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
  0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
  0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
  0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
  0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};
const uint8_t Rcon[11] = {
  0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};
const uint8_t* kKey;
uint8_t kRoundKey[kAESBlockLength];
uint8_t kRound;
uint8_t* kState;
inline uint8_t getSBoxValue(uint8_t num) {return sbox[num];}
inline uint8_t getSBoxInvert(uint8_t num) {return rsbox[num];}
inline uint8_t GetRcon(uint8_t round) {return Rcon[round];}
void GetNextRoundKey() {
  kRoundKey[0] ^= getSBoxValue(kRoundKey[13]) ^ GetRcon(kRound);
  kRoundKey[1] ^= getSBoxValue(kRoundKey[14]);
  kRoundKey[2] ^= getSBoxValue(kRoundKey[15]);
  kRoundKey[3] ^= getSBoxValue(kRoundKey[12]);
  uint8_t i = 0;
  uint8_t j = 4;
  while (i < 12) {
    kRoundKey[j] ^= kRoundKey[i];
    ++j;
    ++i;
  }
}
void GetPreviousRoundKey() {
  uint8_t i = 12;
  uint8_t j = 16;
  while (j > 4) kRoundKey[--j] ^= kRoundKey[--i];
  kRoundKey[2] ^= getSBoxValue(kRoundKey[15]);
  kRoundKey[3] ^= getSBoxValue(kRoundKey[12]);
  kRoundKey[1] ^= getSBoxValue(kRoundKey[14]);
  kRoundKey[0] ^= getSBoxValue(kRoundKey[13]) ^ GetRcon(kRound);
}
void AddRoundKey() {
  for (uint8_t i = 0; i < kAESBlockLength; ++i) kState[i] ^= kRoundKey[i];
}
inline void SubBytes() {
  for (uint8_t i = 0; i < kAESBlockLength; ++i) {
    kState[i] = getSBoxValue(kState[i]);
  }
}
void ShiftRows() {
  // Rotate first row 1 columns to left
  uint8_t temp = kState[1];  // (0, 1)
  kState[1] = kState[5];  // (0, 1) <- (1, 1)
  kState[5] = kState[9];  // (1, 1) <- (2, 1)
  kState[9] = kState[13];  // (2, 1) <- (3, 1)
  kState[13] = temp;  // (3, 1) <- (0, 1)
  // Rotate second row 2 columns to left
  temp = kState[2];  // (0, 2)
  kState[2] = kState[10];  // (0, 2) <- (2, 2)
  kState[10] = temp;  // (2, 2) <- (0, 2)
  temp = kState[6];  // (1, 2)
  kState[6] = kState[14];  // (1, 2) <- (3, 2)
  kState[14] = temp;  // (3, 2) <- (1, 2)

  // Rotate third row 3 columns to left
  temp = kState[3];  // (0, 3)
  kState[3] = kState[15];  // (0, 3) <- (3, 3)
  kState[15] = kState[11];  // (3, 3) <- (2, 3)
  kState[11] = kState[7];  // (2, 3) <- (1, 3)
  kState[7] = temp;  // (1, 3) <- (0, 3)
}

uint8_t xtime(uint8_t x) {
  return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
}

// MixColumns function mixes the columns of the state matrix
void MixColumns() {
  uint8_t Tmp, t;
  for (uint8_t i = 0; i < kAESBlockLength; i += 4) {
    t = kState[i];
    Tmp = kState[i] ^ kState[i + 1] ^ kState[i + 2] ^ kState[i + 3];
    kState[i] ^= xtime(kState[i] ^ kState[i + 1]) ^ Tmp;
    kState[i + 1] ^= xtime(kState[i + 1] ^ kState[i + 2]) ^ Tmp;
    kState[i + 2] ^= xtime(kState[i + 2] ^ kState[i + 3]) ^ Tmp;
    kState[i + 3] ^= xtime(kState[i + 3] ^ t) ^ Tmp;
  }
}

uint8_t Multiply(uint8_t x, uint8_t y) {
  uint8_t result = 0;
  for (uint8_t i = 0; i < 5; ++i) {
    result ^= (y & 1) * x;
    if (i == 4) break;
    y >>= 1;
    x = xtime(x);
  }
  return result;
}

// MixColumns function mixes the columns of the state matrix.
// The method used to multiply may be difficult to understand for the
// inexperienced.
// Please use the references to gain more information.
const uint8_t InvMixColumnsConstant[4] = {0x0e, 0x0b, 0x0d, 0x09};
void InvMixColumns() {
  uint8_t a, b, c, d;
  for (uint8_t i = 0; i < kAESBlockLength; i += 4) {
    a = kState[i];
    b = kState[i + 1];
    c = kState[i + 2];
    d = kState[i + 3];
    for (uint8_t j = 0; j < 4; ++j) {
      kState[i + j] = Multiply(a, InvMixColumnsConstant[(4 - j) % 4]) ^
                      Multiply(b, InvMixColumnsConstant[(5 - j) % 4]) ^
                      Multiply(c, InvMixColumnsConstant[(6 - j) % 4]) ^
                      Multiply(d, InvMixColumnsConstant[(7 - j) % 4]);
    }
  }
}

inline void InvSubBytes() {
  for (uint8_t i = 0; i < kAESBlockLength; ++i) {
    kState[i] = getSBoxInvert(kState[i]);
  }
}

void InvShiftRows() {
  // Rotate first row 1 columns to right
  uint8_t temp = kState[13];  // (3, 1)
  kState[13] = kState[9];  // (3, 1) <- (2, 1)
  kState[9] = kState[5];  // (2, 1) <- (1, 1)
  kState[5] = kState[1];  // (1, 1) <- (0, 1)
  kState[1] = temp;  // (0, 1) <- (3, 1)
  // Rotate second row 2 columns to right
  temp = kState[2];  // (0, 2)
  kState[2] = kState[10];  // (0, 2) <- (2, 2)
  kState[10] = temp;  // (2, 2) <- (0, 2)
  temp = kState[6];  // (1, 2)
  kState[6] = kState[14];  // (1, 2) <- (3, 2)
  kState[14] = temp;  // (3, 2) <- (1, 2)
  // Rotate third row 3 columns to right
  temp = kState[3];  // (0, 3)
  kState[3] = kState[7];  // (0, 3) <- (1, 3)
  kState[7] = kState[11];  // (1, 3) <- (2, 3)
  kState[11] = kState[15];  // (2, 3) <- (3, 3)
  kState[15] = temp;  // (3, 3) <- (0, 3)
}

// Cipher is the main function that encrypts the PlainText.
void Cipher() {
  kRound = 1;

  while (1) {
    AddRoundKey();
    GetNextRoundKey();
    SubBytes();
    ShiftRows();
    if (kRound == kAESRoundNumber) break;
    ++kRound;
    MixColumns();
  }
  AddRoundKey();
}

void InvCipher() {
  kRound = kAESRoundNumber;

  AddRoundKey();
  GetPreviousRoundKey();
  while (1) {
    InvShiftRows();
    InvSubBytes();
    AddRoundKey();
    if (--kRound == 0) break;
    GetPreviousRoundKey();
    InvMixColumns();
  }
}
void XorWithIv(const uint8_t* iv) {
  for (uint8_t i = 0; i < kAESBlockLength; ++i) {kState[i] ^= iv[i];}
}
void ResetKey() {
  for (uint8_t i = 0; i < kAESBlockLength; ++i) kRoundKey[i] = kKey[i];
}
void AES_CBC_encrypt_buffer(const uint8_t* iv, uint8_t length) {
  for (uint8_t i = 0; i < length; i += kAESBlockLength) {
    ResetKey();
    XorWithIv(iv);
    Cipher();
    iv = kState;
    kState += kAESBlockLength;
  }
}
inline void GetFinalRoundKey() {
  for (kRound = 1; kRound <= kAESRoundNumber; ++kRound) GetNextRoundKey();
}
void AES_CBC_decrypt_buffer(const uint8_t* iv, uint8_t length) {
  kState += length;
  const uint8_t* current_iv = kState - kAESBlockLength;
  uint8_t i = length;
  while (1) {
    i -= kAESBlockLength;
    kState -= kAESBlockLength;
    current_iv -= kAESBlockLength;
    ResetKey();
    GetFinalRoundKey();
    InvCipher();
    if (i == 0) current_iv = iv;
    XorWithIv(current_iv);
    if (i < kAESBlockLength) break;
  }
}
