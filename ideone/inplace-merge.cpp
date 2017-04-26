#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void inplaceMerge(vector<int> &a, vector<int> const &b) {

    int n = a.size();

    int pa = n - 1;
    int pb = n - 1;
    int end = 2 * n - 1;

    a.resize(n * 2);

    while ((pa >= 0) && (pb >= 0))   {
        a[end--] = (a[pa] > b[pb]) ? a[pa--] : b[pb--];
    }

    if (pb >= 0) {
        std::memcpy(&a[0], &b[0], sizeof(int) * (pb + 1));
    }
}

int main() {
    vector<int> a = { 1, 5, 6, 9 };
    vector<int> b = { 3, 4, 7, 10 };

    inplaceMerge(a, b);

    for (auto &i : a) {
        cout << i << ' ';
    }

    return 0;
}
