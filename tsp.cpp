/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>

#include <fstream>
#include <sstream>

#include <map>
#include <set>
#include <list>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

class edge {

    int _v;
    int _w;
    float _weight;

public:
    edge(const int &v, const int &w, const float &weight) : _v(v), _w(w), _weight(weight) {
    }

    int either() const {
        return _v;
    }

    int other(const int &v) const {
        if (v == _v)
            return _w;
        else if (v == _w)
            return _v;
        throw logic_error("inconsistent edge");
    }

    float weight() const {
        return _weight;
    }

    friend bool operator < (const edge& lhs, const edge& rhs) {
        return lhs.weight() > rhs.weight();
    }
};

typedef set<int> vertice_list;
typedef list<edge> edge_list;
typedef map<int, edge_list> adj_list;

class undirected_graph {

    vertice_list _vertices;
    edge_list _edges;
    adj_list _adj;

public:

    const edge_list& edges() const {
        return _edges;
    }

    const vertice_list &vertices() const {
        return _vertices;
    }

    const edge_list& adj(const int &v) const {
        return _adj.at(v);
    }

    friend istream& operator>>(istream& is, undirected_graph& g) {

        string line;
        getline(is, line);

        vector<pair<float, float>> city_list;

        while (getline(is, line)) {

            stringstream linestream(line);

            if (linestream) {

                pair<float, float> city;
                linestream >> city.first >> city.second;

                city_list.push_back(city);
            }
        }

        for (size_t i = 0; i < city_list.size(); ++i) {

            for (size_t j = i + 1; j < city_list.size(); ++j) {

                auto &x = city_list[i];
                auto &y = city_list[j];

                float weight = sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2));

                g._edges.push_back(edge(i, j, weight));
                g._adj[i].push_back(g._edges.back());

                g._edges.push_back(edge(j, i, weight));
                g._adj[j].push_back(g._edges.back());

                g._vertices.insert(i);
                g._vertices.insert(j);
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

    float weight() const {

        float sum(.0f);
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

    cout << "vertex count: " << g.vertices().size() << '\n';
    cout << "edge count  : " << g.edges().size() << '\n';

    cout << "prim weight : " << mst.weight() << '\n';

    cin.get();

    return 0;
}
