/*
* Copyleft 1979-2014 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <fstream>

void run_length_encoding(std::istream &buffer) {

    if (buffer) {

        char read, next;

        buffer >> read;
        int count = 1;

        while (buffer >> next) {

            if (next != read) {
                std::cout << count << read;
                read = next;
                count = 1;
            } else {
                count++;
            }
        }

        std::cout << count << read << '\n';
    }
}


int main(int argc, char* argv[]) {

    run_length_encoding(std::cin);

    return 0;
}

