#include <iostream>
#include <vector>

using namespace std;

template<class T>
T median_element(vector<T> const &v) {
	auto i = v.begin();
	auto j = v.begin();
	while (j != v.end()) {
		i += 1;
		j += 2;
	}
	return *i;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> v(n);
		for (auto &i : v)
			cin >> i;
		cout << median_element(v) << '\n';
	}
	return 0;
}
