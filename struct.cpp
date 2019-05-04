#include <iostream>

using namespace std;
 
struct bucha {
  double oak; // 8
  char a; // 8
  double i;  // 8
  char b; // 8
};
 
struct bubba {
  char a;
  double d;
  int i;
};
 
int main() {
  cout << sizeof(bucha::oak) << '\n';
  cout << sizeof(bucha::a) << '\n';
  cout << sizeof(bucha::i) << '\n';
  cout << sizeof(bucha::b) << '\n';

  cout << sizeof(bucha) << '\n';
  cout << sizeof(bubba) << '\n';
  return 0;
}
