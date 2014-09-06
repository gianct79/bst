/*
* Copyleft 1979-2014 GTO Inc. All rights reversed.
*/

#include <iostream>

template <typename T>
T pow_r(T const &base, T exp)
{
    if (exp == 0)
        return 1;
    return base * pow_r(base, --exp);
}

template <typename T>
T pow_i(T const &base, T exp)
{
    T result(1);
    while (exp-- > 0)
        result *= base;
    return result;
}

template <typename T>
T pow(T const &base, T exp)
{
    bool neg = (exp < 0);
    if (neg)
        exp *= -1;
    T result = pow_i(base, exp);
    if (neg)
        result = (1 / result);
    return result;
}


int main()
{
    std::cout << pow_r(2, 0) << '\n';
    std::cout << pow_r(2, 1) << '\n';
    std::cout << pow_r(2, 2) << '\n';
    std::cout << pow_r(3, 3) << '\n';
    
    std::cout << pow(2.0, -0.) << '\n';
    std::cout << pow(2.0, -1.) << '\n';
    std::cout << pow(2.0, -2.) << '\n';
    std::cout << pow(3.0, -3.) << '\n';

    return 0;
}

