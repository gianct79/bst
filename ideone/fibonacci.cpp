#include <iostream>
#include <vector>


int fib_r(int n)
{
    return n < 2 ? n : fib_r(n - 1) + fib_r(n - 2);
}


int fib_i(int n)
{
    int p = 0;
    int c = 1;
    while (--n >= 0) {
        auto s = p + c;
        p = c;
        c = s;
    }
    return p;
}


std::vector<int> fib_g(int n)
{
    std::vector<int> g(n);

    int ip = 0;
    int ic = 1;

    g[ip] = ip;
    g[ic] = ic;

    while (ic < n) {
        g[++ic] = g[ip] + g[++ip];
    }

    return g;
}


int main()
{
    std::cout << fib_r(15) << '\n';
    std::cout << fib_i(15) << '\n';

    auto fib = fib_g(20);
    for (auto i : fib)
        std::cout << i << ' ';

    return 0;
}