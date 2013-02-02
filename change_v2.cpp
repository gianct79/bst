/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

#include <iostream>
#include <array>
#include <map>

int main(int argc, char* argv[]) {

    std::array<int, 4> bills; bills[0] = 100; bills[1] = 50; bills[2] = 10; bills[3] = 1;

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

        std::cout << "\nqty of bills: ";

        for (auto it = billsQty.begin(); it != billsQty.end(); ++it)
            std::cout << it->first << " => " << it->second << ' ';

    } else {
        std::cout << "\nno!";
    }

    return 0;
}
