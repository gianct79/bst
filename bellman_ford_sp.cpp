/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>

#include <fstream>
#include <sstream>

#include <vector>
#include <set>
#include <list>

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

    int from() const {
        return _v;
    }

    int to() const {
        return _w;
    }

    int weight() const {
        return _weight;
    }
};

typedef set<int> vertice_list;
typedef list<edge> edge_list;

class graph {

    vertice_list _vertices;
    edge_list _edges;

public:

    const edge_list& edges() const {
        return _edges;
    }

    const vertice_list &vertices() const {
        return _vertices;
    }

    friend istream& operator>>(istream& is, graph& g) {

        string line;
        getline(is, line);

        while (getline(is, line)) {

            stringstream linestream(line);

            int v, w, weight;
            if (linestream) {
                linestream >> v >> w >> weight;

                g._vertices.insert(v);
                g._vertices.insert(w);

                edge e(v, w, weight);
                g._edges.push_back(e);
            }
        }
        return is;
    }
};

const int MAX = 0x3f3f3f3f;

typedef vector<int> distance_vector;

class bellman_ford_sp {

    distance_vector _dist_to;
    bool _negative_cycle;

public:

    bellman_ford_sp(graph &g, const int &s) {

        _negative_cycle = false;

        const vertice_list &vertices = g.vertices();
        _dist_to.reserve(vertices.size());

        for (auto &v : vertices) {
            _dist_to[v - 1] = MAX;
        }
        _dist_to[s - 1] = 0;

        for (size_t i = 0; i <= vertices.size() - 1; ++i) {

            for (auto &e : g.edges()) {

                int u = e.from();
                int v = e.to();

                if (_dist_to[v - 1] > _dist_to[u - 1] + e.weight()) {
                    _dist_to[v - 1] = _dist_to[u - 1] + e.weight();
                }
            }
        }

        for (auto &e : g.edges()) {
            int u = e.from();
            int v = e.to();

            if (_dist_to[v - 1] > _dist_to[u - 1] + e.weight()) {
                _negative_cycle = true;
                break;
            }
        }
    }

    bool negativeCycle() const {
        return _negative_cycle;
    }

    int dist(int v) const {
        return _dist_to[v - 1];
    }

    bool hasPath(int v) const {
        return _dist_to[v - 1] < MAX;
    }
};

int main(int argc, char* argv[]) {

    graph g;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in); ifs >> g;
    }

    cout << "n: " << g.vertices().size() << '\n';
    cout << "m: " << g.edges().size() << '\n';

    int sd = MAX;

    for (auto &w : g.vertices()) {

        bellman_ford_sp sp(g, w);
        cout << "-: " << sp.negativeCycle();

        for (auto &v : g.vertices()) {
            int d = sp.dist(v);
            if (d < sd)
                sd = d;
        }

        cout << " s: " << sd << '\n';
    }

    cin.get();

    return 0;
}
