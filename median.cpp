#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> d;
    int n;
    cin >> n;
    while (n--) {
        char o; int v;
        cin >> o >> v;
        if (o == 'a') {
            auto it = upper_bound(d.begin(), d.end(), v);
            d.insert(it, v);
        } else if (o == 'r') {
            auto it = lower_bound(d.begin(), d.end(), v);
            if (it == d.end() || (*it != v)) {
                cout << "Wrong!\n";
            } else {
                d.erase(it);
            }
        }
        if (d.size()) {
            int i = d.size() / 2;
            if (d.size() % 2 == 0) {
                cout << 0.5 * (double(d[i - 1]) + double(d[i])) << '\n';
            } else if (d.size()) {
                cout << d[i] << '\n';
            }
        }
    }
    if (d.empty()) {
        cout << "Wrong!\n";
    }
    return 0;
}
