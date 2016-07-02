#include <iostream>
#include <vector>

using namespace std;

void factorial(int n) {
    vector<int> digits = {1};
    for (auto i = 1; i <= n; ++i) {
        auto carry = 0;
        for (auto j = 0; j < digits.size(); ++j) {
            auto d = digits[j] * i + carry;
            auto dv = div(d, 10);
            digits[j] = dv.rem;
            carry = dv.quot;
        }
        while (carry) {
            auto dv = div(carry, 10);
            digits.push_back(dv.rem);
            carry = dv.quot;
        }
		cout << i << "! = ";
    	for (auto it = digits.rbegin(); it != digits.rend(); ++it)
        	cout << *it;
    	cout << '\n';
    }
}

int main() {
    int n; cin >> n;
    factorial(n);

    return 0;
}
