add_library(
  hash 
  hash/hash.hpp 
  hash/hash.cpp
  )

add_library(
  hex 
  hash/hash_output_format.hpp 
  hash/simple.cpp 
  hash/simple.hpp
  )

add_library(
  md2 
  hash/md2.cpp 
  hash/md2.hpp
  )


add_library(
  sha1 
  hash/sha1.cpp 
  hash/sha1.hpp
  )

add_library(
  sha224 
  hash/sha224.cpp 
  hash/sha224.hpp
  )

add_library(
  sha256 
  hash/sha256.cpp 
  hash/sha256.hpp
  )

# add_library(sha384 sha384.cpp sha384.h)
# add_library(sha512 sha512.cpp sha512.h)

target_include_directories(hash PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/hash")
target_include_directories(hex PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/hash")
target_include_directories(md2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/hash")
target_include_directories(sha1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/hash")
target_include_directories(sha224 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/hash")
target_include_directories(sha256 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/hash")
# target_include_directories(sha384 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(sha512 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})