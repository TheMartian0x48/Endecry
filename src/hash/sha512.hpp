#ifndef ENDECRY_SRC_HASH_SHA512_
#define ENDECRY_SRC_HASH_SHA512_

#include <hash_function.hpp>
#include <array>
#include <istream>

class SHA512 : public HashFunction {
  std::array<uint64_t, 80> K{
      0X428a2f98d728ae22, 0X7137449123ef65cd, 0Xb5c0fbcfec4d3b2f, 0Xe9b5dba58189dbbc,
      0X3956c25bf348b538, 0X59f111f1b605d019, 0X923f82a4af194f9b, 0Xab1c5ed5da6d8118,
      0Xd807aa98a3030242, 0X12835b0145706fbe, 0X243185be4ee4b28c, 0X550c7dc3d5ffb4e2,
      0X72be5d74f27b896f, 0X80deb1fe3b1696b1, 0X9bdc06a725c71235, 0Xc19bf174cf692694,
      0Xe49b69c19ef14ad2, 0Xefbe4786384f25e3, 0X0fc19dc68b8cd5b5, 0X240ca1cc77ac9c65,
      0X2de92c6f592b0275, 0X4a7484aa6ea6e483, 0X5cb0a9dcbd41fbd4, 0X76f988da831153b5,
      0X983e5152ee66dfab, 0Xa831c66d2db43210, 0Xb00327c898fb213f, 0Xbf597fc7beef0ee4,
      0Xc6e00bf33da88fc2, 0Xd5a79147930aa725, 0X06ca6351e003826f, 0X142929670a0e6e70,
      0X27b70a8546d22ffc, 0X2e1b21385c26c926, 0X4d2c6dfc5ac42aed, 0X53380d139d95b3df,
      0X650a73548baf63de, 0X766a0abb3c77b2a8, 0X81c2c92e47edaee6, 0X92722c851482353b,
      0Xa2bfe8a14cf10364, 0Xa81a664bbc423001, 0Xc24b8b70d0f89791, 0Xc76c51a30654be30,
      0Xd192e819d6ef5218, 0Xd69906245565a910, 0Xf40e35855771202a, 0X106aa07032bbd1b8,
      0X19a4c116b8d2d0c8, 0X1e376c085141ab53, 0X2748774cdf8eeb99, 0X34b0bcb5e19b48a8,
      0X391c0cb3c5c95a63, 0X4ed8aa4ae3418acb, 0X5b9cca4f7763e373, 0X682e6ff3d6b2b8a3,
      0X748f82ee5defb2fc, 0X78a5636f43172f60, 0X84c87814a1f0ab72, 0X8cc702081a6439ec,
      0X90befffa23631e28, 0Xa4506cebde82bde9, 0Xbef9a3f7b2c67915, 0Xc67178f2e372532b,
      0Xca273eceea26619c, 0Xd186b8c721c0c207, 0Xeada7dd6cde0eb1e, 0Xf57d4f7fee6ed178,
      0X06f067aa72176fba, 0X0a637dc5a2c898a6, 0X113f9804bef90dae, 0X1b710b35131c471b,
      0X28db77f523047d84, 0X32caab7b40c72493, 0X3c9ebe0a15c9bebc, 0X431d67c49c100d4c,
      0X4cc5d4becb3e42b6, 0X597f299cfc657e2a, 0X5fcb6fab3ad6faec, 0X6c44198c4a475817
  };
  void ComputeHash(unsigned char *,
                   std::array<uint64_t, 80>&,
                   uint64_t&, uint64_t&, uint64_t&, uint64_t&,
                   uint64_t&, uint64_t&, uint64_t&, uint64_t&);
 public:
  std::vector<uint8_t> GenerateHash(std::istream&) override;
};

#endif 