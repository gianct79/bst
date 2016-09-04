#include <iostream>

using namespace std;

int add_b(int a, int b) {
    while (b) {
        int c = a & b;
        a = a ^ b;
        b = c << 1;
    }
    return a;
}

int sub_b(int a, int b) {
    while (b) {
        int c = (~a) & b;
        a = a ^ b;
        b = c << 1;
    }
    return a;
}

int mul_b(int a, int b) {
    int r = 0;
    while (b) {
        if (b & 1) {
            r += a;
        }
        a <<= 1;
        b >>= 1;
    }
    return r;
}

int div_b(int a, int b) {
    int d = 1;
    while (b < a) {
        d++;
        b <<= 1;
    }
    int q = 0;
    while (d--) {
        q <<= 1;
        if (a >= b) {
            a -= b;
            q |= 1;
        }
        b >>= 1;
    }
    return q;
}

int main() {
    int a, b;
    while (cin >> a >> b) {
        cout << a << '+' << b << '=' << add_b(a, b) << '\n';
        cout << a << '-' << b << '=' << sub_b(a, b) << '\n';
        cout << a << '*' << b << '=' << mul_b(a, b) << '\n';
        cout << a << '/' << b << '=' << div_b(a, b) << '\n';
    }
    return 0;
}
