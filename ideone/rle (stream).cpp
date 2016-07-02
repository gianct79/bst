/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <sstream>
#include <fstream>


void encode(std::istream &in, std::ostream &out) {
    char read;
    if (in.get(read)) {
        unsigned count = 1;
        char next;
        while (in.get(next)) {
            if (next != read) {
                out << count << read;
                read = next;
                count = 1;
            } else {
                count++;
            }
        }
        out << count << read;
    }
}

void decode(std::istream &in, std::ostream &out) {
    char read;
    unsigned count;
    while (in >> count >> read) {
        while (count--) {
            out << read;
        }
    }
}


int main() {

    std::stringstream in{"abbcccddddeeeeeffffggghhi"};
    std::stringstream out{""};

    encode(in, out);
    std::cout << out.str() << '\n';

    decode(out, in);
    std::cout << in.str() << '\n';

    while (std::cin) {
        std::stringstream buf;

        encode(std::cin, buf);
        std::cout << buf.str() << '\n';

        decode(buf, std::cout);
    }

    return 0;
}