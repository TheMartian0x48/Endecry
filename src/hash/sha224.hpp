#ifndef ENDECRY_SRC_HASH_SHA224_
#define ENDECRY_SRC_HASH_SHA224_

#include <hash_function.hpp>
#include <array>
#include <istream>

class SHA224 : public HashFunction {
  std::array<uint32_t, 64> K{
      0X428a2f98,
      0X71374491,
      0Xb5c0fbcf,
      0Xe9b5dba5,
      0X3956c25b,
      0X59f111f1,
      0X923f82a4,
      0Xab1c5ed5,
      0Xd807aa98,
      0X12835b01,
      0X243185be,
      0X550c7dc3,
      0X72be5d74,
      0X80deb1fe,
      0X9bdc06a7,
      0Xc19bf174,
      0Xe49b69c1,
      0Xefbe4786,
      0X0fc19dc6,
      0X240ca1cc,
      0X2de92c6f,
      0X4a7484aa,
      0X5cb0a9dc,
      0X76f988da,
      0X983e5152,
      0Xa831c66d,
      0Xb00327c8,
      0Xbf597fc7,
      0Xc6e00bf3,
      0Xd5a79147,
      0X06ca6351,
      0X14292967,
      0X27b70a85,
      0X2e1b2138,
      0X4d2c6dfc,
      0X53380d13,
      0X650a7354,
      0X766a0abb,
      0X81c2c92e,
      0X92722c85,
      0Xa2bfe8a1,
      0Xa81a664b,
      0Xc24b8b70,
      0Xc76c51a3,
      0Xd192e819,
      0Xd6990624,
      0Xf40e3585,
      0X106aa070,
      0X19a4c116,
      0X1e376c08,
      0X2748774c,
      0X34b0bcb5,
      0X391c0cb3,
      0X4ed8aa4a,
      0X5b9cca4f,
      0X682e6ff3,
      0X748f82ee,
      0X78a5636f,
      0X84c87814,
      0X8cc70208,
      0X90befffa,
      0Xa4506ceb,
      0Xbef9a3f7,
      0Xc67178f2,
  };
  void ComputeHash(unsigned char *,
                   std::array<uint32_t, 80> &,
                   uint32_t &, uint32_t &, uint32_t &, uint32_t &,
                   uint32_t &, uint32_t &, uint32_t &, uint32_t &);

public:
  std::vector<uint8_t> GenerateHash(std::istream &) override;
};

#endif
