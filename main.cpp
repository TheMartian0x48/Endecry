#include <hash.hpp>
#include <simple.hpp>
#include <md2.hpp>
// #include <md4.h>
// #include <sha1.h>
// #include <sha224.h>
// #include <sha256.h>
// #include <sha384.h>
// #include <sha512.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
using namespace std;
int main() {
  std::string name = "output";
  // cout << "file : ";
  // cin >> name;
  std::ifstream fin(name, std::ios::binary);
  std::shared_ptr<HashOutputFormat> si = std::make_shared<Simple>();
  std::shared_ptr<HashFunction> mh = std::make_shared<MD2>();
  Hash hash(mh, si);
  // cout << "#test : ";
  // int test; cin >> test;
  // while(test--) {
  //   string text;
  //   cout << "text: ";
  //   cin >> text;
    // stringstream fin(text);
    std::istream ss(fin.rdbuf());
    hash.GenerateHash(ss);
    auto res = hash.get_hash();
    std::cout << res << std::endl;
  // }
}