#include <iostream>
#include <vector>

using namespace std;

int canCompleteCircuit(vector<int> const &gas, vector<int> const &cost) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details

    // 1) if the sum of gas >= the sum of cost, then the circle can be completed.
    // 2) if A can not reach C in a the sequence of A-->B-->C, then B can not make it either.
    // If gas[A] < cost[A], then A can not even reach B.
    // So to reach C from A, gas[A] must >= cost[A].
    // Given that A can not reach C, we have gas[A] + gas[B] < cost[A] + cost[B],
    // and gas[A] >= cost[A], therefore, gas[B] < cost[B], i.e., B can not reach C.

    int sumRem = 0; // track current remaining
    int total = 0; // track total remaining
    int start = 0; 

    for (int i = 0; i < gas.size(); ++i) {
        int rem = gas[i] - cost[i];
        if (sumRem >= 0) { // if sum remaining of (i-1) >= 0, continue 
            sumRem += rem;
        } else { //otherwise, reset start index to be current
            sumRem = rem;
            start = i;
        }
        total += rem;
    }
    return (total >= 0) ? start : -1;
}

int main() {
    int g; cin >> g;
    vector<int> gas(g);
    for (auto &i : gas) {
        cin >> i;
    }
    int c; cin >> c;
    vector<int> cost(c);
	for (auto &i : cost) {
        cin >> i;
    }
    cout << canCompleteCircuit(gas, cost);
    return 0;
}
