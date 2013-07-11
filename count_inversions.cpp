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
size_t countSplitInv(vector<T> &a, const vector<T> &b, const vector<T> &c, size_t length) {

    size_t cnt = 0;

    size_t i = 0;
    size_t j = 0;

    for (size_t k = 0; k < length; k++) {

        if (i >= b.size()) {
            a[k] = c[j++];
        } else if (j >= c.size()) {
            a[k] = b[i++];
        } else if (b[i] < c[j]) {
            a[k] = b[i++];
        } else if (c[j] < b[i]) {
            a[k] = c[j++];
            cnt += b.size() - i;
        }
    }

    return cnt;
}

template <class T>
size_t sortAndCount(vector<T> &a) {

    size_t length = a.size();

    if (length <= 1)
        return 0;

    size_t mid = length / 2;

    vector<T> b(mid);
    for (size_t k = 0; k < mid; k++)
        b[k] = a[k];

    vector<T> c(length - mid);
    for (size_t k = 0; k < (length - mid); k++)
        c[k] = a[mid + k];

    size_t x = sortAndCount(b);
    size_t y = sortAndCount(c);

    size_t z = countSplitInv(a, b, c, a.size());

    return x + y + z;
}

int main(int argc, char **argv) {

    vector<int> list;
    istream_iterator<int> eos;

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

    size_t cnt = sortAndCount(list);
    cout << cnt << '\n';

    for (auto i : list) {
        cout << i << '\n';
    }

    return 0;
}

