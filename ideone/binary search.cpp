#include <iostream>

using namespace std;

int binary_search(int a[], int t, int l, int r) {
    if (l > r)
        return -1;
    int m = l + (r - l) / 2;
    if (a[m] < t)
        return binary_search(a, t, m + 1, r);
    else if (a[m] > t)
        return binary_search(a, t, l, m - 1);
    else
        return m;
}

int main() {
    int a[] = { 1, 2, 3, 4, 5, 6, 7 };
    int i;
    while (cin >> i) {
        cout << binary_search(a, i, 0, 6) << '\n';
    }
    return 0;
}