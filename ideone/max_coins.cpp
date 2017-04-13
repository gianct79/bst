#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int max_coins(vector<int> const &A) {

    auto n = A.size();

    int table[n][n];
    std::memset(table, 0, sizeof(table));

    for (int gap = 0; gap < n; ++gap) {
        for (int i = 0, j = gap; j < n; ++i, ++j) {
            int x = ((i + 2) <= j) ? table[i+2][j] : 0;
            int y = ((i + 1) <= (j - 1)) ? table[i+1][j-1] : 0;
            int z = (i <= (j-2)) ? table[i][j-2]: 0;

            table[i][j] = std::max(A[i] + std::min(x, y), A[j] + std::min(y, z));
        }
    }

    return table[0][n-1];
}

int main() {
    cout << max_coins({1, 2, 3, 4}) << '\n';
    return 0;
}
