/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <fstream>

#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

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
                    _cnt++;
                    break;
                }
            }
        }
        return _cnt;
    }

    size_t get_count() const { return _cnt; }
};

class two_sum_fast {

    vector<long> _a;
    size_t _cnt;

public:

    two_sum_fast(const vector<long> &a) : _a(a.begin(), a.end()), _cnt(0) {
    }

    size_t count(const long &sum) {
        map<long, long> d;
        for (auto x : _a) {
            long l = sum - x;
            if (d.find(x) != d.end()) {
                continue;
            }
            if (d.find(l) != d.end()) {
                _cnt++; break;
            }
            d[x] = l;
        }
        return _cnt;
    }

    size_t get_count() const { return _cnt; }
};

class binary_search {
public:
    static bool find(long key, const vector<long> &a) {
        int lo = 0;
        int hi = a.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (key < a[mid])
                hi = mid - 1;
            else if (key > a[mid])
                lo = mid + 1;
            else
                return true;
        }
        return false;
    }
};

class two_sum_bin {

    vector<long> _a;
    size_t _cnt;

public:

    two_sum_bin(const vector<long> &a) : _a(a.begin(), a.end()), _cnt(0) {
        sort(_a.begin(), _a.end());
    }

    size_t count(const long &sum) {
        for (auto x : _a) {
            long l = sum - x;
            if (x != l && binary_search::find(l, _a)) {
                _cnt++;
                break;
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

    long cnt = 0;
    for (size_t i = 0; i < list.size(); ++i) {
        for (size_t j = 0; j < list.size(); ++j) {
            cnt++;
        }
    }
    cout << "count: " << cnt << '\n';

    /*two_sum_fast two_f(list);
    for (long l = -10000; l <= 10000; ++l) {
        two_f.count(l);
    }
    cout << "sumf count: " << two_f.get_count() << '\n';

    two_sum_bin two_b(list);
    for (long l = -10000; l <= 10000; ++l) {
        two_b.count(l);
    }
    cout << "sumb count: " << two_b.get_count() << '\n';

    two_sum_naive two_n(list);
    for (long l = -10000; l <= 10000; ++l) {
        two_n.count(l);
    }
    cout << "sumn count: " << two_n.get_count() << '\n';*/

    return 0;
}
