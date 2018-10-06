cmake_minimum_required(VERSION 3.12)
project(huffman)

set(CMAKE_CXX_STANDARD 17)



add_executable(huffman huffman.cpp)
add_executable(huffmanTesting huffmanTesting.cpp)

add_library(compression compression.cpp compression.h lib/BufferedReader.cpp lib/BufferedReader.h lib/BufferedWriter.cpp lib/BufferedWriter.h lib/BinaryTrie.cpp lib/BinaryTrie.h)

target_link_libraries(huffman compression)
target_link_libraries(huffmanTesting compression -lgtest)