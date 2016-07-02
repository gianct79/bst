#include <iostream>
#include <vector>

using namespace std;
using alphabet = vector<char>;

const unsigned SIZE = 26;

alphabet create_cipher(unsigned k) {
    k %= SIZE;
    alphabet A;
    char X = 'A' + k;
    for (auto x = X; x <= 'Z'; ++x)
        A.push_back(x);
    for (auto x = 'A'; x < X; ++x)
        A.push_back(x);
    return A;
}

char cipher_char(char c, unsigned k) {
    k %= SIZE;
    char x = c + k;
    if (x > 'Z')
        x -= SIZE;
    return x;
}

int main() {

    int k;
    string s;

    cin >> s >> k;
    alphabet cipher = create_cipher(k);
    for (auto &c : s) {
        if (islower(c))
        	c = tolower(cipher_char(toupper(c), k));
            //c = tolower(cipher[toupper(c) - 'A']);
        else if (isupper(c))
        	c = cipher_char(c, k);
            //c = cipher[c - 'A'];
    }
   	cout << s << '\n';
}