#include <iostream>
#include <vector>


template<typename T, typename C = std::less<T>>
struct binary_heap {

    std::vector<T> _data;
    C _cmp;

    const T top() const {
        return _data[0];
    }

    const bool empty() const {
        return _data.empty();
    }

    void push(T const &v) {
        _data.push_back(v);
        _heapify();
    }

    void pop() {
        _data.erase(_data.begin());
        _heapify();
    }

    void _sift_down(int start) {

        int root = start;
        int left = root * 2 + 1;
        int end = _data.size() - 1;

        while (left <= end) {

            int swap = root;

            if (_cmp(_data[swap], _data[left]))
                swap = left;

            int right = left + 1;
            if (right <= end && _cmp(_data[swap], _data[right]))
                swap = right;

            if (swap == root)
                return;
            else {
                std::swap(_data[root], _data[swap]);
                root = swap;
            }
            left = root * 2 + 1;
        }
    }

    void _heapify() {

        int start = (_data.size() - 2) / 2;

        while (start >= 0) {

            _sift_down(start);
            start--;
        }
    }
};


int main() {

    binary_heap<int, std::greater<int>> b;

    //b.push(1);
    //b.push(6);
    //b.push(3);

    while (!b.empty()) {
        std::cout << b.top() << ' ';
        b.pop();
    }
    std::cout << '\n';

    return 0;
}