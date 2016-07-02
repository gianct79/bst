#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int i, j;
	vector<pair<int, int>> v;
	while (cin >> i >> j) {
		v.push_back(make_pair(i , j));
	}
	sort(v.begin(), v.end());
	vector<pair<int, int>> m;
	m.push_back(v[0]);
	for (int i = 1; i < v.size(); ++i) {
		auto &l = m[m.size() - 1];
		if (l.second > v[i].first) {
			l.second = max(l.second, v[i].second);
		} else {
			m.push_back(make_pair(v[i].first, v[i].second));
		}
	}
	for (auto &i : m) {
		cout << '(' << i.first << ',' << i.second << ')';
	}
	return 0;
}