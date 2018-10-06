cmake_minimum_required(VERSION 3.12)
project(huffman)

set(CMAKE_CXX_STANDARD 17)

add_executable(huffman huffman.cpp lib/BufferedReader.cpp lib/BufferedReader.h lib/BufferedWriter.cpp lib/BufferedWriter.h lib/BinaryTrie.cpp lib/BinaryTrie.h compression.cpp compression.h )
add_executable(huffmanTesting huffmanTesting.cpp)
