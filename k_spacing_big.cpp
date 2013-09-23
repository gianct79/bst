/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <fstream>

#include <bitset>

#include <unordered_map>
#include <list>
#include <queue>

using namespace std;

class edge {

    unsigned _v;
    unsigned _w;
    size_t _weight;

public:
    edge() : edge(0, 0, 0) {
    }

    edge(const unsigned &v, const unsigned &w, const size_t &weight) : _v(v), _w(w), _weight(weight) {
    }

    unsigned either() {
        return _v;
    }

    unsigned other(const unsigned &v) {
        if (v == _v)
            return _w;
        else if (v == _w)
            return _v;
        throw logic_error("inconsistent edge");
    }

    size_t weight() const {
        return _weight;
    }

    friend bool operator < (const edge& lhs, const edge& rhs) {
        return lhs.weight() > rhs.weight();
    }
};

typedef list<edge> edge_list;
typedef list<unsigned> vertex_list;
typedef queue<edge> edge_queue;
typedef priority_queue<edge> min_queue;

typedef list<bitset<24>> bit_list;

void generate_bits(bit_list &bitlist, const size_t &pos) {

    bit_list::value_type bits("1");
    bits.set(pos); bitlist.push_back(bits);

    for (size_t i = pos; i < bits.size() - 1; ++i) {
        bits <<= 1; bitlist.push_back(bits);
    }

    if (pos < bits.size() - 1)
        generate_bits(bitlist, pos + 1);
}

class undirected_graph {

    edge_list _edges;
    vertex_list _vertices;

public:
    vertex_list v() const {
        return _vertices;
    }

    edge_list e() const {
        return _edges;
    }

    friend istream& operator>>(istream& is, undirected_graph& g) {

        string line;
        getline(is, line);

        unsigned vertices(0);
        unordered_map<bit_list::value_type, unsigned> nodes;

        bit_list bits;
        generate_bits(bits, 0);

        while (getline(is, line)) {

            auto &end = remove(line.begin(), line.end(), ' ');
            line.erase(end, line.end());

            bit_list::value_type node(line);
            if (nodes.count(node) == 0) {
                g._vertices.push_back(++vertices);
                nodes[node] = vertices;
            }
        }

        for (auto &n : nodes) {
            for (auto &b : bits) {

                auto &h = n.first ^ b;
                if (nodes.count(h) > 0) {

                    size_t weight = (n.first ^ h).count();
                    unsigned v = n.second;
                    unsigned w = nodes[h];

                    g._edges.push_back(edge(v, w, weight));
                }
            }
        }

        return is;
    }
};

class union_find {

    unordered_map<unsigned, vertex_list> _id;

public:
    union_find(vertex_list &src) {
        unsigned id(0);
        for (auto &e : src) {
            _id[++id].push_back(e);
        }
    }

    unsigned find(const unsigned &p) const {
        for (auto &i : _id) {
            for (auto &e : i.second) {
                if (p == e)
                    return i.first;
            }
        }
        return 0;
    }

    void join(const unsigned &p, const unsigned &q) {

        unsigned idP = find(p);
        unsigned idQ = find(q);

        if (idP != idQ) {
            _id[idP].merge(_id[idQ]);
            _id.erase(idQ);
        }
    }

    bool connected(const unsigned &p, const unsigned &q) const {
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

        edge_list edges(g.e());

        min_queue pq(edges.begin(), edges.end());
        union_find uf(g.v());

        size_t v = g.v().size();

        while (!pq.empty() && _mst.size() < v - 1) {
            edge e = pq.top(); pq.pop();

            unsigned v = e.either();
            unsigned w = e.other(v);

            if (uf.connected(v, w))
                continue;

            uf.join(v, w);
            _mst.push(e);
        }

        cout << "max-k-cluster : " << uf.count() << '\n';
    }
};

int main(int argc, char* argv[]) {

    undirected_graph g;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in); ifs >> g;
    }

    kruskal_mst mst(g);

    cout << "vertex count  : " << g.v().size() << '\n';
    cout << "edge count    : " << g.e().size() << '\n';

    cin.get();

    return 0;
}
