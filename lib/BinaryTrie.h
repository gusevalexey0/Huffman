#ifndef HUFFMAN_BINARYTRIE_H
#define HUFFMAN_BINARYTRIE_H


#include <vector>
#include <cstdint>

class BinaryTrie {
public:
    BinaryTrie();
    BinaryTrie(std::vector<uint64_t> const &codes, std::vector<uint8_t> &lens);
    bool isTerminal() const;
    void step(bool direction);
    void reset();
    unsigned char getChar() const;

private:
    struct node {
        const static uint16_t nullpointer = -1;
        uint16_t l, r;
        bool leaf;
        char c;

        node() : leaf(false), l(nullpointer), r(nullpointer) {}
    };

    uint16_t cur_pos;
    std::vector<node> trie;
};


#endif //HUFFMAN_BINARYTRIE_H
