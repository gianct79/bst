/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*
* Copied from Chicao.
*/

#include <iostream>
#include <string>
#include <cctype>

int eval(const char *expr) {

    int ax = 0;
    int op = 1;

    for (; *expr; ) {
        if (isdigit(*expr)) {
            int n = 0;
            while (isdigit(*expr)) {
                n *= 10;
                n += *expr++ - '0';
            }
            ax += (op * n);
            // reset flags
            op = 1;
        } else {
            if (*expr == '+') {
                /* op *= 1; */;
            } else if(*expr == '-') {
                op *= -1;
            } else {
                /* error */
            }
            ++expr;
        }
    }
    return ax;
}

int main(int argc, char **argv) {

    for(std::string expr; std::cin >> expr; ) {
        std::cout << expr << " = ";
        std::cout << eval(expr.c_str()) << std::endl;
    }
}
