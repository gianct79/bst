/*
* Copyright 1979-2013 Giancarlo Tomazelli. All rights reserved.
*
* Do not redistribute without permission.
*/

#include <iostream>
#include <sstream>
#include <map>

int main(int argc, char* argv[]) {

    std::map<int, char*> romanDict;

    romanDict[1] = "I";
    romanDict[4] = "IV";
    romanDict[5] = "V";
    romanDict[9] = "IX";
    romanDict[10] = "X";
    romanDict[40] = "XL";
    romanDict[50] = "L";
    romanDict[90] = "XC";
    romanDict[100] = "C";
    romanDict[400] = "CD";
    romanDict[500] = "C";
    romanDict[900] = "CM";
    romanDict[1000] = "M";

    int value;

    std::cout << "enter value : ";
    std::cin >> value;

    std::map<int, size_t> romanValue;

    while (value > 0) {

        for (auto it = romanDict.rbegin(); it != romanDict.rend(); ++it) {

            romanValue[it->first] = value / it->first;
            value = value % it->first;
        }

        std::stringstream ss;

        for (auto it = romanValue.rbegin(); it != romanValue.rend(); ++it) {

            for (size_t i = 0; i < it->second; ++i)
                ss << romanDict[it->first];
        }

        std::cout << "roman value : " << ss.str() << std::endl;

        std::cout << "enter value : ";
        std::cin >> value;

        romanValue.clear();
    }
}
