#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v;
    int n;
    while (cin >> n) {
        auto it = lower_bound(v.begin(), v.end(), n);
        v.insert(it, n);
        auto i = v.size() / 2;
        if (v.size() & 1) {
            cout << *(v.begin() + i) << '\n';
        } else {
            cout << 0.5d * (double(*(v.begin() + i)) + double(*(v.rbegin() + i))) << '\n';
        }
    }
}
