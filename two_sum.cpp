/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <fstream>

#include <vector>
#include <algorithm>

using namespace std;

class two_sum_naive {

    vector<long> _a;
    size_t _cnt;

public:

    two_sum_naive(const vector<long> &a) : _a(a.begin(), a.end()), _cnt(0) {
        sort(_a.begin(), _a.end());
    }

    size_t count(const long &sum) {
        for (size_t i = 0; i < _a.size(); ++i) {
            for (size_t j = 0; j < _a.size(); ++j) {
                if (i != j && _a[i] != _a[j] && _a[i] + _a[j] == sum) {
                    _cnt++; break;
                }
            }
        }
        return _cnt;
    }

    size_t get_count() const { return _cnt; }
};

class two_sum_bst {

    vector<long> _a;
    size_t _cnt;

public:

    two_sum_bst(const vector<long> &a) : _a(a.begin(), a.end()), _cnt(0) {
        auto last = unique(_a.begin(), _a.end());
        _a.erase(last + 1, _a.end());
        sort(_a.begin(), _a.end());        
    }

    size_t count(const long &sum) {
        size_t l = 0;
        size_t r = _a.size() - 1;
        while (r > 0 && l < r) {
            long s = _a[l] + _a[r];
            if (s == sum) {
                //cout << _a[l] << '+' << _a[r] << '=' << s << '\n'; 
                _cnt++; break;
            } else if (s < sum) {
                l++;
            } else {
                r--;
            }
        }
        return _cnt;
    }

    size_t get_count() const { return _cnt; }
};

int main(int argc, char* argv[]) {

    vector<long> list;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in);
        long l;
        while (ifs >> l) {
            list.push_back(l);
        }
    }

    cout << "list count: " << list.size() << '\n';

    two_sum_bst two_b(list);
    for (long l = -10000; l <= 10000; ++l) {
        two_b.count(l);
    }
    cout << "sum  count: " << two_b.get_count() << '\n';

    /*two_sum_fast two_f(list);
    for (long l = -10000; l <= 10000; ++l) {
        two_f.count(l);
    }
    cout << "sumf count: " << two_f.get_count() << '\n';

    two_sum_naive two_n(list);
    for (long l = -10000; l <= 10000; ++l) {
        two_n.count(l);
    }
    cout << "sumn count: " << two_n.get_count() << '\n';*/

    return 0;
}
