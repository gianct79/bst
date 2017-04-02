#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct node {
    int freq = 0;
    unordered_map<char, node*> next;
};

void addWord(node *root, string const &word) {
    auto p = root;
    for (auto &c : word) {
        if (!p->next.count(c)) {
            p->next[c] = new node();
        }
        p->next[c]->freq++;
        p = p->next[c];
    }
}

void findPrefixes(node *root, string &s, vector<string> &ret) {

    if (root->freq == 1) {
        ret.push_back(s);
    } else {
        for (auto &it : root->next) {
            s.push_back(it.first);
            findPrefixes(it.second, s, ret);
            s.pop_back();
        }
    }
}

vector<string> prefix(vector<string> const &v) {

    node *root = new node();

    for (string const &s : v) {
        addWord(root, s);
    }

    string s;
    vector<string> ret;

    findPrefixes(root, s, ret);
    return ret;
}


int main() {
    auto ret = prefix({"zebra", "dog", "duck", "dot"});
    for (auto &it : ret) {
        cout << it << ' ';
    }
    return 0;
}
