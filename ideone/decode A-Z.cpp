#include <iostream>
#include <string>

using namespace std;

int num_dec(string const &buf) {

    int cnt1 = buf.size() == 0 ? 0 : 1, cnt2 = cnt1;

    for (int i = 1; i <= buf.size(); ++i) {

        char c = buf[i - 1];
        char p = i > 1 ? buf[i - 2] : '-';

        int temp = cnt2;

        if (c == '0')
            cnt2 = 0;

        if (p == '1' || (p == '2' && c <= '6'))
            cnt2 += cnt1;  

        cnt1 = temp;
    }
    return cnt2;
}

int main() {
    string s;
    while (cin >> s) {
        cout << s << ':' << num_dec(s) << '\n';
    }
    return 0;
}