#include <iostream>
#include <vector>

using namespace std;

struct version {

    const unsigned COMPONENTS = 3;
    unsigned value = 0;

    version(string const &s) {
        vector<int> v;
        for (unsigned i = 0; i < s.length(); ++i) {
            if (isdigit(s[i])) {
                int t = 0;
                for (; i < s.length() && isdigit(s[i]); ++i) {
                    t *= 10;
                    t += s[i] - '0';
                }
                v.push_back(t);
            }
        }
        for (unsigned i = v.size(); i < COMPONENTS; ++i) {
            v.push_back(0);
        }
        int b = 1;
        for (auto i = v.rbegin(); i != v.rend(); ++i) {
            value += (*i * b);
            b *= 100;
        }
    }

    int compare_to(version const &o) {
        if (value < o.value)
            return -1;
        else if (value > o.value)
            return 1;
        else
            return 0;
    }
};

int main() {

    string a, b;
    while (cin >> a >> b) {
        cout << version(a).compare_to(version(b)) << '\n';
    }
    return 0;
}