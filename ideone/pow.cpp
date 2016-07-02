#include <iostream>


int pow_r(int b, int e)
{
    if (e == 0)
        return 1;
    return b * pow_r(b, --e);
}


int pow_i(int b, int e)
{
    int r = 1;
    while (e--) {
        r *= b;
    }
    return r;
}


int main()
{
    int b, e;
    while (std::cin >> b >> e) {
        std::cout << pow_r(b, e) << '\n';
        std::cout << pow_i(b, e) << '\n';
    }
    return 0;
}
