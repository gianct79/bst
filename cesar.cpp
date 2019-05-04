#include <iostream>
#include <vector>

using namespace std;

/*using alphabet = vector<char>;

alphabet create_cipher(unsigned k) {
    k %= 26;
    alphabet A;
    char X = 'A' + k;
    for (auto x = X; x <= 'Z'; ++x)
        A.push_back(x);
    for (auto x = 'A'; x < X; ++x)
        A.push_back(x);
    return A;
}*/

char encode(char c, unsigned k) {
	if (!isalpha(c))
		return c;
	auto const complement = 'z' - c;
	return k < complement ? c + k : c + (k - complement);
}

int main() {

    int k;
    string s;

    cin >> s >> k;

    /*alphabet cipher = create_cipher(k);
    for (auto &c : s) {
        if (islower(c))
            c = tolower(cipher[toupper(c) - 'A']);
        else if (isupper(c))
            c = cipher[c - 'A'];
    }*/

    for (auto &c : s) {
    	c = encode(c, k);
	}
	
    cout << s << '\n';
}