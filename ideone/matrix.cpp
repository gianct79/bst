#include <iostream>
#include <array>


template<typename T, std::size_t m>
struct matrix {

    void rotate() {

        for (auto i = 0; i < _data.size(); ++i) {
            for (auto j = i + 1; j < _data.size(); ++j) {
                std::swap(_data[i][j], _data[j][i]);
            }
        }
    }

    std::array<std::array<T, m>, m> _data;
};

template<typename T, std::size_t m>
std::ostream &operator<<(std::ostream &out, matrix<T, m> &a) {

    for (auto i = 0; i < a._data.size(); ++i) {
        for (auto j = 0; j < a._data[i].size(); ++j) {
            std::cout << a._data[i][j] << " ";
        }
        std::cout << "\n";
    }

    return out;
}

int main() {

    matrix<const char*, 4> a{
        " 1"," 2"," 3"," 4",
        " 5"," 6"," 7"," 8",
        " 9", "10", "11", "12",
        "13", "14", "15", "16"};

    std::cout << a << "\n";

    a.rotate();
    std::cout << a << "\n";

    return 0;
}