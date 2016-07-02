#include <iostream>

unsigned popcount(unsigned i) {
    unsigned count = 0;
    while (i) {
        ++count;
        i = i & (i - 1);
    }
    return count;
}

unsigned popCount(unsigned i) {
    unsigned count = 0;
    while (i) {
        count += i & 0x1;
        i = i >> 1;
    }
    return count;
}

int main() {
    std::cout << popcount(0b00000000) << '\n';
    std::cout << popcount(0b00000001) << '\n';
    std::cout << popcount(0b00100001) << '\n';
    std::cout << popcount(0b11111111) << '\n';
    std::cout << popcount(0b1111111111110000) << '\n';

    std::cout << popCount(0b00000000) << '\n';
    std::cout << popCount(0b00000001) << '\n';
    std::cout << popCount(0b00100001) << '\n';
    std::cout << popCount(0b11111111) << '\n';
    std::cout << popCount(0b1111111111110000) << '\n';

    return 0;
}
