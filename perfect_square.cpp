#include <iostream>
#include <set>

using namespace std;

set<int> generate_perfect_squares(unsigned limit) {

    set<int> result;
    
    for (unsigned i = 1; i <= limit; ++i) {
        result.insert(i * i); 
    }

    return std::move(result);
}

int main() {

    unsigned lbound, ubound;
    cin >> lbound >> ubound;

    set<int> perfect_squares = generate_perfect_squares(100);
    
    unsigned cnt = 0;
    for (; lbound <= ubound; ++lbound) {
        if (perfect_squares.count(lbound))
            cnt++;
    }
    cout << cnt << '\n';
    
    return 0;
}