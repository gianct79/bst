#include <iostream>
#include <vector>

using namespace std;

int canJump(vector<int> const &A) {
    auto n = A.size();
    if (n == 1 && A[0] == 0) {
        return 1;
    }
    auto max = A[0];
    for (auto i = 0; i < n; ++i) {
        if (max <= i && A[i] == 0) {
            return 0;
        }
        max = std::max(max, i + A[i]);
        if (max >= n) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (auto &i : A) {
        cin >> i;
    }
    cout << canJump(A) << '\n';
    return 0;
}
