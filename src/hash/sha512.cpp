#include "sha512.hpp"

std::vector<uint8_t> SHA512::GenerateHash(std::istream& in) {
  uint64_t H0 = 0X6a09e667f3bcc908, H1 = 0Xbb67ae8584caa73b, H2 = 0X3c6ef372fe94f82b, H3 = 0Xa54ff53a5f1d36f1;
  uint64_t H4 = 0X510e527fade682d1, H5 = 0X9b05688c2b3e6c1f, H6 = 0X1f83d9abfb41bd6b, H7 = 0X5be0cd19137e2179;
  // std::array<uint8_t, 128> M{0};
  std::array<uint64_t, 80> Buffer{0};
  // char ch;
  uint32_t index = 0;
  uint64_t bit_lower_len = 0, bit_higher_len = 0;
  // while (in.get(ch)){
  //   bit_lower_len += 8;
  //   if (bit_lower_len == 0) bit_higher_len++;
  //   M[index++] = ch;
  //   if (index == 128) {
  //     ComputeHash(M, Buffer, H0, H1, H2, H3, H4, H5, H6, H7);
  //     index = 0;
  //   }
  // }

  unsigned char M[128];
  while(true) {
    in.read((char *)M, 128 - index);
    uint8_t tmp = in.gcount();
    index += tmp;
    uint64_t gained_space = (uint64_t)tmp * 8;
    uint64_t remain_space = UINT64_MAX - gained_space;
    if (gained_space > remain_space) {
      bit_higher_len++;
      bit_lower_len = gained_space - remain_space;
    } else {
      bit_lower_len += gained_space; 
    }

    if (index == 128) {
      index = 0;
      ComputeHash(M, Buffer, H0, H1, H2, H3, H4, H5, H6, H7);
    } else if (in.eof()) {
      break;
    }
  }

  // padding
  if (index > 111) {
    M[index] = 0X80;
    for (++index; index < 128; index++) {
      M[index] = 0;
    }
    ComputeHash(M, Buffer, H0, H1, H2, H3, H4, H5, H6, H7);
    for (index = 0; index < 112; index++) {
      M[index] = 0;
    }
  } else if (index < 112) {
    M[index] = 0X80;
    for (++index; index < 112; index++) {
      M[index] = 0;
    }
  }
  // append length
  M[112] = bit_higher_len >> 56, M[113] = bit_higher_len >> 48, M[114] = bit_higher_len >> 40, M[115] = bit_higher_len >> 32;
  M[116] = bit_higher_len >> 24, M[117] = bit_higher_len >> 16, M[118] = bit_higher_len >> 8, M[119] = bit_higher_len;
  M[120] = bit_lower_len >> 56, M[121] = bit_lower_len >> 48, M[122] = bit_lower_len >> 40, M[123] = bit_lower_len >> 32;
  M[124] = bit_lower_len >> 24, M[125] = bit_lower_len >> 16, M[126] = bit_lower_len >> 8, M[127] = bit_lower_len;
  // final call
  ComputeHash(M, Buffer, H0, H1, H2, H3, H4, H5, H6, H7);
  std::vector<uint8_t> result(64);
  result[0] = H0 >> 56; result[1] = H0 >> 48; result[2] = H0 >> 40; result[3] = H0 >> 32;
  result[4] = H0 >> 24; result[5] = H0 >> 16; result[6] = H0 >> 8; result[7] = H0;
  result[8] = H1 >> 56; result[9] = H1 >> 48; result[10] = H1 >> 40; result[11] = H1 >> 32;
  result[12] = H1 >> 24; result[13] = H1 >> 16; result[14] = H1 >> 8; result[15] = H1;
  result[16] = H2 >> 56; result[17] = H2 >> 48; result[18] = H2 >> 40; result[19] = H2 >> 32;
  result[20] = H2 >> 24; result[21] = H2 >> 16; result[22] = H2 >> 8; result[23] = H2;
  result[24] = H3 >> 56; result[25] = H3 >> 48; result[26] = H3 >> 40; result[27] = H3 >> 32;
  result[28] = H3 >> 24; result[29] = H3 >> 16; result[30] = H3 >> 8; result[31] = H3;
  result[32] = H4 >> 56; result[33] = H4 >> 48; result[34] = H4 >> 40; result[35] = H4 >> 32;
  result[36] = H4 >> 24; result[37] = H4 >> 16; result[38] = H4 >> 8; result[39] = H4;
  result[40] = H5 >> 56; result[41] = H5 >> 48; result[42] = H5 >> 40; result[43] = H5 >> 32;
  result[44] = H5 >> 24; result[45] = H5 >> 16; result[46] = H5 >> 8; result[47] = H5;
  result[48] = H6 >> 56; result[49] = H6 >> 48; result[50] = H6 >> 40; result[51] = H6 >> 32;
  result[52] = H6 >> 24; result[53] = H6 >> 16; result[54] = H6 >> 8; result[55] = H6;
  result[56] = H7 >> 56; result[57] = H7 >> 48; result[58] = H7 >> 40; result[59] = H7 >> 32;
  result[60] = H7 >> 24; result[61] = H7 >> 16; result[62] = H7 >> 8; result[63] = H7;
  //zeros everything
  Buffer.fill(0);
  for (uint8_t i = 0; i < 128; i++) M[i] = 0;
  H0 = H1 = H2 = H3 = H4 = H5 = H6 = H7 = 0;
  bit_lower_len = 0, bit_higher_len = 0;
  return move(result);
}

