#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

bool ransom_note(vector<string> const &magazine, vector<string> const &ransom) {
    unordered_multiset<string> dict;
    for (string const &s : magazine) {
        dict.insert(s);
    }
    for (string const &s : ransom) {
        auto it = dict.find(s);
        if (it != dict.end()) {
            dict.erase(it);
        } else {
            return false;
        }
    }
    return true;
}

bool ransom_note_order(vector<string> const &magazine, vector<string> const &ransom) {
    for (auto  rit = ransom.begin(), mit = magazine.begin(); rit != ransom.end(); ++rit) {
        while (*rit != *mit && mit != magazine.end()) {
            ++mit;
        }
        if (mit == magazine.end()) {
            return false;
        }
    }
    return true;
}

int main(){
    int m, n;
    cin >> m >> n;
    vector<string> magazine(m);
    for (string &s : magazine){
       cin >> s;
    }
    vector<string> ransom(n);
    for (string &s : ransom) {
       cin >> s;
    }
    cout << (ransom_note(magazine, ransom) ? "yes" : "no") << '\n';

    return 0;
}
