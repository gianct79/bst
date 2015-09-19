/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>

void sort_string(std::string &s) {
    int i = s.size();
    int j = -1;

    do {
        while (s[--i] == '1');

        while (s[++j] == '0');

        if (i > j)
            std::swap(s[i], s[j]);

    } while (i > j);
}

int main() {
    std::string s;
    while (std::cin >> s) {
        sort_string(s);
        std::cout << s << '\n';
    }

    return 0;
}