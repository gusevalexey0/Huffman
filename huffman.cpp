#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "compression.h"
int main(int argc, char **argv) {
    if (argc != 4 || (std::string(argv[1]) != "-c" && std::string(argv[1]) != "-d")) {
        std::cout << "Usage: huffman [-c|-d] %source% %destination%";
        return 0;
    }

    std::string src = argv[2];
    std::string dest = argv[3];

    std::ifstream source;
    std::ofstream destination;

    source.open(src, std::ios::binary);
    destination.open(dest, std::ios::binary);

    std::clock_t time = clock();
    if (std::string(argv[1]) == "-c") {
        encode(source, destination);
    } else {
        decode(source, destination);
    }

    std::cerr << "Time spent:" << std::setprecision(3) << double(clock() - time) / CLOCKS_PER_SEC << " sec."
              << std::endl;
}
