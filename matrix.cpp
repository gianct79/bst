#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template <typename T>
struct matrix {

    using value_type = T;

    unsigned size_;
    vector<value_type> data_;

    matrix(unsigned const size) : size_(size), data_(size * size) {
    }

    unsigned size() const {
        return size_;
    }

    value_type &at(unsigned i, unsigned j) {
        return data_[(size_ * i) + j];
    }

    value_type diff() {
        value_type sum1 = 0;
        value_type sum2 = 0;
        for (unsigned i = 0, j = size_ - 1; i < size_; ++i, --j) {
            sum1 += at(i, i);
            sum2 += at(i, j);
        }
        return abs(sum1 - sum2);
    }
};

template<typename type>
ostream &operator<<(ostream &out, matrix<type> &a) {
    for (unsigned i = 0; i < a.size(); ++i) {
        for (unsigned j = 0; j < a.size(); ++j) {
            cout << a.at(i, j) << ' ';
        }
        cout << '\n';
    }
    return out;
}

template<typename type>
istream &operator>>(istream &in, matrix<type> &a) {
    for (unsigned i = 0; i < a.size(); ++i) {
        for (unsigned j = 0; j < a.size(); ++j) {
            cin >> a.at(i, j);
        }
    }
    return in;
}


int main() {

    unsigned size;
    cin >> size;
    
    matrix<int> m(size);
    cin >> m;

    cout << m.diff() << '\n';

    return 0;
}