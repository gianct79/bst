/*
 * Copyleft 1979-2013 GTO Inc. All rights reversed.
 */

#include <iostream>
#include <fstream>

#include <iterator>
#include <algorithm>

#include <vector>

using namespace std;

template <class T>
void countSplitInv(vector<T> &a, vector<T> &aux, size_t lo, size_t mid, size_t hi, size_t &count) {

    size_t i = lo;
    size_t j = mid + 1;

    for (size_t k = lo; k <= hi; k++)
        aux[k] = a[k];

    for (size_t k = lo; k <= hi; k++) {
        if (i > mid)
            a[k] = aux[j++];
        else if (j > hi)
            a[k] = aux[i++];
        else if (aux[j] < aux[i]) {
            a[k] = aux[j++];
            count += (hi - lo - k);
        } else {
            a[k] = aux[i++];
        }
    }
}

template <class T>
void sortAndCount(vector<T> &a, vector<T> &aux, size_t lo, size_t hi, size_t &count) {

    if (hi <= lo)
        return;

    size_t mid = lo + (hi - lo) / 2;
    sortAndCount(a, aux, lo, mid, count);
    sortAndCount(a, aux, mid + 1, hi, count);

    countSplitInv(a, aux, lo, mid, hi, count);
}

template <class T>
void sortAndCount(vector<T> &a, size_t &count) {

    vector<T> aux(a.size());
    sortAndCount(a, aux, 0, a.size() - 1, count);
}

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

    size_t cnt = 0;
    sortAndCount(list, cnt);

    cout << cnt << '\n';

    for (auto i : list) {
        cout << i << '\n';
    }

    return 0;
}

