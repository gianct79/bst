/*
* Copyright 1979-2013 Giancarlo Tomazelli. All rights reserved.
*
* Do not redistribute without permission.
*/

#include <iostream>

#include <sstream>
#include <iterator>

#include <algorithm>
#include <map>

int stoi(const std::string &str) {
    return atoi(str.c_str());
}

int main(int argc, char* argv[]) {

    std::string str("100 50 10 5 1");
    std::cout << "enter bill values: ";

    getline(std::cin, str);
    std::istringstream iss(str);

    std::vector<std::string> tokens;
    std::copy(
        std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>(),
        std::back_inserter<std::vector<std::string>>(tokens));

    std::vector<int> bills(tokens.size());
    std::transform(tokens.begin(), tokens.end(), bills.begin(), stoi);

    std::sort(bills.begin(), bills.end(), [](int a, int b) {
        return b < a;
    });

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

//for(std::string expr; std::cin >> expr; ) {
//    std::cout << expr << " = ";
//    std::cout << eval(expr.c_str()) << std::endl;
//}
