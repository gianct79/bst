/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <string>
#include <cmath>
#include <queue>

std::string gt_itoa(int n) {
    std::string buf;
    std::div_t d = {n, 0};

    do {
        d = std::div(d.quot, 10);
        buf += std::abs(d.rem) + '0';
    } while (d.quot);

    if (n < 0)
        buf += '-';

    return {buf.rbegin(), buf.rend()};
}

int gt_atoi(std::string const &s) {
    int acc = 0;
    int base = 1;

    for (auto it = s.rbegin(); it < s.rend(); ++it, base *= 10) {
        if (*it == '-') {
            acc *= -1;
        } else {
            acc += (*it - '0') * base;
        }
    }

    return acc;
}

int main() {
    std::queue<int> values;

    std::string s;
    while (std::cin >> s) {
        values.push(gt_atoi(s));
        std::cout << values.back() << '\n';
    }

    while (!values.empty()) {
        std::cout << gt_itoa(values.front()) << '\n';
        values.pop();
    }

    return 0;
}