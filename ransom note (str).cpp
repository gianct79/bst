#include <iostream>

using namespace std;

bool ransom_note(string const &magazine, string const &ransom) {
    int count[128] = {0};
    for (auto &c : magazine) {
        count[c]++;
    }
    for (auto &c : ransom) {
        if (!count[c]) {
            return false;
        }
        count[c]--;
    }
    return true;
}

int main() {

    cout << ransom_note("oi, seu bundao", "fuck you, you") << '\n';
    cout << ransom_note("the quick brown fox jumps over the lazy dog", "abcdefghijklmnopqrstuvwxyz") << '\n';

    return 0;
}
