/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

#include <iostream>
#include <stdexcept>

using namespace std;

namespace gtlib {

template <typename T>
class single_list {

	struct node {
		T value;
		node *next;

		node(const T &value) : value(value), next(nullptr) {}
	};

	node *first_;
	node *last_;

	struct iterator : public std::iterator<forward_iterator_tag, T> {
		iterator(node* curr) : curr_(curr) {
		}
		iterator& operator ++() {
			curr_ = curr_->next; return *this;
		}
		const T& operator *() const {
			return curr_->value;
		}
		T& operator *() {
			return curr_->value;
		}
		const T* operator ->() const {
			return &curr_->value;
		}
		T* operator ->() {
			return &curr_->value;
		}
		bool operator ==(const iterator& other) {
			return curr_ == other.curr_;
		}
		bool operator !=(const iterator& other) {
			return curr_ != other.curr_;
		}

	private:
		node* curr_;
	};

	public:
	single_list() : first_(nullptr), last_(nullptr) {
	}

	~single_list() {
		for (node *curr = first_; curr; ) {
			node *temp = curr;
			curr = curr->next;
			delete temp;
		}
	}

	void push_tail(const T &value) {

		node *n = new node(value);

		if (!first_)
			first_ = n;
		else
			last_->next = n;

		last_ = n;
	}

	const T pop_head() {

		if (!first_) {
			throw logic_error("underflow");
		}

		T v = first_->value;

		node *temp = first_;
		first_ = first_->next;

		delete temp;

		if (!first_) {
			last_ = first_;
		}

		return v;
	}

	iterator begin() { return iterator(first_); }
	iterator end() { return iterator(nullptr); }
};

}


int main() {

	gtlib::single_list<int> l;

	for (auto it = l.begin(); it != l.end(); ++it ) {
		cout << *it << endl;
	}

	l.push_tail(1);
	l.push_tail(2);
	l.push_tail(5);

	for (auto it = l.begin(); it != l.end(); ++it ) {
		cout << *it << endl;
	}

	l.pop_head();

	l.push_tail(40);
	l.push_tail(20);
	l.push_tail(30);

	for (auto it = l.begin(); it != l.end(); ++it ) {
		cout << *it << endl;
	}

	return 0;
}
