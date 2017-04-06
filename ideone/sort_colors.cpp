#include <iostream>
#include <vector>

using namespace std;

void sortColors(vector<int> &A) {
	if (A.size() < 2) {
        return;
    }

    vector<int> color(3);
    for (auto &i : A) {
        color[i]++;
    }

    for (int i = 0, j = 0; j < 3; ++j) {
    while (color[j]-- > 0)
        A[i++] = j;
    }
}

int main() {
    int n; cin >> n;
    vector<int> colors(n);
    for (auto &i : colors) {
        cin >> i;
    }
    sortColors(colors);
    for (auto &i : colors) {
        cout << i << ' ';
    }
    return 0;
}
