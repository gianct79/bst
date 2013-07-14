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

	static size_t partition(vector<T> &a, size_t lo, size_t hi) {

        T p = a[lo];
	    size_t i = lo + 1;

        for (size_t j = i; j < hi; j++) {
            if (a[j] < p)
                swap<int>(a[j], a[i++]);
	    }
        swap<int>(a[lo], a[--i]);

        return i;
	}

    static void sort(vector<T> &a, size_t lo, size_t hi) {

        if (hi <= lo)
            return;

        size_t p = partition(a, lo, hi);
        sort(a, lo, p);
        sort(a, p + 1, hi);
    }

public:
	static void sort(vector<T> &a) {
        sort(a, 0, a.size());
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

    quick_sort<int>::sort(list);

    for (vector<int>::iterator it = list.begin(); it != list.end(); ++it) {
        cout << *it << '\n';
    }

    return 0;
}