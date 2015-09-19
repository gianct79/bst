/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>

template<typename T>
std::pair <T, T> binary_division(T a, T b) {

    size_t diff = 1;

    while (b < a) {
        ++diff;
        b <<= 1;
    }

    T result = 0;

    while (diff--) {
        result <<= 1;

        if (a >= b) {
            a -= b;
            result |= 1;
        }

        b >>= 1;
    }

    return std::make_pair(result, a);
}

int main() {

    unsigned a, b;
    while (std::cin >> a >> b) {
        auto r = binary_division(a, b);
        std::cout << r.first << '.' << r.second << '\n';
    }

    return 0;
}
