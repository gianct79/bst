/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

#include <iostream>
#include <array>
#include <map>

int main(int argc, char* argv[]) {

    std::array<int, 4> bills = {100, 50, 10, 1, };
    int sale, money;

    std::cout << "sale value. : ";
    std::cin >> sale;

    std::cout << "money...... : ";
    std::cin >> money;

    int change = money - sale;

    std::map<int, size_t> billsQty;

    if (change > 0) {

        for (auto it = bills.begin(); it != bills.end(); ++it) {

            billsQty[*it] = change / *it;
            change = change % *it;
        }

        std::cout << "qty of bills: ";

        for (auto it = billsQty.begin(); it != billsQty.end(); ++it)
            std::cout << it->first << " => " << it->second << ' ';

    } else if (change == 0) {
        std::cout << "cool!";
    } else {
        std::cout << "what?";
    }
    std::cout << std::endl;

    return 0;
}
