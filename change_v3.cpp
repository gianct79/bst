/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>

#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef int Bill;
typedef unordered_map<Bill, int> Bills;

class Node {
    Bills bills_;

public:
    const Bills &getBills() const {
        return bills_;
    }

    void setBill(const Bill &bill) {
        bills_[bill] = 0;
    }

    void addBill(const Bill &bill) {
        bills_[bill] += 1;
    }

    Bill getReminder(const Bill &change) const {
        Bill reminder = change;
        for (auto it = bills_.begin(); it != bills_.end(); ++it) {
            reminder -= it->first * it->second;
        }
        return reminder;
    }

    bool isFinal(const Bill &change) const {
        return getReminder(change) == 0;
    }

    bool operator==(const Node &other) const {
        return bills_ == other.bills_;
    }
};

namespace std {
    template<>
    struct hash<Node> {
    public:
        size_t operator()(const Node &node) const {
            size_t h1 = 0;

            for (auto it = node.getBills().begin(); it != node.getBills().end(); ++it) {
                h1 = h1 ^ (it->first << it->second);
            }

            return h1;
        }
    };
}

class Progress {
    char curr_ = '\\';

public:
    void step() {
        switch (curr_) {
            case '\\':
                curr_ = '|';
                break;
            case '|':
                curr_ = '/';
                break;
            case '/':
                curr_ = '-';
                break;
            case '-':
                curr_ = '\\';
                break;
        }
        cout << curr_ << char(8);
    }

};

typedef unordered_set <Node> Solutions;

Progress indicator;

void generateSolutions(const Bill &change, const Node &node, Solutions &solutions) {

    indicator.step();

    if (node.isFinal(change)) {
        solutions.insert(node);
    } else if (node.getReminder(change) > 0) {

        for (auto it = node.getBills().begin(); it != node.getBills().end(); ++it) {

            Bill bill = it->first;

            Node possible(node);
            possible.addBill(bill);

            generateSolutions(change, possible, solutions);
        }
    }
}

int main() {

    Bill money;
    cin >> money;

    Bill sale;
    cin >> sale;

    Node initial;

    Bill n;
    while (cin >> n) {
        initial.setBill(n);
    }

    cout << "Money : " << money << endl;
    cout << "Sale  : " << sale << endl;

    Bill change = money - sale;

    cout << "Change: " << change << endl;

    if (change > 0) {
        Solutions solutions;
        generateSolutions(change, initial, solutions);

        for (Node solution : solutions) {
            for (auto it = solution.getBills().begin(); it != solution.getBills().end(); ++it) {
                cout << "[" << it->first << "]: " << it->second << ", ";
            }
            cout << endl;
        }

    } else if (change == 0) {
        cout << "cool!" << endl;
    } else {
        cout << "what?" << endl;
    }

    return 0;
}
