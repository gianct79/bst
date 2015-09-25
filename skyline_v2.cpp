/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


template<typename T>
struct max_heap {

    typedef std::vector<T> cache_type;
    typedef typename cache_type::const_iterator const_iterator;

    cache_type data_;

    max_heap() {
    }

    max_heap(std::initializer_list<T> list) : data_(list) {
        std::make_heap(data_.begin(), data_.end());
    }

    void insert(T const &value) {
        data_.push_back(value);
        std::make_heap(data_.begin(), data_.end());
    }

    void remove(T const &value) {
        auto pos = std::find(data_.begin(), data_.end(), value);
        if (pos != data_.end()) {
            data_.erase(pos);
            std::make_heap(data_.begin(), data_.end());
        }
    }

    T const max() {
        return data_.empty() ? T() : data_.front();
    }

    const_iterator begin() const { return data_.begin(); }

    const_iterator end() const { return data_.end(); }
};

struct building {
    int xl;
    int xr;
    int h;
};

using building_vector = std::vector<building>;

std::ostream &operator<<(std::ostream &out, building_vector const &input) {
    out << '[';
    for (auto &b : input) {
        out << '(' << b.xl << ',' << b.xr << ',' << b.h << ')';
    }
    out << ']';
    return out;
}

struct point {
    int x;
    int h;

    bool operator>(point const &rhs) const {
        return (x > rhs.x);
    }
};

using skyline = std::priority_queue<point, std::vector<point>, std::greater<point>>;

int perimeter(building_vector const &B) {

    if (!B.size())
        return 0;

    skyline sk;

    for (auto &b : B) {
        sk.push({b.xl, b.h});
        sk.push({b.xr, -b.h});
    }

    point prev = sk.top();
    sk.pop();

    max_heap<int> h{prev.h};

    int p = prev.h;

    while (!sk.empty()) {

        point curr = sk.top();
        sk.pop();

        int prevH = h.max();

        if (curr.h >= 0) { // start
            h.insert(curr.h);
        } else { // end
            h.remove(-curr.h);
        }

        int maxH = h.max();

        if (maxH != prevH) {
            p += std::abs(maxH - prevH);
        }
        p += std::abs(curr.x - prev.x);

        prev = curr;
    }

    return p;
}


int main() {

    building_vector input;

    std::cout << "Enter values x, w, h; one building per line...\n";

    int x, h, w;
    while (std::cin >> x >> w >> h) {
        input.push_back({x, x + w, h});
    }
    //input.push_back({2, 5, 2});
    //input.push_back({1, 6, 1});
    //input.push_back({3, 4, 4});
    //input.push_back({1, 6, 3});


    std::cout << input << '\n';

    std::cout << perimeter(input) << '\n';

    return 0;
}
