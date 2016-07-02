#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*void move_odds(vector<int> &a) {
	int i = 0;
	int j = a.size() - 1;
	while (i < j) {
		// find first even
		while (i < j && (a[i] % 2 == 0))
			i++;
		// find last odd
		while (i < j && (a[j] % 2 == 1))
			j--;
		if (i < j) {
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
}*/

void move_odds(vector<int> &a) {
	int i = 0;
	int j = a.size() - 1;
	while (i < j) {
		// find first even
		while (i < j && (a[i] % 2 == 0))
			i++;
		// find last odd
		while (i < j && (a[j] % 2 == 1))
			j--;
		if (i < j) {
			//cout << i << ' ' << j << '\n';
			//j--;
			a.insert(a.begin() + j, a[i]);
			a.erase(a.begin() + i);
			//j--;
		}
	}
}

/*void move_odds(vector<int> &a) {
	int i = 0;
	int j = a.size() - 1;
    do {
        while (i <= j && (a[i] & 1) == 0) { i++; }
        while (i <= j && (a[j] & 1) != 0) { j--; }

        if (i >= j) {
            return;
        }

		swap(a[i], a[j]);

    } while (true);
}*/

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (auto &i : a)
			cin >> i;
		move_odds(a);
		for (auto &i : a)
			cout << i << ' ';
		cout << '\n';
	}
	return 0;
}
