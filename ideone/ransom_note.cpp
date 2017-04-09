#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

bool ransom_note(vector<string> magazine, vector<string> ransom) {
    unordered_multiset<string> dict;
    for (string &s : magazine) {
        dict.insert(s);
    }
    for (string &s : ransom) {
        auto it = dict.find(s);
        if (it != dict.end()) {
            dict.erase(it);
        } else {
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
