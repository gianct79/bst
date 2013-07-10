/*
 * Copyleft 1979-2013 GTO Inc. All rights reversed.
 */

#include <iostream>
#include <fstream>

#include <iterator>
#include <vector>

using namespace std;

template <class T>
class merge_sort {

	static vector<T> aux;

	void static merge(vector<T> &a, size_t lo, size_t mid, size_t hi) {

	    size_t i = lo;
	    size_t j = mid + 1;

	    for (size_t k = lo; k <= hi; k++)
	        aux[k] = a[k];

	    for (size_t k = lo; k <= hi; k++) {
	        if (i > mid)
	            a[k] = aux[j++];
	        else if (j > hi)
	            a[k] = aux[i++];
	        else if (aux[j] < aux[i])
	            a[k] = aux[j++];
	        else
	            a[k] = aux[i++];
	    }
	}

	void static sort(vector<T> &a, size_t lo, size_t hi) {

	    if (hi <= lo)
	        return;

	    size_t mid = lo + (hi - lo) / 2;
	    sort(a, lo, mid);
	    sort(a, mid + 1, hi);

	    merge(a, lo, mid, hi);
	}

public:

	void static sort(vector<T> &a) {

		aux = vector<T>(a.size());
	    sort(a, 0, a.size() - 1);
	}
};

template <class T>
vector<T> merge_sort<T>::aux;

int main(int argc, char **argv) {

    istream_iterator<int> eos;

    vector<int> list;

    ifstream input(argv[1], istream::in);
    if (input) {
    	copy(istream_iterator<int>(input), eos, back_inserter(list));
    } else {
    	cout << "type int values, one per line...\n";
    	copy(istream_iterator<int>(cin), eos, back_inserter(list));
    }

    merge_sort<int>::sort(list);

    for (auto i : list) {
        cout << i << '\n';
    }

    return 0;
}
