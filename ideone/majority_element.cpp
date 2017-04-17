#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    vector<int> v;
    int i;
    while (cin >> i) {
        v.push_back(i);
    }
    auto n = v.size();
    map<int, int> m; // element count
    int ans = 0;
    for (auto &i : v) {
        m[i]++;
        if (m[i] > (n/2)) {
            // if count greater than n/2, it is major element
            ans = i;
        }
    }
    cout << ans << '\n';
    return 0;
}
