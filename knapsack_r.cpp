/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <fstream>

#include <vector>
#include <sstream>

#include <algorithm>

using namespace std;

struct item {
    int value;
    int weight;
};

typedef vector <item> item_list;
typedef vector <vector<int>> result_table;

class knapsack {

    item_list _items;

    int _capacity;

    int find_best_pack_r(const int capacity, const int n) {
        if (n == 0 || capacity == 0)
            return 0;

        if (_items[n - 1].weight > capacity) {
            return find_best_pack_r(capacity, n - 1);
        }
        else {
            return max(_items[n - 1].value
                       + find_best_pack_r(capacity - _items[n - 1].weight, n - 1),
                       find_best_pack_r(capacity, n - 1)
            );
        }
    }

public:
    knapsack() : _capacity(0) {
    }

    int find_best_pack() {
        return find_best_pack_r(_capacity, _items.size());
    }

    friend istream &operator>>(istream &is, knapsack &k) {

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

        return is;
    }
};

int main(int argc, char *argv[]) {

    knapsack k;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in);
        ifs >> k;
    }

    cout << k.find_best_pack() << '\n';

    return 0;
}

