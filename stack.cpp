/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <stdexcept>
#include <memory>


namespace gtlib {

    template<class T>
    struct stack {

        typedef T value_type;

    private:
        struct node {
            T value_;
            node *prev;

            node(const T &v) : value_(v), prev(nullptr) {
            }

            ~node() {
            }
        };

        std::unique_ptr<node> top_;

    public:
        stack() {
        }

        ~stack() {
            while (top_) {
                top_.reset(top_->prev);
            }
        }

        stack(std::initializer_list<T> list) : stack() {
            for (auto &it : list) {
                push(it);
            }
        }

        void push(const T &v) {
            node *n = new node(v);

            if (top_) {
                n->prev = top_.release();
            }

            top_.reset(n);
        }

        T pop() {
            if (!top_) {
                throw std::logic_error("underflow");
            }

            T v = top_->value_;

            top_.reset(top_->prev);

            return v;
        }

        bool empty() {
            return (top_ == nullptr);
        }

        void reverse() {

            node *temp, *prev = nullptr, *curr = top_.release();

            while (curr) {

                temp = curr->prev;
                curr->prev = prev;

                prev = curr;
                curr = temp;
            }

            top_.reset(prev);
        }
    };

}

int main(int argc, char **argv) {

    using int_stack = gtlib::stack<int>;

    int_stack s = {1, 2, 3, 4, 5};

    std::cout << s.pop() << '\n';
    std::cout << s.pop() << '\n';
    std::cout << s.pop() << '\n';

    s.push(6);
    s.push(7);
    s.push(8);

    s.reverse();

    std::cout << s.pop() << '\n';
    std::cout << s.pop() << '\n';

    std::cout << std::boolalpha << s.empty() << '\n';
}
