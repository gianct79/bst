#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n, k, q;
  cin >> n >> k >> q;
  vector<int> a(n);
  for (auto &i : a) {
    cin >> i;
  }
  if (k > n) {
    k %= n;
  }
  if (k != 0 && k != n) {
    std::reverse(a.rbegin(), a.rbegin() + k);
    std::reverse(a.rbegin() + k, a.rend());
    std::reverse(a.begin(), a.end());
  }
  /*for (auto &i : a) {
    cout << i << ' ';
  }*/
  while (q--) {
    cin >> n;
    cout << a[n] << '\n';
  }
  return 0;
}
