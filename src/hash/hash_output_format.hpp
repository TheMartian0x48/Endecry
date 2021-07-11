#ifndef ENDECRY_SRC_HASH_OUTPUT_FORMAT
#define ENDECRY_SRC_HASH_OUTPUT_FORMAT

#include <string>
#include <vector>
#include <cstdint>

class HashOutputFormat{
  public:
    HashOutputFormat() = default;
    HashOutputFormat& operator=(const HashOutputFormat&) = delete;
    HashOutputFormat(const HashOutputFormat&) = default;
    HashOutputFormat(HashOutputFormat &&) = default;
    HashOutputFormat& operator=(const HashOutputFormat &&) = delete;
    ~HashOutputFormat() = default;
    virtual std::string get(std::vector<uint8_t>&) = 0;
};

#endif
