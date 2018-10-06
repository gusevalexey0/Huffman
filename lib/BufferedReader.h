
#ifndef HUFFMAN_BUFFERED_READER_H
#define HUFFMAN_BUFFERED_READER_H


#include <istream>

const size_t SIZE = (1 << 15);

class BufferedReader {
public:
    explicit BufferedReader(std::istream &stream);
    bool read(unsigned char &c);
    void reset();
private:
    char buf[SIZE];
    std::size_t pos, cur_size;
    std::istream &stream;
    void load();
};


#endif //HUFFMAN_BUFFERED_READER_H
