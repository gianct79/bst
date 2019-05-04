#include <iostream>
#include <vector>

using namespace std;

string string_trim(string const &str) {
    string bf;
    bool f = false;
    for (unsigned i = 0; i < str.length();) {
        if (str[i] == '"') {
            f = !f;
        }
        if (isspace(str[i]) && !f) {
            i++;
        } else {
            bf += str[i++];
        }
    }
    return bf;
}

vector<string> pretty_JSON(string const &str) {
    vector<string> r;
    string bf, in, s = string_trim(str);
    for (unsigned i = 0; i < s.length(); i++) {
        switch (s[i]) {
            case '[':
            case '{': {
                if (bf.length()) {
                    r.push_back(in + bf);
                    bf.clear();
                }
                r.push_back(in + s[i]);
                in.push_back('\t');
            }
            break;
            case ']':
            case '}': {
                if (bf.length()) {
                    r.push_back(in + bf);
                    bf.clear();
                }
                in.pop_back();
                r.push_back(in + s[i]);
            }
            break;
            case ',': {
                if (bf.length()) {
                    r.push_back(in + bf);
                    bf.clear();
                }
                r[r.size() - 1] += s[i];
            }
            break;
            default: {
                bf += s[i];
            }
            break;            
        }
    }
    return r;
}

int main() {

    string s;
    while (getline(cin, s)) {
        auto r = pretty_JSON(s);
        for (auto &i : r)
            cout << i << '\n';
    }

    return 0;
}