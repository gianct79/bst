#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, int> d;
    int n;
    cin >> n;
    while (n--) {
        char o; int v;
        cin >> o >> v;
        if (o == 'a') {
            d[v]++;
        } else if (o == 'x') {
            if (d.count(v)) {
                d[v]--;
                if (d[v] == 0) {
                    d.erase(v);
                }
            } else {
                cout << "Wrong!\n";
            }
        }
        if (d.size()) {
            int i = d.size() / 2;
            auto x = d.begin();
            auto y = d.rbegin();
            while (i--) {
                x++; y++;
            }
            cout << (x->first + y->first) / 2.0 << '\n';
        } else {
            cout << "Wrong!\n";
        }
    }
    return 0;
}