void SHA512::ComputeHash(unsigned char * M,
                         std::array<uint64_t, 80>& Buffer,
                         uint64_t& H0, uint64_t& H1, uint64_t& H2, uint64_t& H3,
                         uint64_t& H4, uint64_t& H5, uint64_t& H6, uint64_t& H7) {
#define ROTR(x,n) (((x) >> (n)) | ((x) << (64 - n)))
//#define ROTL(x,n) (((x) << (n)) | ((x) >> (64 - n)))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define BSIG0(x) ((ROTR(x,28)) ^ (ROTR(x,34)) ^ (ROTR(x,39)))
#define BSIG1(x) ((ROTR(x,14)) ^ (ROTR(x,18)) ^ (ROTR(x,41)))
#define SSIG0(x) ((ROTR(x,1)) ^ (ROTR(x,8)) ^ ((x) >> 7))
#define SSIG1(x) ((ROTR(x,19)) ^ (ROTR(x,61)) ^ ((x) >> 6))

  for (uint8_t i = 0; i < 16; i++) {
    Buffer[i] = ((uint64_t)M[i * 8] << 56) | ((uint64_t)M[i * 8 + 1] << 48) | ((uint64_t)M[i * 8 + 2] << 40) | ((uint64_t)M[i * 8 + 3] << 32);
    Buffer[i] |= ((uint64_t)M[i * 8 + 4] << 24) | ((uint64_t)M[i * 8 + 5] << 16) | ((uint64_t)M[i * 8 + 6] << 8) | (uint64_t)M[i * 8 + 7];
  }

  for (uint8_t i = 16; i < 80; i++)  {
    Buffer[i] = SSIG1(Buffer[i - 2]) + Buffer[i - 7] + SSIG0(Buffer[i - 15]) + Buffer[i - 16];
  }
  uint64_t a = H0, b = H1, c = H2, d = H3, e = H4, f = H5, g = H6, h = H7;
  for (uint8_t i = 0; i < 80; i++) {
    uint64_t t1 = h + BSIG1(e) + CH(e,f,g) + K[i] + Buffer[i];
    uint64_t t2 = BSIG0(a) + MAJ(a,b,c);
    h = g, g = f, f = e, e = d + t1, d = c, c = b, b = a, a = t1 + t2;
  }
  H0 += a, H1 += b, H2 += c, H3 += d, H4 += e, H5 += f, H6 += g, H7 += h;
}