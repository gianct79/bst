#include <iostream>

template<typename T>
struct foo {
    static void print() {
        std::cout << "foo ";
    }
};

template<>
struct foo<std::string> {
    static void print() {
        std::cout << "stringao ";
    }
};

struct vehicle {
    std::string plate;
};

struct car : vehicle {
    
};

template<>
struct foo<vehicle> {
    static void print() {
        std::cout << "vehicle ";
    }	
};

int main() {
    foo<int>::print();
    foo<std::string>::print();
    
    foo<car>::print();
    foo<vehicle>::print();

    return 0;
}