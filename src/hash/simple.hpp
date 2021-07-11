#ifndef ENDECRY_SRC_HASH_SIMPLE_
#define ENDECRY_SRC_HASH_SIMPLE_

#include "hash_output_format.hpp"
#include <string>
#include <vector>

class Simple : public HashOutputFormat {
  public:
    std::string get(std::vector<uint8_t>&) override;
};

#endif
