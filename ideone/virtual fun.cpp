
#include <iostream>

using namespace std;

class A {
    int x;
public:
    A(int x = 0) : x(x) {
        cout << x << endl;
    }
};

class B : virtual A {
public:
    B() : A(1) {
    }
};

class C : A {
public:
    C() : A(2) {
    }
};

class D : B {
};

class E : C {
};

int main(int argc, char **argv) {

    cout << "oi" << endl;

    A a;
    B b;
    C c;
    D d;
    E e;

}