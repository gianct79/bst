/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>


int gcd_r(int x, int y) {
    if (x < y)
        return gcd_r(y, x);

    return y == 0 ? x : gcd_r(y, x % y);
}


int gcd_i(int x, int y) {
    if (x < y)
        std::swap(x, y);

    while (y > 0) {
        auto f = x % y;
        x = y;
        y = f;
    }
    return x;
}


int lcm(int x, int y) {
    return x == 0 ? 0 : x * y / gcd_i(x, y);
}


int main() {
    int x, y;
    while (std::cin >> x >> y) {
        std::cout << gcd_r(x, y) << '\t' << lcm(x, y) << '\n';
    }

    return 0;
}