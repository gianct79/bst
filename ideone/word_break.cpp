#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// helper function (not good)
/*bool wordBreak(string const &str, unordered_set<string> const &dict) {
    int sz = str.size();
    if (sz == 0) {
        return true;
    }
    for (int i = 1; i <= sz; ++i) {
        // check whether current prefix is in dictionary
        // recursively check for remaining string suffix of length size-i
        if (dict.count(str.substr(0, i)) && wordBreak(str.substr(i, sz - i), dict)) {
            return true;
        }
    }
    // tried all prefixes and none worked
    return false;
}*/

// helper function (memorize steps)
bool wordBreak(string const &str, unordered_set<string> const &dict) {
    int sz = str.size();
    if (sz == 0) {
        return true;
    }
    vector<bool> wb(sz + 1);
    wb[0] = true;
    for (int i = 1; i <= sz; ++i) {
        for (int j = i-1; j >= 0; --j) {
            if (wb[j]) {
                auto word = str.substr(j, i-j);
                if (dict.count(word)) {
                    wb[i] = true;
                    break;
                }
            }
        }
    }
    return wb[sz];
}

int main() {
    unordered_set<string> dict { "bbba", "aaaa", "abaa", "aba", "aabaaa", "baabbaab", "bbbabbbaaa", "abaabbbbba", "abaa", "aba", "bbabbbbabb", "aab", "baaabbbaaa", "b", "baba", "aaba", "baaba", "abb", "aaaa", "baaabbbaa", "ab" };
    cout << wordBreak("babbbbaabbaabaabaabaaabaababaaaabbbbbabbaabbabbbbababaabbabbbabbbaaabaababaaaababbbbabbbbbbaaaabaaabaabbbaaaabaaabbbaabababbbaaaabbabbbabaaabbbabaaabbbaaaaaabaabbabbaabbbbbaababbbbabbabbaabbbabaababaaaabbaabbbaabaabbbbbbaabbbaaaabbaaaaaabaabbaababbbabbbbbbaabbaabbbabbbaabbbaaaabbbaaaabbbabbaababaaabbababbaabbabbabaabbbbaaaabbaababababbbbbabbbbabbaaabbaabaaaaabbaaaaaaaaaaababaaabbbaababbbbbbbabbababbaabbaaaababbbabbaaabbbbbabbbaabbaaaaabbbbbbabbbbbabbabbbabbabbababbabaabaabbabababbababaababbaababbabaabbaaaabbbaa", dict) << '\n';
    return 0;
}
