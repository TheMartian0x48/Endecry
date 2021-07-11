#include "sha1.hpp"

std::vector<uint8_t> SHA1::GenerateHash(std::istream &in) {
  uint32_t H0 = 0X67452301, H1 = 0XEFCDAB89, H2 = 0X98BADCFE, H3 = 0X10325476, H4 = 0XC3D2E1F0;
  // std::array<uint8_t, 64> M{0};
  std::array<uint32_t, 80> Buffer{0};
  unsigned char M[64];

  // char ch;
  uint8_t index = 0;
  uint32_t bit_lower_len = 0, bit_higher_len = 0;

  while(true) {
    in.read((char *)M, 64 - index);
    uint8_t tmp = in.gcount();
    index += tmp;
    uint32_t gained_space = (uint32_t)tmp * 8;
    uint32_t remain_space = UINT32_MAX - gained_space;
    if (gained_space > remain_space) {
      bit_higher_len++;
      bit_lower_len = gained_space - remain_space;
    } else {
      bit_lower_len += gained_space; 
    }

    if (index == 64) {
      index = 0;
      ComputeHash(M, Buffer, H0, H1, H2, H3, H4);
    } else if (in.eof()) {
      break;
    }
  }

  // padding
  if (index > 55) {
    M[index] = 0X80;
    for (++index; index < 64; index++) {
      M[index] = 0;
    }
    ComputeHash(M, Buffer, H0, H1, H2, H3, H4);
    for (index = 0; index < 56; index++) {
      M[index] = 0;
    }
  }
  else if (index < 56) {
    M[index] = 0X80;
    for (++index; index < 56; index++) {
      M[index] = 0;
    }
  }
  // append length
  M[56] = bit_higher_len >> 24, M[57] = bit_higher_len >> 16, M[58] = bit_higher_len >> 8, M[59] = bit_higher_len;
  M[60] = bit_lower_len >> 24, M[61] = bit_lower_len >> 16, M[62] = bit_lower_len >> 8, M[63] = bit_lower_len;
  // final call
  ComputeHash(M, Buffer, H0, H1, H2, H3, H4);
  std::vector<uint8_t> result(20);
  result[0] = H0 >> 24;
  result[1] = H0 >> 16;
  result[2] = H0 >> 8;
  result[3] = H0;
  result[4] = H1 >> 24;
  result[5] = H1 >> 16;
  result[6] = H1 >> 8;
  result[7] = H1;
  result[8] = H2 >> 24;
  result[9] = H2 >> 16;
  result[10] = H2 >> 8;
  result[11] = H2;
  result[12] = H3 >> 24;
  result[13] = H3 >> 16;
  result[14] = H3 >> 8;
  result[15] = H3;
  result[16] = H4 >> 24;
  result[17] = H4 >> 16;
  result[18] = H4 >> 8;
  result[19] = H4;
  //zeros everything
  Buffer.fill(0);
  for (uint8_t i = 0; i < 64; i++) {
    M[i] = 0;
  }
  H0 = H1 = H2 = H3 = H4 = 0;
  bit_lower_len = 0, bit_higher_len = 0;
  return move(result);
}

uint32_t SHA1::F(uint32_t t, uint32_t B, uint32_t C, uint32_t D) {
  if (t <= 19)
    return (B & C) | ((~B) & D);
  else if (t <= 39)
    return B ^ C ^ D;
  else if (t <= 59)
    return (B & C) | (B & D) | (C & D);
  return B ^ C ^ D;
}

uint32_t SHA1::LeftShift(uint32_t X, uint8_t n) {
  return (X << n) | (X >> (32 - n));
}

void SHA1::ComputeHash(unsigned char * M,
                       std::array<uint32_t, 80> &Buffer,
                       uint32_t &H0, uint32_t &H1, uint32_t &H2, uint32_t &H3, uint32_t &H4) {
  for (uint8_t i = 0; i < 16; i++) {
    Buffer[i] = (M[i * 4] << 24) | (M[i * 4 + 1] << 16) | (M[i * 4 + 2] << 8) | M[i * 4 + 3];
  }
  for (uint8_t i = 16; i < 80; i++) {
    Buffer[i] = LeftShift(
        Buffer[i - 3] ^ Buffer[i - 8] ^ Buffer[i - 14] ^ Buffer[i - 16],
        1);
  }
  uint32_t A = H0, B = H1, C = H2, D = H3, E = H4;
  for (uint8_t i = 0; i < 80; i++) {
    uint32_t T = LeftShift(A, 5) + F(i, B, C, D) + E + Buffer[i] + K[(uint8_t)(i / 20)];
    E = D, D = C, C = LeftShift(B, 30), B = A, A = T;
  }
  H0 += A;
  H1 += B;
  H2 += C;
  H3 += D;
  H4 += E;
}
