/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <queue>
#include <vector>
#include <functional>


int main() {

    std::priority_queue<int> max_heap;
    std::priority_queue<int, std::vector<int>, std::less<int>> min_heap;

    int i;
    while (std::cin >> i) {
        size_t maxsize = max_heap.size();
        size_t minsize = min_heap.size();

        if (maxsize == 0) {
            max_heap.push(i);
        }
        else if (max_heap.top() > i) {
            if (maxsize > minsize) {
                min_heap.push(max_heap.top());
                max_heap.pop();
            }
            max_heap.push(i);
        }
        else {
            if (minsize > maxsize) {
                max_heap.push(min_heap.top());
                min_heap.pop();
            }
            min_heap.push(i);
        }

        if (min_heap.size() > max_heap.size()) {
            std::cout << min_heap.top() << '\n';
        }
        else if (min_heap.size() < max_heap.size()) {
            std::cout << max_heap.top() << '\n';
        }
        else {
            std::cout << (min_heap.top() + max_heap.top()) / 2 << '\n';
        }
    }

    return 0;
}

