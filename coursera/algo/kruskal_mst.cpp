/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>

#include <fstream>
#include <sstream>

#include <map>
#include <list>
#include <queue>

using namespace std;

class edge {

    int _v;
    int _w;
    int _weight;

public:
    edge() : edge(0, 0, 0) {
    }

    edge(const int &v, const int &w, const int &weight) : _v(v), _w(w), _weight(weight) {
    }

    int either() {
        return _v;
    }

    int other(const int &v) {
        if (v == _v)
            return _w;
        else if (v == _w)
            return _v;
        throw logic_error("inconsistent edge");
    }

    int weight() const {
        return _weight;
    }

    friend bool operator<(const edge &lhs, const edge &rhs) {
        return lhs.weight() > rhs.weight();
    }
};

typedef list <edge> edge_list;
typedef queue <edge> edge_queue;
typedef priority_queue <edge> min_queue;

class undirected_graph {

    typedef map<int, edge_list> adj_list;
    adj_list _adj;

public:
    size_t v() {
        return _adj.size();
    }

    size_t e() {
        int n(0);
        for (auto &e : _adj) {
            n += e.second.size();
        }
        return (n / 2);
    }

    list<int> vertices() {
        list<int> b;
        for (auto &a : _adj) {
            b.push_back(a.first);
        }
        return b;
    }

    edge_list edges() {
        edge_list b;
        for (auto &a : _adj) {
            for (auto &e : a.second) {
                if (e.other(a.first) > a.first)
                    b.push_back(e);
            }
        }
        return b;
    }

    friend istream &operator>>(istream &is, undirected_graph &g) {

        string line;
        getline(is, line);

        while (getline(is, line)) {

            stringstream linestream(line);

            int v, w, weight;
            if (linestream) {
                linestream >> v >> w >> weight;

                g._adj[v].push_back(edge(v, w, weight));
                g._adj[w].push_back(edge(w, v, weight));
            }
        }

        return is;
    }
};

class union_find {

    map<int, list<int>> _id;

public:
    union_find(const list<int> &src) {
        int id(0);
        for (auto &e : src) {
            _id[++id].push_back(e);
        }
    }

    int find(const int &p) const {
        for (auto &i : _id) {
            for (auto &e : i.second) {
                if (p == e)
                    return i.first;
            }
        }
        return 0;
    }

    void join(const int &p, const int &q) {

        int idP = find(p);
        int idQ = find(q);

        if (idP != idQ) {
            _id[idP].merge(_id[idQ]);
            _id.erase(idQ);
        }
    }

    bool connected(const int &p, const int &q) const {
        return find(p) == find(q);
    }

    size_t count() const {
        return _id.size();
    }
};

class kruskal_mst {

    edge_queue _mst;

public:
    kruskal_mst(undirected_graph &g) {

        edge_list edges(g.edges());

        min_queue pq(edges.begin(), edges.end());
        union_find uf(g.vertices());

        while (!pq.empty() && _mst.size() < g.v() - 1) {
            edge e = pq.top();
            pq.pop();

            int v = e.either();
            int w = e.other(v);

            if (uf.connected(v, w))
                continue;

            uf.join(v, w);
            _mst.push(e);
        }
    }

    int weight() const {

        int sum(0);
        edge_queue edges(_mst);

        while (!edges.empty()) {
            edge e = edges.front();
            edges.pop();
            sum += e.weight();
        }

        return sum;
    }
};

int main(int argc, char *argv[]) {

    undirected_graph g;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in);
        ifs >> g;
    }

    kruskal_mst mst(g);

    cout << "vertex count  : " << g.v() << '\n';
    cout << "edge count    : " << g.e() << '\n';

    cout << "kruskal weight: " << mst.weight() << '\n';

    cin.get();

    return 0;
}
