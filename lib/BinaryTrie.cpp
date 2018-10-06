
#include "BinaryTrie.h"

BinaryTrie::BinaryTrie() : cur_pos(0), trie(1) {}

BinaryTrie::BinaryTrie(std::vector<uint64_t> const &codes, std::vector<uint8_t> &lens) : trie(1), cur_pos(0){
    trie.reserve(511);
    unsigned char i = 0;
    do {
        int pos = 0;

        for (unsigned char j = lens[i]; j-- > 0;) {
            bool direction = codes[i] & (1ULL << j);
            uint16_t to = direction ? trie[pos].r : trie[pos].l;
            if (to == node::nullpointer) {
                to = trie.size();
                trie.emplace_back(
                );
                if (direction) {
                    trie[pos].r = to;
                } else {
                    trie[pos].l = to;
                }
            }
            pos = to;
        }
        trie[pos].leaf = true;
        trie[pos].c = i;
    } while (++i != 0);

}

bool BinaryTrie::isTerminal() const {
    return trie[cur_pos].leaf;
}

void BinaryTrie::step(bool direction) {
    cur_pos = direction ? trie[cur_pos].r : trie[cur_pos].l;
}

void BinaryTrie::reset() {
    cur_pos = 0;
}

unsigned char BinaryTrie::getChar() const {
    return static_cast<unsigned char>(trie[cur_pos].c);
}
