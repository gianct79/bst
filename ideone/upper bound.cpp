#include <iostream>

unsigned f(unsigned v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    return ++v;
}

unsigned g(unsigned v) {
    if (v < 2)
        return 1;
    v--;
    unsigned diff = 1;
    while (v >>= 1)
        diff++;
    v++;
    while (diff--)
        v <<= 1;
    return v;
}

int main() {
    for (auto i = 0; i < 128; i++) {
        std::cout << i << ':' << f(i) << ' ' << g(i) << '\n';	
    }
    return 0;
}