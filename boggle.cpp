#include <iostream>
#include <array>
#include <stack>
#include <set>

using namespace std;

using boggle_board = array<array<char, 4>, 4>;
using coord = pair<unsigned, unsigned>;

ostream &operator<<(ostream &out, boggle_board const &board) {
    for (auto i = 0; i < board.size(); ++i) {
        for (auto j = 0; j < board[i].size(); j++) {
            out << board[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

void solve_boggle(unsigned i, unsigned j, boggle_board &board) {
    stack<coord> s;
    set<coord> v;
    s.push(make_pair(i, j));
    while (!s.empty()) {
        auto top = s.top(); s.pop();
        if (!v.count(top)) {
            auto i = top.first;
            auto j = top.second;
            //cout << i << ':' << j << ';';
            cout << board[i][j] << '-';
            if (i > 0) s.push(make_pair(i - 1, j));
            if (j > 0) s.push(make_pair(i, j - 1));
            if (i < board.size() - 1) s.push(make_pair(i + 1, j));
            if (j < board.size() - 1) s.push(make_pair(i, j + 1));
            v.insert(top);
        }
    }
    cout << '\n';
}

void solve_boggle(boggle_board &board) {
    for (auto i = 0; i < board.size(); ++i) {
        for (auto j = 0; j < board.size(); ++j) {
            solve_boggle(i, j, board);
        }
    }
}

int main() {

    boggle_board board = {
        'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p' };

    cout << board;

    solve_boggle(board);

    return 0;
}