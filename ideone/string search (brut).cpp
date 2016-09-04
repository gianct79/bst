#include <iostream>
#include <string>


int search(std::string const &s, std::string const &q) {

    unsigned n = s.size();
    unsigned m = q.size();

    unsigned i, j;

    for (i = 0, j = 0; i < n && j < m; ++i) {

        if (s[i] == q[j])
            j++;
        else {
            i -= j;
            j = 0;
        }
    }

    if (j == m)
        return i - m;
    else
        return -1;
}


int main() {

    std::string s, q;
    while (std::cin >> s && std::cin >> q)
        std::cout << search(s, q) << '\n';

    return 0;
}