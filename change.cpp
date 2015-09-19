/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>

int main(int argc, char *argv[]) {

    int trade, money;

    std::cout << "sale value..: ";
    std::cin >> trade;

    std::cout << "money.......: ";
    std::cin >> money;

    int change = money - trade;

    int bills = 0;

    if (change) {

        bills += change / 100;
        change = change % 100;

        bills += change / 50;
        change = change % 50;

        bills += change / 10;
        change = change % 10;

        bills += change / 1;
    }

    std::cout << "qty of bills: " << bills << std::endl;

    return 0;
}
