/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>

std::size_t count_words(std::istream &stream) {

    std::size_t word = 0, cnt = 0;

    while (stream) {
        auto c = stream.get();

        if (std::isspace(c)) {
            if (cnt)
                word++;
            cnt = 0;
        } else {
            cnt++;
        }
    }

    if (cnt)
        word++;

    return word;
}

int main() {
    std::stringstream ss{"the quick brown fox jumps over the lazy dog"};
    std::cout << count_words(ss) << '\n';

    std::cout << count_words(std::cin) << '\n';

    return 0;
}
