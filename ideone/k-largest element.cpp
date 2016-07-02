#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
struct k_largest {

	vector<T> v_;
	int k_;

	typedef typename vector<T>::const_iterator const_iterator;

	k_largest(int k) : k_(k), v_(k) {
	}

	void push(T const &v) {
		const_iterator it;
		if (v_.empty() || v_.size() < k_) {
			auto it = upper_bound(v_.begin(), v_.end(), v);
			v_.insert(it, v);
		} else {
			auto it = v_.begin();
			if (v > *it) {
				v_.erase(it);
				it = upper_bound(v_.begin(), v_.end(), v);
				v_.insert(it, v);
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
        k_largest<int> v(k);
        while (n--) {
            int c;
            cin >> c;
            v.push(c);
        }
        for (auto i : v) {
            cout << i << ' ';
        }
        cout << '\n';
	}
	return 0;
}
