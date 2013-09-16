/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>

#include <fstream>
#include <sstream>

#include <map>
#include <vector>
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

    friend bool operator < (const edge& lhs, const edge& rhs) {
        return lhs.weight() > rhs.weight();
    }
};

class undirected_graph {

    typedef vector<edge> edge_list;
    typedef map<int, edge_list> adj_list;

    adj_list _adj;

public:
    int m() {
        return _adj.size();
    }

    int n() {
        int n(0);

        for (auto &e : _adj) {
            n += e.second.size();
        }

        return (n / 2);
    }

    edge_list& adj(const int &v) {
        return _adj[v];
    }

    friend istream& operator>>(istream& is, undirected_graph& g) {

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

class lazy_prim_mst {

    typedef map<int, bool> visited_map;
    typedef queue<edge> edge_queue;
    typedef priority_queue<edge> min_queue;

    visited_map _marked;
    edge_queue _mst;
    min_queue _pq;

    void visit(undirected_graph &g, const int &v) {

        _marked[v] = true;

        for (auto &e : g.adj(v)) {
            if (!_marked[e.other(v)])
                _pq.push(e);
        }
    }

public:
    lazy_prim_mst(undirected_graph &g) {

        visit(g, 1);

        while (!_pq.empty()) {
            edge e = _pq.top(); _pq.pop();

            int v = e.either();
            int w = e.other(v);

            if (_marked[v] && _marked[w]) 
                continue;

            _mst.push(e);

            if (!_marked[v])
                visit(g, v);
            if (!_marked[w])
                visit(g, w);
        }
    }

    int weight() const {

        int sum(0);
        edge_queue edges(_mst);

        while (!edges.empty()) {
            edge e = edges.front(); edges.pop();
            sum += e.weight();
        }

        return sum;
    }
};

int main(int argc, char* argv[]) {

    undirected_graph g;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in); ifs >> g;
    }

    lazy_prim_mst mst(g);

    cout << "vertex count: " << g.m() << '\n';
    cout << "edge count  : " << g.n() << '\n';

    cout << "prim weight : " << mst.weight() << '\n';

    cin.get();

    return 0;
}
