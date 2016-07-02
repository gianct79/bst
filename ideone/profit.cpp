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
    vector<int> stocks = { 3, 4, 5, 6, 5, 4, 3, 2, 1, 2, 3, 4, 3, 2, 1, 4, 5 };
    cout << get_profit(stocks) << '\n';

    stocks = { 3, 2, 1, 3, 6, 5, 2 };
    cout << get_profit(stocks) << '\n';
    
    return 0;
}