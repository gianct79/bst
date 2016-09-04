#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using Board = vector<vector<int>>;

void dfs(int i, int j, Board& board) {
    // bounds check
    if (i < 0 || i > board.size() - 1 ||
        j < 0 || j > board[i].size() - 1)
        return;

    // "visited" check
    if (board[i][j] == 0)
        return;

    int cnt = 1;
    board[i][j] = 0; // mark "visited"

    dfs(i - 1, j, board); // n
    dfs(i - 1, j + 1, board); // ne
    dfs(i, j + 1, board); // e
    dfs(i + 1, j + 1, board); // se
    dfs(i + 1, j, board); // s
    dfs(i + 1, j - 1, board); // sw
    dfs(i, j - 1, board); // w
    dfs(i - 1, j - 1, board); // nw
}

int main() {
    int m, n;
    cin >> m >> n;
    Board board(m);

    for (int i = 0; i < m; ++i) {
        board[i].resize(n);
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
        }
    }

    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j){
            if (board[i][j] == 1) {
                cnt++;
                dfs(i, j, board);
            }
        }
    }
    cout << cnt << '\n';

    return 0;
}
