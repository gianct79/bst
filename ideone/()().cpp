#include <iostream>


void print(std::string &buf, unsigned pos, unsigned open, unsigned close) {

    unsigned n = buf.length() / 2;

    if (close == n) {
        std::cout << buf << '\n';
        return;
    }

    if (open < n) {
        buf[pos] = '(';
        print(buf, pos + 1, open + 1, close);
    }

    if (open > close) {
        buf[pos] = ')';
        print(buf, pos + 1, open, close + 1);
    }
}

int main() {

    std::string buf;

    unsigned n;
    while (std::cin >> n) {

        buf.resize(n * 2);
        print(buf, 0, 0, 0);
    }

    return 0;
}