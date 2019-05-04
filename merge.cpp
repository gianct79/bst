#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

// 5,25 10,20 30,40
// 5,10 15,20 25,30 25,40
// 1,2 3,4 5,6 7,8
// 0,1 0,2 0,3,0,4
int main() {

    int n;
    cin >> n;

    vector<pair<int, int>> v(n);

    for (auto &i : v) {
        cin >> i.first >> i.second;
    }

    sort(v.begin(), v.end());

    stack<pair<int, int>> s;
    s.push(v[0]);

    for (int i = 1; i < n; ++i) {

        auto e = s.top();
        if (e.second > v[i].first) {
            s.pop();
            s.push(make_pair(e.first, max(e.second, v[i].second)));
        } else {
            s.push(v[i]);
        }
    }

    while (!s.empty()) {
        cout << '(' << s.top().first << ',' << s.top().second << ')';
        s.pop();
    }

    return 0;
}
