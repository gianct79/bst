/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct item {
    int value;
    int weight;
};

typedef vector<item> item_list;
typedef vector<vector<int>> result_table;

class knapsack {

    item_list _items;
    result_table _knapsack;

    int _capacity;

public:
    knapsack() : _capacity(0) {
    }

    int find_best_pack() {
        for (item item : _items) {
            for (auto w = 0; w <= _capacity; ++w) {

                if (item.weight > w) {
                    _knapsack[1][w] = _knapsack[0][w];
                } else {
                    int remaining = w - item.weight;
                    int new_value = item.value + _knapsack[0][remaining];
                    int pre_value = _knapsack[0][w];

                    if (pre_value >= new_value) {
                        _knapsack[1][w] = _knapsack[0][w];
                    }
                    else {
                        _knapsack[1][w] = new_value;
                    }
                }
            }
            copy(_knapsack[1].begin(), _knapsack[1].end(), _knapsack[0].begin());
        }

        return _knapsack[1][_capacity];
    }

    friend istream& operator>>(istream& is, knapsack& k) {

        string line;
        getline(is, line);

        stringstream linestream(line);
        linestream >> k._capacity;

        while (getline(is, line)) {

            stringstream linestream(line);

            if (linestream) {

                item tata;
                linestream >> tata.value >> tata.weight;

                k._items.push_back(tata);
            }
        }

        k._knapsack.resize(2, vector<int>(k._capacity + 1));

        return is;
    }
};

int main(int argc, char* argv[]) {

    knapsack k;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in); ifs >> k;
    }

    cout << k.find_best_pack() << '\n';

    cin.get();

    return 0;
}

