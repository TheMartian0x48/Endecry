#ifndef ENDECRY_SRC_HASH__SHA1_
#define ENDECRY_SRC_HASH__SHA1_

#include <hash_function.hpp>
#include <array>
#include <istream>
#include <cstdlib>

class SHA1 : public HashFunction {
  std::array<uint32_t, 4> K{0X5A827999, 0X6ED9EBA1, 0X8F1BBCDC, 0XCA62C1D6};
  static uint32_t F(uint32_t, uint32_t, uint32_t, uint32_t);
  static inline uint32_t LeftShift(uint32_t, uint8_t);
  void ComputeHash(unsigned char *,
                   std::array<uint32_t, 80> &,
                   uint32_t &, uint32_t &, uint32_t &, uint32_t &, uint32_t &);

public:
  std::vector<uint8_t> GenerateHash(std::istream &) override;
};

#endif
