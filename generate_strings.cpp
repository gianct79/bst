/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <vector>


template<typename T>
void gen_sequence(std::vector <T> const &A, int a, int k, int i, std::string &buffer) {

    if (i == k) {
        std::cout << buffer << ',';
        return;
    }

    if (a >= A.size())
        return;

    buffer[i] = A[a];

    gen_sequence(A, a + 1, k, i + 1, buffer);
    gen_sequence(A, a + 1, k, i, buffer);
}


template<typename T>
void power_set(std::vector <T> const &A, int k, int i, std::string &buffer) {

    if (i == k) {
        std::cout << buffer << ',';
        return;
    }

    for (int n = 0; n < A.size(); ++n) {
        buffer[i] = A[n];
        power_set(A, k, i + 1, buffer);
    }
}

int main() {

    std::vector<char> A = {'a', 'b', 'c', 'd', 'e'};

    std::string buffer;

    unsigned k;
    while (std::cin >> k) {

        buffer.resize(k);
        gen_sequence(A, 0, k, 0, buffer);
        std::cout << '\n';

        buffer.resize(k);
        power_set(A, k, 0, buffer);
        std::cout << '\n';
    }

    return 0;
}
