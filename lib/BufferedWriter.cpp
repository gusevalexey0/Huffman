//
// Created by qw on 05.10.18.
//

#include "BufferedWriter.h"

BufferedWriter::BufferedWriter(std::ostream &stream) : stream(stream), pos(0) {}

const size_t SIZE = (1 << 15);
void BufferedWriter::write(unsigned char const &c) {
    if (pos < SIZE) {
        buf[pos++] = c;
    } else {
        flush();
        buf[pos++] = c;
    }

}

BufferedWriter::~BufferedWriter() {
    flush();
}

void BufferedWriter::flush() {
    stream.write(buf, pos);
    pos = 0;
}
