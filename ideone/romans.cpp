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
    romanDict[500] = "D";
    romanDict[900] = "CM";
    romanDict[1000] = "M";

    int value;
    std::cin >> value;

    while (value > 0) {

        std::cout << value << ": ";
        std::stringstream ss;

        for (auto it = romanDict.rbegin(); it != romanDict.rend(); ++it) {

            for (size_t r = value / it->first; r > 0; --r)
                ss << romanDict[it->first];

            value = value % it->first;
        }

        std::cout << ss.str() << std::endl;
        std::cin >> value;
    }
}