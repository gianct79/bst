#include <iostream>
#include <vector>

using namespace std;
using Number = vector<int>;

Number sum(Number const &a, const Number &b) {
    Number r;
    bool n = (a[0] < 0 ^ b[0] < 0);
    auto i = a.rbegin();
    auto j = b.rbegin();
    bool c = false;
    while (*i || *j) {
        auto a = 0;
        if (*i)
            n ? a -= *i++ : a += *i++;
        if (*j)
            n ? a -= *j++ : a += *j++;
        a += c ? 1 : 0;
        c = a >= 10;
        r.push_back(c ? a - 10 : a);
    }
    return Number { r.rbegin(), r.rend() };
}

int main() {

    Number a = { -1, 9, 9 };
    Number b = { 1 };

    Number c = sum(a, b);

    for (auto &i : c) {
        cout << i;
    }

    return 0;
}
