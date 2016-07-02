#include <iostream>
#include <vector>

using namespace std;

using int_list = vector<int>;

void diff_2(int_list &list, int diff) {
    for (auto i = list.begin(), j = list.begin() + 1; i < j; ) {
        int d = *j - *i;
        if (d > diff) {
            i++;
        } else if (d < diff) {
            j++;
        } else {
            cout << *i << ':' << *j << '\n';
            i++;
            j++;
        }
    }
}


int main() {

    int_list list = { 1, 2, 3, 4, 5 };

    diff_2(list, 2);

    return 0;
}
