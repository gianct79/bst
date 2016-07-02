#include <iostream>


void permute_string(std::string &s, unsigned sz) {

    if (sz == s.size()) {
        std::cout << s << ',';
    } else {
        for (auto i = sz; i < s.size(); ++i) {
            std::swap(s[i], s[sz]);
            permute_string(s, sz + 1);
            std::swap(s[i], s[sz]);
        }
    }
}

int main() {

    std::string s;
    while (std::cin >> s) {
        permute_string(s, 0);
        std::cout << '\n';
    }

    return 0;
}