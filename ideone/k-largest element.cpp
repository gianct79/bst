#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T, typename U = std::less<T>>
struct k_elements {
    unsigned k_;
    vector<T> v_;
    U u_ = U();

    typedef typename vector<T>::const_iterator const_iterator;

    k_elements(int k) : k_(k) {
    }

    void push(T const &v) {
        if (v_.size() < k_) {
            v_.insert(upper_bound(v_.begin(), v_.end(), v, u_), v);
        } else {
            auto it = v_.begin();
            if (!u_(v, *it)) {
                v_.erase(it);
                v_.insert(upper_bound(v_.begin(), v_.end(), v, u_), v);
            }
        }
    }

    const_iterator begin() const { return v_.begin(); }; 
    const_iterator end() const { return v_.end(); }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        k_elements<int> max(k);
        k_elements<int, std::greater<int>> min(k);
        while (n--) {
            int c;
            cin >> c;
            max.push(c);
            min.push(c);
        }
        cout << k << " largest elements : ";
        for (auto &i : max) {
            cout << i << ' ';
        }
        cout << '\n' << k << " smallest elements: ";
        for (auto &i : min) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    return 0;
}
