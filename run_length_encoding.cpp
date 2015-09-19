/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <sstream>
#include <fstream>

void run_length_encoding(std::istream &stream) {
    if (stream) {
        size_t count = 1;

        auto read = stream.get();

        while (stream) {
            auto next = stream.get();

            if (next != read && next != -1) {
                std::cout << count << ' ' << read << ", ";
                read = next;
                count = 1;
            } else {
                count++;
            }
        }

        std::cout << count << ' ' << read << '\n';
    }
}


int main() {

    std::stringstream ss{"aaabcccdddddeeeeffgghhhiiijjjkk"};
    run_length_encoding(ss);

    while (std::cin)
        run_length_encoding(std::cin);

    return 0;
}
