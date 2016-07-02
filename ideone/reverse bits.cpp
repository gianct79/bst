#include <iostream>
#include <bitset>

using namespace std;

unsigned short reverse_bits(unsigned short n) {
    unsigned short cnt = sizeof(n) * 8 - 1;
    unsigned short rev = n;
    n >>= 1;
    while (n) {
       rev <<= 1;
       rev |= n & 1;
       n >>= 1;
       cnt--;
    }
    rev <<= cnt;
    return rev;
}

int main() {
	unsigned short n = 3560;
	cout << "input =" << std::dec << n << " (hex=0x" << std::hex << n << ", binary=0b" << std::bitset<16>(n) << ")\n";
	unsigned short r = reverse_bits(n);
	cout << "output=" << std::dec << r << " (hex=0x" << std::hex << r << ", binary=0b" << std::bitset<16>(r) << ")\n";
	return 0;
}
