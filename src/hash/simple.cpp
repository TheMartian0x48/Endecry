#include "simple.hpp"

std::string Simple::get(std::vector<uint8_t> &hash) {
  std::string result;
  const std::string hex{"0123456789abcdef"};
  for (auto h : hash) {
    result.push_back(hex[h >> 4]);
    result.push_back(hex[h & 15]);
  }
  return result;
}
