#include <iostream>
#include <array>

template <typename LHS, typename RHS, typename Fn>
void intersect(LHS it_a, LHS aend, RHS it_b, RHS bend, Fn &&fn) {
    while (it_a != aend && it_b != bend) {
        if (*it_a < *it_b) {
            fn(*it_a); ++it_a;
        } 
        if (*it_a > *it_b) {
            fn(*it_b); ++it_b;
        }
        ++it_a; ++it_b;
    }
}

int main() {
    std::array<int, 5> a {{1, 3, 5, 7, 9}};
    std::array<int, 4> b {{1, 2, 3, 4}};
    //std::array<int, 2> b {{2, 4}};

    intersect(a.begin(), a.end(), b.begin(), b.end(), [](int x) {
        std::cout << x << '\n';
    });

    return 0;
}