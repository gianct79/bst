#include <cassert>

template <typename T = double>
double divide(T dividend, T divisor, T  const &epsilon = T(1e-9)) {
  bool negative = (dividend < 0) != (divisor < 0);
  if (dividend < 0) { dividend = -dividend; }
  if (divisor < 0) { divisor = -divisor; }

  for (T lbound = 0, ubound = dividend; ;) {
    assert(lbound <= ubound);
    auto const quotient = lbound + (ubound - lbound) / 2;
    auto const target = quotient * divisor;

    T precision;
    if (target > dividend) {
      precision = target - dividend;
      ubound = quotient;
    } else {
      precision = dividend - target;
      lbound = quotient;
    }

    if (precision <= epsilon) {
      return negative ? -quotient : quotient;
    }
  }
}

#define TEST(Dividend, Divisor) \
  do { \
    auto const expected = static_cast<double>(Dividend) / Divisor; \
    auto const actual = divide<double>(Dividend, Divisor); \
    std::cout \
      << std::endl << "dividend: " << Dividend \
      << std::endl << "divisor: " << Divisor \
      << std::endl << "expected: " << expected \
      << std::endl << "actual:   " << actual \
      << std::endl << "------------------------------------------------------" \
      << std::endl; \
      \
      if (std::abs(actual - expected) > 1e-9) { \
        exit = EXIT_FAILURE; \
      } \
  } while (false)

#include <algorithm>
#include <iostream>

int main() {
  auto exit = EXIT_SUCCESS;

  TEST(1, 1);
  TEST(9, 3);
  TEST(45, 15);
  TEST(10000, 100);
  TEST(10000, 33);
  TEST(123, 22);
  TEST(22, 123);
  TEST(123, 22);
  TEST(123, -22);
  TEST(-123, 22);
  TEST(-123, -22);
  TEST(0, 0);

  return exit;
}