#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void sum(vector<T> v, T s) {

    if (v.size() < 2)
        return;

    for (auto f = v.begin(), b = v.end() - 1; f < b;) {
        T t = *f + *b;
        if (t > s)
            b--;
        else if (t < s)
            f++;
        else
            cout << *f++ << ',' << *b-- << ';';
    }
    cout << '\n';
}

int main() {

    vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    sum(v, 9);

    v = {};
    sum(v, 0);

    v = {1};
    sum(v, 1);

    v = {1,2};
    sum(v, 3);

    v = {0,0};
    sum(v, 1);

    v = {0,1,2};
    sum(v, 2);

    return 0;
}