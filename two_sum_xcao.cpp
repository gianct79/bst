#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename iterator>
pair<iterator, iterator> find_2sum_sorted(typename iterator_traits<iterator>::value_type const &target, iterator begin, iterator end) {
    if(begin == end || *begin > target) {
        return make_pair(end, end);
    }

    for(auto r = end - 1; begin != r; ) {
        auto seek = target - *begin;

        while(*r > seek) {
            if(--r == begin) {
                return make_pair(end, end);
            }
        }

        if(*r == seek) {
            return make_pair(begin, r);
        }

        if(*++begin > target) break;
    }
    return make_pair(end, end);
}

template <typename iterator>
pair<iterator, iterator> find_2sum(typename iterator_traits<iterator>::value_type const &target, iterator begin, iterator end) {
    sort(begin, end);

    return find_2sum_sorted(target, begin, end);
}

template <typename iterator, typename method_type>
void test_2sum(typename iterator_traits<iterator>::value_type const &target, iterator begin, iterator end, method_type method) {
    auto result = method(target, begin, end);

    if (*result.first + *result.second == target) {
        cout << *result.first << " + " << *result.second << " = " << target << endl;
    }
}

int main(int argc, char **argv) {

    vector<long> v;

    if(argc > 1) {
        ifstream ifs(argv[1], istream::in);
        long l;
        while(ifs >> l) {
            v.push_back(l);
        }
    }

    cout << "list count: " << v.size() << '\n';

    for(long l = -10000; l <= 10000; ++l) {
        test_2sum(l, begin(v), end(v), find_2sum<decltype(begin(v))>);
    }
}
