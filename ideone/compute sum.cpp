/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

typedef vector<int> int_vector;

class vector_sum {
    int_vector list;

public:
    static const size_t QTY = 3;

    vector_sum(const int &value) {
        push_back(value);
    }

    void push_back(const int &value) {
        list.push_back(value);
    }

    void pop_back() {
        list.pop_back();
    }

    const int sum() const {
        int sum = 0;
        for (auto i : list)
            sum += i;
        return sum;
    }

    const size_t size() const {
        return list.size();
    }

    friend ostream& operator <<(ostream &out, const vector_sum &sum) {
        copy(sum.list.begin(), sum.list.end(),
            ostream_iterator<int>(out, ", "));
        return out;
    }
};

void computeSum(const int_vector &list, const int &X,
    int_vector::iterator st, vector_sum &sum) {

    if (sum.size() == sum.QTY) {
        if (sum.sum() == X) {
            cout << sum << endl;
        }
    } else {
        for (auto it = st; it != list.end(); ++it) {
            sum.push_back(*it);
            computeSum(list, X, it + 1, sum);
            sum.pop_back();
        }
    }
}

int main() {

    vector<int> list;
    cout << "type int values, one value per line, 0 to finish..." << endl;

    int x;
    while (cin >> x) {
        if (x == 0) break;
        list.push_back(x);
    }
    //sort(list.begin(), list.end());

    do {
        cout << "enter sum X, 0 to finish: ";
        cin >> x;

        auto end = list.end();
        /* set limit (end) on number (if exist)
        for (auto it = list.begin(); it != end; ++it) {
            if (*it >= x) {
                end = it; break;
            }
        }*/

        for (auto it = list.begin(); it != end; ++it) {
            vector_sum sum(*it);
            computeSum(list, x, it + 1, sum);
        }

    } while (x > 0);

    return 0;
}
