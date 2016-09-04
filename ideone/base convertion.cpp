#include <iostream>

using namespace std;

string to_base(int n, int base) {
    const char *alpha = "0123456789abcdef";

    string buf;
    div_t d = { n, 0 };

    do {
        d = div(d.quot, base);
        buf += alpha[d.rem];
    } while (d.quot);

    return { buf.rbegin(), buf.rend() };
}

int main() {
    for (int i = 0; i < 100; ++i)
        cout << i << ':' << to_base(i, 2) << '\n';
    return 0;
}
