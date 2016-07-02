#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int rabin_karp(string const &s, string const &q) {

	hash<string> hash_fn;

	int n = s.length();
	int m = q.length();

	string ss { s.begin(), s.begin() + m };

	unsigned hs = hash_fn(ss);
	unsigned hq = hash_fn(q);

	for (int i = 0; i < (n - m) + 1; ++i) {
		if (hs == hq) {
			if (equal(ss.begin(), ss.end(), q.begin())) {
				return i;
			}
		}
		ss = { s.begin() + i, s.begin() + i + m };
		hs = hash_fn(ss);
	}

	return -1;
}

int main() {
	
	string s, q;
	while (cin >> s && cin >> q) {
		cout << rabin_karp(s, q) << '\n';
	}

	return 0;
}