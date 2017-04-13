#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef unordered_map<int, vector<string>> MAPAO;

vector<string> word_break2(MAPAO &m, int const &i, string const &A, unordered_set<string> const &dict) {

    if (!m.count(i)) {
        for (int j = i+1; j <= A.size(); ++j) {
            if (dict.count(A.substr(i, j-i))) {
                for (string tail : word_break2(m, j, A, dict)) {
                    m[i].push_back(A.substr(i, j-i) + (tail == "" ? "" : ' ' + tail));
                }
            }
        }
    }

    return m[i];
}

int main() {

    string A = "catsanddog";
    unordered_set<string> dict {"cat", "cats", "and", "sand", "dog"};

    MAPAO m { {A.size(), {""}} };

    auto ret = word_break2(m, 0, A, dict);

    for (auto &s : ret) {
        cout << s << '\n';
    }

    return 0;
}
