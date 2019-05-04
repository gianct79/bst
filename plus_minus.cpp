#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    unsigned pos = 0;
    unsigned neg = 0;
    unsigned zer = 0;

    unsigned cnt;
    cin >> cnt;

    for (unsigned c = 0; c < cnt; ++c) {
        int i; cin >> i;
        if (i < 0)
            neg++;
        else if (i > 0)
            pos++;
        else
            zer++;
    }

    cout << setprecision(3)
        << pos / static_cast<float>(cnt) << '\n'
        << neg / static_cast<float>(cnt) << '\n'
        << zer / static_cast<float>(cnt);

    return 0;
}
