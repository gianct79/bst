/*
 * Copyleft GTO Inc. All rights reversed.
 */


#include <iostream>
#include <stdexcept>
#include <memory>


namespace gtlib {

    template<typename T>
    struct single_list {

        typedef T value_type;

    private:
        struct node {
            T value;
            node *next;

            node(T const &value) : value(value), next(nullptr) {
            }
        };

        std::unique_ptr<node> head_;
        node *tail_;

        struct iterator : public std::iterator<std::forward_iterator_tag, T> {
            iterator(node *curr) : curr_(curr) {
            }

            iterator &operator++() {
                curr_ = curr_->next;
                return *this;
            }

            const T &operator*() const {
                return curr_->value;
            }

            T &operator*() {
                return curr_->value;
            }

            const T *operator->() const {
                return &curr_->value;
            }

            T *operator->() {
                return &curr_->value;
            }

            bool operator==(iterator const &other) {
                return curr_ == other.curr_;
            }

            bool operator!=(iterator const &other) {
                return curr_ != other.curr_;
            }

        private:
            node *curr_;
        };

        node *reverse_r(node *curr, node *prev = nullptr) {

            if (!curr) {
                tail_ = prev;
                return prev;
            }

            auto last = reverse_r(curr->next, curr);
            curr->next = prev;

            return last;
        }

    public:
        single_list() : tail_(nullptr) {
        }

        ~single_list() {
            while (head_) {
                head_.reset(head_->next);
            }
        }

        single_list(std::initializer_list<T> list) : single_list() {
            for (auto &it : list) {
                push_tail(it);
            }
        }

        void push_tail(T const &value) {

            node *n = new node(value);

            if (!head_)
                head_.reset(n);
            else
                tail_->next = n;

            tail_ = n;
        }

        const T pop_head() {

            if (!head_) {
                throw std::logic_error("underflow");
            }

            T v = head_->value;

            head_.reset(head_->next);

            if (!head_) {
                tail_ = nullptr;
            }

            return v;
        }

        void reverse() {

            tail_ = head_.release();
            node *temp, *prev = nullptr, *curr = tail_;

            while (curr) {

                temp = curr->next;
                curr->next = prev;

                prev = curr;
                curr = temp;
            }

            head_.reset(prev);
        }

        void reverse_r() {
            head_.reset(reverse_r(head_.release()));
        }

        iterator begin() { return iterator(head_.get()); }

        iterator end() { return iterator(nullptr); }
    };

    template<typename T>
    std::ostream &operator<<(std::ostream &out, single_list<T> &list) {
        for (auto &it : list)
            out << it << ' ';
        return out;
    }
}


int main() {

    using int_list = gtlib::single_list<int>;

    int_list l = {1, 2, 3};
    std::cout << l << '\n';

    l.reverse();
    std::cout << l << '\n';

    l.pop_head();
    l.pop_head();
    l.pop_head();

    int_list::value_type v;
    while (std::cin >> v)
        l.push_tail(v);

    std::cout << l << '\n';

    l.reverse_r();
    std::cout << l << '\n';

    return 0;
}

