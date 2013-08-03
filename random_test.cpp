/*
 * Copyleft 1979-2013 GTO Inc. All rights reversed.
 */

#include <iostream>
#include <list>

#include <random>

using namespace std;

class int_rand {

    random_device _rd;
    mt19937 _gen;

    uniform_int_distribution<> _dist;
    
public:
    int_rand(int lo, int hi) : _gen { _rd() }, _dist { lo, hi } {
    }

    int operator()() {
        return _dist(_gen);
    }
};

template <typename T>
T random_element(T begin, T end) {

    const size_t n = distance(begin, end);
    cout << "n: " << n << ' ';

    int_rand rnd(0, n - 1);

    advance(begin, rnd());

    return begin;
}


int main() {

    list<int> values { 1, 7, 10, 3 };

    for (auto i : values)
        cout << i << ' ';

    cout << '\n';

    for (int i = 0; i < 10; ++i)
        cout << *random_element(values.begin() , values.end()) << '\n';

    return 0;
}
