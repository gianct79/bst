#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxProduct3(vector<int> &A) {
    std::sort(A.begin(), A.end());
    int n = A.size();
    return std::max(A[0] * A[1] * A[n - 1],
            A[n - 1] * A[n - 2] * A[n - 3]);
}	

int main() {
    std::vector<int> v;
    int i;
    while (cin >> i) {
        v.push_back(i);
    }
    cout << maxProduct3(v) <<  '\n';
    return 0;
}
