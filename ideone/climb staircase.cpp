#include <iostream>

using namespace std;

/*int baby_steps(int n) {
	return n < 2 ? n : baby_steps(n - 1) + baby_steps(n - 2);
}*/

unsigned baby_steps(int n) {
	unsigned p = 0;
	unsigned c = 1;
	while (--n >= 0) {
		unsigned s = p + c;
		p = c;
		c = s;
	}
	return p;
}

int main() {
	int steps;
	cin >> steps;
	cout << baby_steps(steps) << '\n';
	return 0;
}