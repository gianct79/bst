/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <unordered_map>

using namespace std;

typedef int Note;
typedef unordered_map<Note, int> Notes;

class Node {
    Notes notes_;

public:
    const Notes &getNotes() const {
        return notes_;
    }

    void setNote(const Note &note) {
        notes_[note] = 0;
    }

    void addNote(const Note &note) {
        notes_[note] += 1;
    }

    const int countNotes() const {
        int count = 0;
        for (auto it = notes_.begin(); it != notes_.end(); ++it) {
            count += it->second;
        }
        return count;
    }

    Note getReminder(const Note &change) const {
        Note reminder = change;
        for (auto it = notes_.begin(); it != notes_.end(); ++it) {
            reminder -= it->first * it->second;
        }
        return reminder;
    }

    bool isFinal(const Note &change) const {
        return getReminder(change) == 0;
    }

};

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

Progress indicator;

void generateSolutions(const Note &change, const Node &node, Node &solution) {

    if (solution.countNotes() > 0 && node.countNotes() > solution.countNotes()) {
        // Suggestion from diegodie: only accept solutions that could generate fewer notes
        return;
    }

    if (node.isFinal(change)) {
        indicator.step();
        solution = node;
    } else if (node.getReminder(change) > 0) {

        for (auto it = node.getNotes().begin(); it != node.getNotes().end(); ++it) {

            Note note = it->first;

            Node possible(node);
            possible.addNote(note);

            generateSolutions(change, possible, solution);
        }
    }
}

int main() {

    cout << "Money : ";
    Note money;
    cin >> money;

    cout << "Sale  : ";
    Note sale;
    cin >> sale;

    cout << "Notes : ";
    Node initial;

    Note n;
    while (cin >> n) {
        initial.setNote(n);
    }

    Note change = money - sale;

    cout << "Change: " << change << endl;

    if (change > 0) {
        Node solution;
        generateSolutions(change, initial, solution);

        for (auto it = solution.getNotes().begin(); it != solution.getNotes().end(); ++it) {
            cout << "[" << it->first << "]: " << it->second << ", ";
        }
        cout << endl;

    } else if (change == 0) {
        cout << "cool!" << endl;
    } else {
        cout << "what?" << endl;
    }

    return 0;
}
