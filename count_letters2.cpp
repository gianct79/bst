#include <iostream>

using namespace std;

int main() {

    string s;
    cin >> s;

    if (s.length()) {

        int a[128] = { 0 };
        int i, cnt = 1;

        for (i = 1; i < s.length(); ++i) {
            if (s[i - 1] != s[i]) {
                if (cnt > a[s[i - 1]])
                    a[s[i - 1]] = cnt;
                cnt = 1;
            } else {
                cnt++;
            }
        }
        if (cnt > a[s[i + 1]])
            a[s[i + 1]] = cnt;

        int m = 0;
        for (i = 0; i < 128; ++i) {
            if (a[i] > a[m]) {
                m = i;
            }
        }
        cout << string(a[m], char(m)) << '\n';
    }

    return 0;
}
