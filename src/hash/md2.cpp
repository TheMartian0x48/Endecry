#include "md2.hpp"

// void MD2::Checksum(const std::array<uint8_t, 16> &input, std::array<uint8_t, 16> &checksum, uint8_t &L){
//   for (uint8_t i = 0; i < 16; i++) {
//     checksum[i] ^= S[input[i] ^ L];
//     L = checksum[i];
//   }
// }

// void MD2::Update(const std::array<uint8_t, 16> &input, std::array<uint8_t, 48> &md_buffer){
//   for (uint8_t i = 0; i < 16; i++) {
//     md_buffer[16 + i] = input[i];
//     md_buffer[32 + i] = md_buffer[16 + i] ^ md_buffer[i];
//   }
//   uint8_t t = 0;
//   for (uint8_t round = 0; round < 18; round++) {
//     for (uint8_t k = 0; k < 48; k++) {
//       md_buffer[k] ^= S[t];
//       t = md_buffer[k];
//     }
//     t = (t + round) % 256;
//   }
// }

// std::vector<uint8_t> MD2::GenerateHash(std::istream& in) {
//   std::array<uint8_t, 16> input{}, checksum{};
//   std::array<uint8_t, 48> md_buffer{};
//   checksum.fill(0), md_buffer.fill(0);
// 
//   char ch;
//   uint8_t len = 0, L = 0;
// 
//   while (in.get(ch)) {
//     input[len] = ch;
//     len = (len + 1) % 16;
//     if (len == 0) {
//       Checksum(input, checksum, L);
//       Update(input, md_buffer);
//     }
//   }
// 
//   uint8_t padding_len = 16 - len;
//   for (uint8_t i = len; i < 16; i++) {
//     input[i] = (uint8_t) padding_len;
//   }
//   Checksum(input, checksum, L);
//   Update(input, md_buffer);
//   Update(checksum, md_buffer);
//   std::vector<uint8_t> hash(16);
//   for (int i = 0; i < 16; i++) {
//     hash[i] = md_buffer[i];
//   }
//   md_buffer.fill(0), checksum.fill(0), input.fill(0);
//   return move(hash);
// }

void MD2::Checksum(const unsigned char *input, std::array<uint8_t, 16> &checksum, uint8_t &L){
  for (uint8_t i = 0; i < 16; i++) {
    checksum[i] ^= S[input[i] ^ L];
    L = checksum[i];
  }
}

void MD2::Update(const unsigned char *input, std::array<uint8_t, 48> &md_buffer){
  for (uint8_t i = 0; i < 16; i++) {
    md_buffer[16 + i] = input[i];
    md_buffer[32 + i] = md_buffer[16 + i] ^ md_buffer[i];
  }
  uint8_t t = 0;
  for (uint8_t round = 0; round < 18; round++) {
    for (uint8_t k = 0; k < 48; k++) {
      md_buffer[k] ^= S[t];
      t = md_buffer[k];
    }
    t = (t + round) % 256;
  }
}


std::vector<uint8_t> MD2::GenerateHash(std::istream& in) {
  std::array<uint8_t, 16> checksum{};
  std::array<uint8_t, 48> md_buffer{};
  checksum.fill(0), md_buffer.fill(0);

  unsigned char msg[16];
  uint8_t len = 0, L = 0;

  while(true) {
    in.read((char *)msg, 16 - len);
    len += in.gcount();
    if (len == 16) {
      len = 0;
      Checksum(msg, checksum, L);
      Update(msg, md_buffer);
    } else if (in.eof()) {
      break;
    }
  }
  uint8_t padding_len = 16 - len;
  for (uint8_t i = len; i < 16; i++) {
    msg[i] = (uint8_t) padding_len;
  }
  Checksum(msg, checksum, L);
  Update(msg, md_buffer);
  for (int i = 0; i < 16; i++) {
    msg[i] = checksum[i];
  }
  Update(msg, md_buffer);
  std::vector<uint8_t> hash(16);
  for (int i = 0; i < 16; i++) {
    hash[i] = md_buffer[i];
  }
  md_buffer.fill(0), checksum.fill(0);
  for (int i = 0; i < 16; i++) msg[i] = 0;
  return move(hash);
}