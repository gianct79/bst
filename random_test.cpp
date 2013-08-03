/*
 * Copyleft 1979-2013 GTO Inc. All rights reversed.
 */

#include <iostream>
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

int main() {

    int_rand rnd(1, 10);

    for (int i = 0; i < 10; ++i)
        cout << rnd() << ' ';

    return 0;
}
