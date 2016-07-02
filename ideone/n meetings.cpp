#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct meeting {
    int st, et;
};

bool operator<(meeting const &a, meeting const &b) {
	/*int da = a.et - a.st;
	int db = b.et - b.st;
    return da == db ? a.et < b.st : da < db;*/
    return a.et < b.et;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<meeting> m(n);
        for (auto &i : m)
            cin >> i.st;
        for (auto &i : m)
            cin >> i.et;
        sort(m.begin(), m.end());
		int i = 0;
        cout << '{' << m[i].st << ':' << m[i].et << '}';
        for (int j = 1; j < m.size(); ++j) {
			if (m[j].st >= m[i].et) {        	
            	cout << '{' << m[j].st << ':' << m[j].et << '}';
            	i = j;
			}
        }
    }
	return 0;
}
