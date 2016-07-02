#include <iostream>
#include <queue>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        queue<string> q;
        q.push("1");
        for (int i = 1; i < n; ++i) {
            string s = q.front(); q.pop();
            cout << s << ',';
            string t = s;
            q.push(s.append("0"));
            q.push(t.append("1"));
        }
        cout << q.front() << '\n';
    }
	return 0;
}
