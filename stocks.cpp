#include <iostream>
#include <vector>

using namespace std;

int get_profit(vector<int> const &stocks) {

    int min = 0;
    int max = 0;

    for (unsigned i = 1; i < stocks.size(); i++) {
        if (stocks[i] < stocks[min]) {
            min = i;
        }
        int profit = stocks[i] - stocks[min];
        if (profit > max) {
            max = profit;
        }
    }    

    return max;
}


int main() {
    vector<int> stocks;
    int s;
    while (cin >> s) {
        stocks.push_back(s);
    }
    cout << get_profit(stocks) << '\n';
    return 0;
}
