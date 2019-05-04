#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

int main()
{
    int m, n, r;
    cin >> m >> n >> r;

    Matrix M(m);
    for (int i = 0; i < m; ++i) {
        M[i].resize(n);
        for (int j = 0; j < n; ++j)
            cin >> M[i][j];
    }

    if (r %= m * n) {
        int lv = std::min(n, m) / 2;

        Matrix R(lv);
        for (int l = 0; l < lv; l++) {
            int t = (n - 1) - 2 * l;
            int s = (m - 1) - 2 * l;
            for (int i = 0; i < t; ++i) // top
                R[l].push_back(M[l][l + i]);
            for (int j = 0; j < s; ++j) // right
                R[l].push_back(M[l + j][l + t]);
            for (int i = 0; i < t; ++i) // bottom
                R[l].push_back(M[l + s][l + t - i]);
            for (int j = 0; j < s; ++j) // left
                R[l].push_back(M[l + s - j][l]); 
        }

        /*for (int l = 0; l < R.size(); ++l) {
            cout << "\nl" << l << ':';
            for (auto &i : R[l])
                cout << i << ',';
        }*/

        for (int l = 0; l < R.size(); ++l) {
            int rr = r % R[l].size();
            std::rotate(R[l].begin(), R[l].begin() + rr, R[l].end());
            int t = (n - 1) - 2 * l;
            int s = (m - 1) - 2 * l;
            for (int i = 0; i < t; ++i) { // top
                M[l][l + i] = R[l].front();
                R[l].erase(R[l].begin());
            }
            for (int j = 0; j < s; ++j) { // right
                M[l + j][l + t] = R[l].front();
                R[l].erase(R[l].begin());
            }
            for (int i = 0; i < t; ++i) { // bottom
                M[l + s][l + t - i] = R[l].front();
                R[l].erase(R[l].begin());
            }
            for (int j = 0; j < s; ++j) { // left
                M[l + s - j][l] = R[l].front();
                R[l].erase(R[l].begin());
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            cout << M[i][j] << ' ';
        cout << '\n';
    }

    return 0;
}
