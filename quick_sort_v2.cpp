/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <fstream>

#include <iterator>
#include <vector>

using namespace std;

template <class T>
class quick_sort {

    static size_t pivot(const vector<T> &v, size_t lo, size_t hi) {
        //return lo;
        //return hi - 1;

        size_t l = lo;
        size_t r = (hi - 1);
        size_t m = (l + r) / 2;

        if (v[l] < v[m]) {
            if (v[m] < v[r])
                return m;
            else if (v[r] < v[m])
                return r;
            else
                return l;
        } else {
            if (v[m] > v[r])
                return m;
            else if (v[r] > v[m])
                return r;
            else
                return l;
        }

        //T l = max<int>(a[lo], a[hi - 1]);
        //T s = min<int>(a[lo], a[hi - 1]);
        //T c = a[(hi - lo - 1) / 2];

        //if (c > l)
        //    return l;
        //else if (c < s) 
        //    return s;
        //else
        //    return c;
    }

    static size_t partition(vector<T> &a, size_t lo, size_t hi) {

        size_t k = pivot(a, lo, hi);
        size_t i = lo + 1;

        T p = a[k];

        swap<int>(a[lo], a[k]);
        for (size_t j = i; j < hi; j++) {
            if (a[j] < p)
                swap<int>(a[j], a[i++]);
        }
        swap<int>(a[lo], a[i - 1]);

        return i - 1;
    }

    static size_t sort(vector<T> &a, size_t lo, size_t hi) {

        if (hi <= lo)
            return 0;

        size_t cnt = hi - lo - 1;

        size_t p = partition(a, lo, hi);

        cnt += sort(a, lo, p);
        cnt += sort(a, p + 1, hi);

        return cnt;
    }

public:
    static size_t sort(vector<T> &a) {
        return sort(a, 0, a.size());
    }
};

int main(int argc, char **argv) {

    istream_iterator<int> eos;
    vector<int> list;

    if (argc > 1) {
        ifstream input(argv[1], istream::in);
        if (input) {
            copy(istream_iterator<int>(input), eos, back_inserter(list));
        }
    }

    if (list.size() == 0) {
        cout << "type int values, one per line...\n";
        copy(istream_iterator<int>(cin), eos, back_inserter(list));
    }

    cout << quick_sort<int>::sort(list) << '\n';

    for (vector<int>::iterator it = list.begin(); it != list.end(); ++it) {
        cout << *it << '\n';
    }

    return 0;
}