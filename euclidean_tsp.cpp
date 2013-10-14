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
#include <stack>
#include <cmath>

using namespace std;

class edge {

    int _v;
    int _w;
    float _weight;

public:
    edge(const int &v, const int &w, const float &weight) : _v(v), _w(w), _weight(weight) {
    }

    int v() const {
        return _v;
    }

    int w() const {
        return _w;
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

    const float minWeight(const int &v, const int &w) const {

        float weight = 999999.9999f;

        for (auto &e : _edges) {
            if (e.v() == v && e.w() == w && e.weight() < weight)
                weight = e.weight();
        }

        return weight;
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
    typedef priority_queue<edge> min_queue;

    const undirected_graph _g;

    visited_map _visited;
    edge_list _mst;
    min_queue _min;

    void visit(const int &v) {

        _visited[v] = true;

        for (auto &e : _g.adj(v)) {
            if (!_visited[e.other(v)])
                _min.push(e);
        }
    }

public:
    lazy_prim_mst(const undirected_graph &g) : _g(g) {

        visit(0);

        while (!_min.empty()) {
            edge e = _min.top(); _min.pop();

            int v = e.either();
            int w = e.other(v);

            if (_visited[v] && _visited[w])
                continue;

            _mst.push_back(e);

            if (!_visited[v])
                visit(v);
            if (!_visited[w])
                visit(w);
        }
    }

    float weight() const {

        float sum(.0f);
        for (auto &e : _mst) {
            sum += e.weight();
        }

        return sum;
    }

    float tsp_weight() const {

        map<int, vector<int>> dfs_walk;

        for (auto &e : _mst) {
            dfs_walk[e.v()].push_back(e.w());
        }

        vector<int> ham_tour;
        visited_map visited;

        stack<int> to_visit;
        to_visit.push(0);

        while (!to_visit.empty()) {

            int top = to_visit.top(); to_visit.pop();
            visited[top] = true;

            ham_tour.push_back(top);

            for (auto &v : dfs_walk[top]) {
                if (!visited[v])
                    to_visit.push(v);
            }
        }

        ham_tour.push_back(0);

        float sum(.0f);

        for (size_t i = 1; i < ham_tour.size(); ++i) {

            sum += _g.minWeight(ham_tour[i - 1], ham_tour[i]);
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
    cout << "tsp weight  : " << mst.tsp_weight() << '\n';

    cin.get();

    return 0;
}