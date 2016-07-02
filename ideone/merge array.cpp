#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main() {

    using range = pair<int, int>;

    vector<range> input = {{4,7}, {11,15}, {1,3}, {6,9}, {1,2}};

	sort(input.begin(), input.end());

    vector<range> output;

    range curr = input[0];
    for (auto i = 1; i < input.size(); ++i) {
        range next = input[i];
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