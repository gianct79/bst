/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <vector>

int f_r(int n, int k) {
    if (k == 0)
        return 1;
    return f_r(n, k - 1) * (n + 1 - k) / k;
}

void pascal_recursive(int n) {
    for (auto k = 0; k <= n; ++k)
        std::cout << f_r(n, k) << ' ';
    std::cout << '\n';
}

void pascal_computed(int n) {
    std::vector<int> p{};
    for (auto k = 0; k <= n; ++k)
        std::cout << *p.emplace(
                p.end(), (k == 0) ? 1 : p[k - 1] * (n + 1 - k) / k) << ' ';
    std::cout << '\n';
}

int main() {
    int n;
    while (std::cin >> n) {
        //pascal_recursive(n);
        pascal_computed(n);
    }

    return 0;
}