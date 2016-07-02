#include <iostream>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

void spiral_print(Matrix const &M) {

    int m = M.size();
    int n = M[0].size();

    int k = 0, l = 0;
 
    while (k < m && l < n) {

        for (int i = l; i < n; ++i) // top
            cout << M[k][i] << ' ';
        k++;
 
        for (int i = k; i < m; ++i) // right
            cout << M[i][n - 1] << ' ';
        n--;
 
        if (k < m) {
            for (int i = n - 1; i >= l; --i) // bottom
                cout << M[m - 1][i] << ' ';
            m--;
        }
 
        if (l < n)
        {
            for (int i = m - 1; i >= k; --i) // left
                cout << M[i][l] << ' ';
            l++;    
        }        
    }
}
 
int main() {
    int m, n;
    cin >> m >> n;

    Matrix M(m);

    for (int i = 0; i < m; ++i) {
        M[i].resize(n);
        for (int j = 0; j < n; ++j)
            cin >> M[i][j];
    }

    spiral_print(M);

    return 0;
}
