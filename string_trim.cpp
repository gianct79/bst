/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <vector>


std::size_t trim_and_compress_spaces(char *s, std::size_t len) {
    // trim left
    std::size_t r = 0;
    while (r < len && std::isspace(s[r]))
        r++;

    std::size_t w = 0;
    while (r < len) {
        s[w++] = s[r++];
        if (r < len && std::isspace(s[r])) {
            s[w++] = s[r];
            while (r < len && std::isspace(s[r]))
                r++;
        }
    }
    if (w && len > w)
        s[--w] = 0;

    return w;
}


int main() {
    std::string s;
    while (std::getline(std::cin, s)) {
        std::vector<char> buffer(s.begin(), s.end());
        auto len = trim_and_compress_spaces(buffer.data(), buffer.size());
        s = {buffer.data(), len};
        std::cout << len << " \'" << s << "'\n";
    }
}
