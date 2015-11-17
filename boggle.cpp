#include <iostream>
#include <fstream>
#include <array>
#include <set>
#include <random>
#include "prefix_tree.h"

using namespace std;

using boggle_board = array<array<char, 4>, 4>;
using word_list = vector<string>;

unsigned slow_rng() {
    static random_device rng;
    return rng();
}

unsigned fast_rng() {
    static mt19937 rng(slow_rng());
    return rng();
}

boggle_board build_random_boggle_board() {
    boggle_board board;
    // a clowny but simple way to build a random boggle board
    for (auto y = board.size(); y--; ) {
        auto &line = board[y];
        for (auto x = line.size(); x--; ) {
            line[x] = 'a' + (fast_rng() % 26);
        }
    }
    return board;
}

boggle_board build_fixed_boggle_board() {
    boggle_board board { 
        't', 'h', 'e',
        's', 'e', 'a',
        'e', 'h', 't'
    };
    return board;
}

ostream &operator<<(ostream &out, boggle_board const &board) {
    for (auto y = 0; y < board.size(); ++y) {
        auto const &line = board[y];
        for (auto x = 0; x < line.size(); ++x) {
            cout << line[x] << ' ';
        }
        cout << '\n';
    }
    return out;
}

prefix_tree build_dictionary() {
    prefix_tree out;
    ifstream input("brit-a-z.txt");
    if (!input) {
        system("curl \"http://www.curlewcommunications.co.uk/resource/british.zip\" -o british.zip");
        system("unzip british.zip");
        input.open("brit-a-z.txt");
    }
    for (string s; input >> s; ) {
        out.add_word(s);
    }
    return out;
}

using board_pos = pair<unsigned, unsigned>;
using visited_set = set<board_pos>;
using word_set = set<string>;

void solve_boggle(prefix_tree::node *root, boggle_board const &board,
    board_pos const &pos, word_set &words, visited_set &visited, string word)
{
    if (!root || visited.count(pos))
        return;

    auto y = pos.first;
    auto x = pos.second;

    if (x < 0 || x > board.size() - 1 ||
        y < 0 || y > board.size() - 1)
        return;

    visited.insert(pos);

    if (root->word && !words.count(word)) {
        words.insert(word);
    }

    auto c = board[y][x];

    board_pos n = make_pair(y - 1, x);
    board_pos ne = make_pair(y - 1, x + 1);
    board_pos e = make_pair(y, x + 1);
    board_pos se = make_pair(y + 1, x + 1);
    board_pos s = make_pair(y + 1, x);
    board_pos sw = make_pair(y + 1, x - 1);
    board_pos w = make_pair(y, x - 1);
    board_pos nw = make_pair(y - 1, x - 1);

    solve_boggle(root->next[c].get(), board, n, words, visited, word + c);
    solve_boggle(root->next[c].get(), board, ne, words, visited, word + c);
    solve_boggle(root->next[c].get(), board, e, words, visited, word + c);
    solve_boggle(root->next[c].get(), board, se, words, visited, word + c);
    solve_boggle(root->next[c].get(), board, s, words, visited, word + c);
    solve_boggle(root->next[c].get(), board, sw, words, visited, word + c);
    solve_boggle(root->next[c].get(), board, w, words, visited, word + c);
    solve_boggle(root->next[c].get(), board, nw, words, visited, word + c);
}

word_set solve_boggle(prefix_tree const &dict, boggle_board const &board) {
    word_set words;
    for (auto y = 0; y < board.size(); ++y) {
        for (auto x = 0; x < board.size(); ++x) {
            visited_set visited;
            solve_boggle(dict.root.get(), board, make_pair(y, x), words, visited, "");
        }
    }
    return words;
}


int main() {
    auto dict = build_dictionary();
    cout << "prefix tree size is " << dict.size() << '\n';

    auto board = build_random_boggle_board();
    //auto board = build_fixed_boggle_board();
    cout << board;

    auto result = solve_boggle(dict, board);
    cout << "found " << result.size() << " words from the dictionary in the board";
    for (auto const &i: result) {
        cout << " '" << i << '\'';
    }
    cout << '\n';

    return 0;
}
