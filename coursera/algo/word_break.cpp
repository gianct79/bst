#include <iostream>
#include <unordered_set>

using namespace std;

// helper function
bool wordBreak(string const &str, unordered_set<string> const &dict) {

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
}

int main() {
    unordered_set<string> dict { "trainer", "my", "interview" };
    cout << wordBreak("myinterviewtrainer", dict) << '\n';
    return 0;
}
