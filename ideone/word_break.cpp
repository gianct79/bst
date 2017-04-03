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

    // try all prefixes of lengths from 1 to size
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

// helper function
bool wordBreak(string const &str, unordered_set<string> const &dict) {

    int sz = str.size();

    if (sz == 0) {
        return true;
    }

    // wb[i] will be true if str[0..i-1] can be segmented into dict words
    vector<bool> wb(sz + 1);

    // try all prefixes of lengths from 1 to size
    for (int i = 1; i <= sz; ++i) {
        
        // wb[i] is false, check if current prefix can make it true
        if (!wb[i] && dict.count(str.substr(0, i))) {
            wb[i] = true;
        }

        if (wb[i]) {
            // reached the last prefix
            if (i == sz) {
                return true;
            }

            for (int j = i + 1; j <= sz; ++j) {
                // update wb[j] if it can be updated
                if (wb[j] == false && dict.count(str.substr(i, j - i))) {
                    wb[j] = true;
                }

                // last character reached
                if (j == sz && wb[j]) {
                    return true;
                }
            }
        }
    }

    // tried all prefixes and none worked
    return false;
}

int main() {
    unordered_set<string> dict { "bbba", "aaaa", "abaa", "aba", "aabaaa", "baabbaab", "bbbabbbaaa", "abaabbbbba", "abaa", "aba", "bbabbbbabb", "aab", "baaabbbaaa", "b", "baba", "aaba", "baaba", "abb", "aaaa", "baaabbbaa", "ab" };
    cout << wordBreak("babbbbaabbaabaabaabaaabaababaaaabbbbbabbaabbabbbbababaabbabbbabbbaaabaababaaaababbbbabbbbbbaaaabaaabaabbbaaaabaaabbbaabababbbaaaabbabbbabaaabbbabaaabbbaaaaaabaabbabbaabbbbbaababbbbabbabbaabbbabaababaaaabbaabbbaabaabbbbbbaabbbaaaabbaaaaaabaabbaababbbabbbbbbaabbaabbbabbbaabbbaaaabbbaaaabbbabbaababaaabbababbaabbabbabaabbbbaaaabbaababababbbbbabbbbabbaaabbaabaaaaabbaaaaaaaaaaababaaabbbaababbbbbbbabbababbaabbaaaababbbabbaaabbbbbabbbaabbaaaaabbbbbbabbbbbabbabbbabbabbababbabaabaabbabababbababaababbaababbabaabbaaaabbbaa", dict) << '\n';
    return 0;
}
