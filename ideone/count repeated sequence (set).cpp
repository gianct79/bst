#include <iostream>
#include <set>

using namespace std;

struct bucha {
    bool operator()(string const &a, string const &b) {
        return a.length() > b.length();
    }
};

int main() {

    string s;
    cin >> s;

    set<string, bucha> a;

    if (s.length()) {
        string t {s[0]};
        for (int i = 1; i < s.length(); ++i) {
            if (s[i - 1] != s[i]) {
                a.insert(t);
                t.clear();
            }
            t += s[i];
        }
        a.insert(t);
        cout << *a.begin() << '\n';
    }
    return 0;
}
