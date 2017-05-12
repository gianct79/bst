#include <iostream>
#include <vector>

using namespace std;

template<typename T>
int lower_bound(vector<T> const &a, T const &x) {
    int l = 0;
    int h = a.size();
    while (l < h) {
        int mid = l + (h - l) / 2;
        if (x <= a[mid]) {
            h = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int main() {
    vector<int> a = { 0, 1, 1, 2, 2, 2, 3, 4, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9 };
    cout << lower_bound(a, 0) << '\n';
    cout << lower_bound(a, 8) << '\n';
    cout << lower_bound(a, 5) << '\n';
    cout << lower_bound(a, 9) << '\n';
    cout << lower_bound(a, 1) << '\n';
    cout << lower_bound(a, 10) << '\n'; // acho que estourou
    return 0;
}
