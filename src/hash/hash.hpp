#ifndef ENDECRY_SRC_HASH_HASH_
#define ENDECRY_SRC_HASH_HASH_

#include <memory>
#include <cstdint>
#include <istream>
#include <string>
#include "hash_output_format.hpp"
#include "hash_function.hpp"


class Hash{
  std::shared_ptr<HashOutputFormat> hash_output_format_;
  std::shared_ptr<HashFunction> hash_function_;
  std::vector<uint8_t> hash_;
 public:
  Hash();
  Hash(std::shared_ptr<HashFunction> &, std::shared_ptr<HashOutputFormat> &);
  ~Hash();
  void GenerateHash(std::istream&);
  void set_hash_function(std::shared_ptr<HashFunction>&);
  void set_hash_output_function(std::shared_ptr<HashOutputFormat>&); 
  std::string get_hash();
};

#endif
