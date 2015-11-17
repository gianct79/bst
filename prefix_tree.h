#include <unordered_map>
#include <memory>
 
using namespace std;
 
struct prefix_tree {
 
    struct node {
        bool word;
        unordered_map<char, unique_ptr<node>> next;
    };
 
    unique_ptr<node> root;
 
    node *add_node(node *root, string const &word, unsigned sz) {
        if (!root)
            root = new node { false };
        if (sz == word.size()) {
            root->word = true;
        } else {
            char c = word[sz];
            root->next[c].reset(add_node(root->next[c].release(), word, sz + 1));
        }
        return root;
    }
 
    node *get_node(node *root, string const &word, unsigned sz) {
        if (!root || (sz == word.size()))
            return root;
        char c = word[sz];
        return get_node(root->next[c].get(), word, sz + 1);
    }
 
    unsigned size(node *root) {
        if (!root)
            return 0;
        unsigned cnt = 0;
        for (auto &c : root->next) {
            if (c.second) {
                cnt += 1 + size(c.second.get());
            }
        }
        return cnt;
    }

    void add_word(string const &word) {
        root.reset(add_node(root.release(), word, 0));
    }
 
    bool has_word(string const &word) {
        node *node = get_node(root.get(), word, 0);
        return node ? node->word : false;
    }
 
    bool has_prefix(string const &prefix) {
        node *node = get_node(root.get(), prefix, 0);
        return node;
    }

    unsigned size() {
        return size(root.get());
    }
};
