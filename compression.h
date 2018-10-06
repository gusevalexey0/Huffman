
#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H
#include <iosfwd>
#include <vector>
#include <queue>
#include <algorithm>
#include "lib/BufferedReader.h"
#include "lib/BufferedWriter.h"
struct node {
    const static uint16_t nullpointer = -1;
    uint16_t left;
    uint16_t right;

    node() : left(nullpointer), right(nullpointer) {}

    node(int left, int right) : left(left), right(right) {}
};
std::vector<uint64_t> buildCodes(std::vector<unsigned char> const &lens);
void countLens(size_t v, unsigned char d, std::vector<node> const &tree, std::vector<unsigned char> &lens);
void encode(std::istream &input, std::ostream &output);
void decode(std::istream &input, std::ostream &output);
//void countLens(size_t v, uint16_t d, std::vector<node> const &tree, std::vector<unsigned char> &lens);
//std::vector<uint64_t> buildCodes(std::vector<unsigned char> const &lens);
//void encode(std::istream &source, std::ostream &destination);
#endif //HUFFMAN_COMPRESS_H
