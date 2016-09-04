#include <iostream>
#include <set>
#include <cmath>

using namespace std;

set<int> generate_perfect_squares(unsigned limit) {
    set<int> result;
    for (unsigned i = 1; i <= limit; ++i) {
        result.insert(i * i); 
    }
    return result;
}

unsigned count_perfect_squares(unsigned lbound, unsigned ubound) {
    unsigned cnt = 0;
    for (unsigned i = ceil(sqrt(lbound)); i * i <= ubound; ++i) {
        ++cnt;	
    }
    return cnt;
}

int main() {

    unsigned lbound, ubound;
    cin >> lbound >> ubound;

    cout << count_perfect_squares(lbound, ubound);

    /*set<int> perfect_squares = generate_perfect_squares(100);
    unsigned cnt = 0;
    for (; lbound <= ubound; ++lbound) {
        if (perfect_squares.count(lbound))
            cnt++;
    }
    cout << cnt << '\n';*/
    
    return 0;
}