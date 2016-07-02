#include <iostream>
#include <vector>

using namespace std;

void move_zeros(vector<int> &a) {
	int i = 0;
	int j = a.size() - 1;
	do {
		while (i < j && a[i] != 0)
			i++;
		while (j > i && a[j] == 0)
			j--;
		if (i < j)
			swap(a[i], a[j]);
	} while (i++ < j--);
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (auto &i : a)
			cin >> i;
		move_zeros(a);
		for (auto &i : a)
			cout << i << ' ';
		cout << '\n';
	}
	return 0;
}
