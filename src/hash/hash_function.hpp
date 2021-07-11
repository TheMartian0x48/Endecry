#ifndef UDECRY_SRC_HASH_HASH_FUNCTION_H_
#define UDECRY_SRC_HASH_HASH_FUNCTION_H_

#include <vector>
#include <cstdint>
#include <istream>

class HashFunction{
  public:
    virtual std::vector<uint8_t> GenerateHash(std::istream&) = 0;
};

#endif
