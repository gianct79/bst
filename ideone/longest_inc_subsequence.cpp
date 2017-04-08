#include <iostream>
#include <vector>

using namespace std;

int lis(vector<int> const &A) {
    auto n = A.size();
    vector<int> lis(n, 1);

    int i, j, max = 0;

    for (i = 1; i < n; ++i) {
        for (j = 0; j < i; ++j) {
            if (A[i] > A[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    for (i = 0; i < n; ++i) {
        if (max < lis[i]) {
            max = lis[i];
        }
    }

    return max;
}
    
int main() {
    vector<int> A { 10, 22, 9, 33, 21, 50, 41, 60 };
    cout << lis(A) << '\n';
    return 0;
}
