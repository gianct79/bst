#include <iostream>
#include <vector>

using namespace std;

// sum implementation
int missing_number(vector<int> const &v) {
    int sum = (v.size() + 1) * (v.size() + 2) / 2;   
    for (auto &i : v)
        sum -= i;
    return sum;
}

// XOR implementation
/*int missing_number(vector<int> const &v) {
    int x1 = v[0];
    int x2 = 1;
    for (int i = 1; i < v.size(); ++i)
        x1 ^= v[i];
    for (int i = 2; i <= v.size() + 1; ++i)
        x2 ^= i;
    return (x1 ^ x2);
}*/

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (auto &c : v) {
            cin >> c;
        }
        cout << missing_number(v) << '\n';
    }
    return 0;
}
