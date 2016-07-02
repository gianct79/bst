#include <iostream>

using namespace std;

class A {
    public:
    A() {
        cout << "A::A" << endl;
    }
    ~A() {
        cout << "A::~A" << endl;
    }
};

class B : public A {
    public:
    B() {
        cout << "B::B" << endl;
    }
    ~B() {
        cout << "B::~B" << endl;
    }
};

class C : public B {
    public:
    C() {
        cout << "C::C" << endl;
    }
    ~C() {
        cout << "C::~C" << endl;
    }
};


int main() {

	C c;
	B b;
	A a;

    return 0;

}