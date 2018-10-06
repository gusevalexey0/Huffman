
#include "BufferedReader.h"

BufferedReader::BufferedReader(std::istream &stream) : stream(stream) {
    load();
}

void BufferedReader::load() {
    stream.read(buf, SIZE);
    cur_size = static_cast<size_t>(stream.gcount());
    pos = 0;
}

bool BufferedReader::read(unsigned char &c) {
    if (pos < cur_size) {
        c = buf[pos++];
        return true;
    } else {
        load();
        if (pos < cur_size) {
            c = buf[pos++];
            return true;
        } else {
            return false;
        }
    }
}

void BufferedReader::reset() {
    stream.clear();
    stream.seekg(0);
}
