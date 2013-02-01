#include <iostream>
#include <stdexcept>

using namespace std;

namespace gtlib {

template <class T>
class stack {

    struct node {
        T value_;
        node *prev_;

        node(const T& v) : value_(v), prev_(nullptr) {
        }
    };

    node *top_;

public:
    stack() : top_(nullptr) {
    }
    
    ~stack() {
        while (top_) {
            pop();
        }
    }
    
    void push(const T& v) {
        node *n = new node(v);
        
        if (top_ != nullptr) {
            n->prev_ = top_;
        }
        
        top_ = n;
    }

    T pop() {
        if (top_ == nullptr) {
            throw logic_error("underflow");
        }

        T v = top_->value_;
        
        node *t = top_;
        top_ = top_->prev_;
        
        delete t;
        
        return v;
    }
};

}

int main(int argc, char **argv) {

    gtlib::stack<int> pilha;

    try {
        pilha.push(1);
        pilha.push(2);
        pilha.push(3);
        cout << pilha.pop() << endl;
        cout << pilha.pop() << endl;
        cout << pilha.pop() << endl;
        pilha.push(2);
        cout << pilha.pop() << endl;
        cout << pilha.pop() << endl;
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}