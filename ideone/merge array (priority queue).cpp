#include <iostream>
#include <queue>

using namespace std;

int main() {

    using range = pair<int, int>;

    vector<range> input = {{4,7}, {11,15}, {3,5}, {1,2}, {6,9}, {8,13}};

    priority_queue<range, vector<range>, greater<range>> queue;
    for (auto i : input)
        queue.push(i);

    vector<range> output;

    range curr = queue.top(); queue.pop();
    while (!queue.empty()) {
        range next = queue.top(); queue.pop();
        if (curr.second >= next.first) {
            curr = make_pair(curr.first, next.second);
        } else {
            output.push_back(curr);
            curr = next;
        }
    }
    output.push_back(curr);

    for (auto i : output)
        cout << '[' << i.first << ',' << i.second << ']';

    return 0;
}