#include <iostream>
#include <vector>

void sort012(std::vector<int> &v) {
    int lo = 0;
    int hi = v.size();
    int i = 0;
    while (i < hi) {
        switch (v[i]) {
            case 0:
                std::swap(v[lo++], v[i++]);
                break;
            case 1:
                i++;
                break;
            case 2:
                std::swap(v[i], v[--hi]);
                break;
            default:
                // argg...
                i++;
                break;
        }
    }
}

int main() {
    auto v = std::vector<int>{ 2, 1, 2, 1, 0, 2, 0, 0, 2, 2, 1, 1, 0, 1, 0, 1 };
    sort012(v);
    for (auto &it : v) {
        std::cout << it << ' ';
    }
    return 0;
}
