#include "hash.hpp"

Hash::Hash() {
  hash_function_ = nullptr;
  hash_output_format_ = nullptr;
  hash_.clear();
}

Hash::Hash(std::shared_ptr<HashFunction> &function, std::shared_ptr<HashOutputFormat> &format) {
  hash_function_ = function;
  hash_output_format_ = format;
}
Hash::~Hash() {
  for (auto &e :  hash_) {
    e = 0;
  }
}
void Hash::GenerateHash(std::istream& plaintext) {
  if (hash_function_ != nullptr)
    hash_ = hash_function_->GenerateHash(plaintext);
}

void Hash::set_hash_function(std::shared_ptr<HashFunction>& function) {
  hash_function_ = function;
}

void Hash::set_hash_output_function(std::shared_ptr<HashOutputFormat>& format) {
  hash_output_format_ = format;
}

std::string Hash::get_hash() {
  if (hash_output_format_ == nullptr || hash_.empty()) return {};
  return hash_output_format_->get(hash_);
}