#include <iostream>

using namespace std;

class A {
  public:
    virtual void f() { cout << "A::f" << endl; }
    void g() { cout << "A::g" << endl; }
};

class B {
  public:
    virtual void f() { cout << "B::f" << endl; }
    void g() { cout << "B::g" << endl; }
};

class C {
  public:
    virtual void h() { cout << "C::h" << endl; }
};


int main() {
  A a, *p;
  B b;
  C c;

  p = &a;
  p->f();
  p->g();

  p = reinterpret_cast<A*>(&b);
  p->f();
  p->g();

  p = reinterpret_cast<A*>(&c);
  p->f();
  p->g();
  //p->h();
}