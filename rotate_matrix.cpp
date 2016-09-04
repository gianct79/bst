/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <array>

using namespace std;

template<typename T, std::size_t m>
struct matrix {

    void rotate() {
        // transpose matrix
        for (auto i = 0; i < _data.size(); ++i) {
            for (auto j = i + 1; j < _data.size(); ++j) {
                swap(_data[i][j], _data[j][i]);
            }
        }
        // change columns to rotate right
        for (auto i = 0; i < _data.size(); ++i) {
            for (auto j = 0 ; j < _data.size() / 2; ++j) {
                swap(_data[i][j], _data[i][_data.size() - j - 1]);
            }
        }
        // change rows to rotate left
    }

    std::array <std::array<T, m>, m> _data;
};

template<typename T, std::size_t m>
std::ostream &operator<<(std::ostream &out, matrix<T, m> &a) {

    for (auto i = 0; i < a._data.size(); ++i) {
        for (auto j = 0; j < a._data[i].size(); ++j) {
            out << a._data[i][j] << " ";
        }
        out << '\n';
    }

    return out;
}

int main() {

    matrix<const char *, 4> a{
            " 1", " 2", " 3", " 4",
            " 5", " 6", " 7", " 8",
            " 9", "10", "11", "12",
            "13", "14", "15", "16"};

    cout << a << "\n";

    a.rotate();
    cout << a << "\n";

    return 0;
}
