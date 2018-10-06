//
// Created by qw on 05.10.18.
//

#ifndef HUFFMAN_BUFFERED_WRITER_H
#define HUFFMAN_BUFFERED_WRITER_H


#include <ostream>

class BufferedWriter {
public:
    explicit BufferedWriter(std::ostream &stream);
    ~BufferedWriter();
    void write(unsigned char const &c);
private:
    char buf[1 << 15];
    size_t pos;
    std::ostream &stream;
    void flush();
};


#endif //HUFFMAN_BUFFERED_WRITER_H
