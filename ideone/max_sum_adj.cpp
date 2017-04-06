#include <iostream>
#include <vector>

using namespace std;

unsigned maxSum(vector<unsigned> const &v) {

    unsigned max = 0, sum = 0;

    for (unsigned i = 1; i < v.size(); ++i) {

        if (v[i] < v[i - 1]) {
            sum = v[i];
        } else {
            sum += v[i];
            if (sum > max) {
                max = sum;
            }
        }
    }

    return max;
}

pair<unsigned, unsigned> maxPos(vector<unsigned> const &v) {

    pair<unsigned, unsigned> ret;
    unsigned max = 0, sum = 0, min = 0;

    for (unsigned i = 1; i < v.size(); ++i) {

        if (v[i] < v[i - 1]) {
            sum = v[i];
            min = i;
        } else {
            sum += v[i];
            if (sum > max) {
                max = sum;
                ret.first = min;
                ret.second = i;
            }
        }
    }

    return ret;
}

std::ostream &operator<<(ostream &out, pair<unsigned, unsigned> const &p) {
    out << '{' << p.first << ',' << p.second << '}';
    return out;
}

int main() {

	vector<unsigned> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << maxPos(v) << ':' << maxSum(v) << '\n';
    
    v = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    cout << maxPos(v) << ':' << maxSum(v) << '\n';

	v = {2, 1, 2, 4, 3, 2, 7, 1, 1, 0};
    cout << maxPos(v) << ':' << maxSum(v) << '\n';

    return 0;
}
