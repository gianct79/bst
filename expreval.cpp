/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <string>

int eval(const char *expr) {
 
    int ax = 0;
    int n  = 0;
 
    char op = '+';
 
    while (char c = *expr++) {
        switch (c) {
        case '0':case '1':case '2':case '3':case '4':
        case '5':case '6':case '7':case '8':case '9':
            n = c - 48;
            switch(op) {
            case '+':
                ax += n;
                break;
            case '-':
                ax -= n;
                break;
            }
            op = '+';
            break;
        case '+':
            if (op == '-')
                op = '-';
            else
                op = c;
            break;
        case '-': 
            if (op == '-')
                op = '+';
            else
                op = c;
            break;
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