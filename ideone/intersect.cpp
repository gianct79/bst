#include <iostream>
#include <array>

int main() {

    std::array<int, 5> a {{1, 3, 5, 7, 9}};
    std::array<int, 4> b {{1, 2, 3, 4}};
    //std::array<int, 2> b {{2, 4}};

    auto it_a = a.begin();
    auto it_b = b.begin();

    while (it_a != a.end() && it_b != b.end()) {
        if (*it_a < *it_b)
            ++it_a;
        else if (*it_a > *it_b)
            ++it_b;
        else {
            std::cout << *it_a << '\n';
            ++it_a; ++it_b;
        }
    }

    return 0;
}