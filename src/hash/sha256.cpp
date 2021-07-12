#include "sha256.hpp"

std::vector<uint8_t> SHA256::GenerateHash(std::istream& in) {
  uint32_t H0 = 0X6a09e667, H1 = 0Xbb67ae85, H2 = 0X3c6ef372, H3 = 0Xa54ff53a;
  uint32_t H4 = 0X510e527f, H5 = 0X9b05688c, H6 = 0X1f83d9ab, H7 = 0X5be0cd19;
  std::array<uint32_t, 80> Buffer{0};
  unsigned char M[64];
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
      ComputeHash(M, Buffer, H0, H1, H2, H3, H4, H5, H6, H7);
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
    ComputeHash(M, Buffer, H0, H1, H2, H3, H4, H5, H6, H7);
    for (index = 0; index < 56; index++) {
      M[index] = 0;
    }
  } else if (index < 56) {
    M[index] = 0X80;
    for (++index; index < 56; index++) {
      M[index] = 0;
    }
  }
  // append length
  M[56] = bit_higher_len >> 24, M[57] = bit_higher_len >> 16, M[58] = bit_higher_len >> 8, M[59] = bit_higher_len;
  M[60] = bit_lower_len >> 24, M[61] = bit_lower_len >> 16, M[62] = bit_lower_len >> 8, M[63] = bit_lower_len;
  // final call
  ComputeHash(M, Buffer, H0, H1, H2, H3, H4, H5, H6, H7);
  std::vector<uint8_t> result(32);
  result[0] = H0 >> 24; result[1] = H0 >> 16; result[2] = H0 >> 8; result[3] = H0;
  result[4] = H1 >> 24; result[5] = H1 >> 16; result[6] = H1 >> 8; result[7] = H1;
  result[8] = H2 >> 24; result[9] = H2 >> 16; result[10] = H2 >> 8; result[11] = H2;
  result[12] = H3 >> 24; result[13] = H3 >> 16; result[14] = H3 >> 8; result[15] = H3;
  result[16] = H4 >> 24; result[17] = H4 >> 16; result[18] = H4 >> 8; result[19] = H4;
  result[20] = H5 >> 24; result[21] = H5 >> 16; result[22] = H5 >> 8; result[23] = H5;
  result[24] = H6 >> 24; result[25] = H6 >> 16; result[26] = H6 >> 8; result[27] = H6;
  result[28] = H7 >> 24; result[29] = H7 >> 16; result[30] = H7 >> 8; result[31] = H7;
  //zeros everything
  Buffer.fill(0);
  for (int i = 0; i < 64; i++) M[i] = 0;
  H0 = H1 = H2 = H3 = H4 = H5 = H6 = H7 = 0;
  bit_lower_len = 0, bit_higher_len = 0;
  return move(result);
}

void SHA256::ComputeHash(unsigned char * M,
                         std::array<uint32_t, 80>& Buffer,
                         uint32_t& H0, uint32_t& H1, uint32_t& H2, uint32_t& H3,
                         uint32_t& H4, uint32_t& H5, uint32_t& H6, uint32_t& H7) {
#define ROTR(x,n) (((x) >> (n)) | ((x) << (32 - n)))
//#define ROTL(x,n) (((x) << (n)) | ((x) >> (32 - n)))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & y) ^ ((x) & (z)) ^ ((y) & (z)))
#define BSIGO(x) ((ROTR(x,2)) ^ (ROTR(x,13)) ^ (ROTR(x,22)))
#define BSIG1(x) ((ROTR(x,6)) ^ (ROTR(x,11)) ^ (ROTR(x,25)))
#define SSIG0(x) ((ROTR(x,7)) ^ (ROTR(x,18)) ^ ((x) >> 3))
#define SSIG1(x) ((ROTR(x,17)) ^ (ROTR(x,19)) ^ ((x) >> 10))

  for (uint8_t i = 0; i < 16; i++) {
    Buffer[i] = (M[i * 4] << 24) | (M[i * 4 + 1] << 16) | (M[i * 4 + 2] << 8) | M[i * 4 + 3];
  }

  for (uint8_t i = 16; i < 64; i++)  {
    Buffer[i] = SSIG1(Buffer[i - 2]) + Buffer[i - 7] + SSIG0(Buffer[i - 15]) + Buffer[i - 16];
  }
  uint32_t a = H0, b = H1, c = H2, d = H3, e = H4, f = H5, g = H6, h = H7;
  for (uint8_t i = 0; i < 64; i++) {
    uint32_t t1 = h + BSIG1(e) + CH(e,f,g) + K[i] + Buffer[i];
    uint32_t t2 = BSIGO(a) + MAJ(a,b,c);
    h = g, g = f, f = e, e = d + t1, d = c, c = b, b = a, a = t1 + t2;
  }
  H0 += a, H1 += b, H2 += c, H3 += d, H4 += e, H5 += f, H6 += g, H7 += h;
}
