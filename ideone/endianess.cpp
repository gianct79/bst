#include <iostream>

enum endianess {
	BE,
	LE
};

endianess f() {
	short s = 0xff00;
	return reinterpret_cast<const char*>(&s)[0] ? BE : LE;
}

int main() {
	std::cout << f() << '\n';
}