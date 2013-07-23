/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <list>
#include <vector>
#include <map>

#include <time.h>
#include <math.h>

using namespace std;

class karger_graph {

    typedef list<size_t> matrix_row;
    typedef map<matrix_row::value_type, matrix_row> matrix;

    matrix _data;

public:

    size_t get_size() const {
        return _data.size();
    }

    vector<matrix_row::value_type> get_vertices() const {

        vector<size_t> vertices;

        for (matrix::const_iterator it = _data.begin(); it != _data.end(); ++it) {
            vertices.push_back(it->first);
        }

        return vertices;
    }

    size_t count_vertices() const {
        return _data.size();
    }

    size_t count_edges() const {

        size_t n = 0;

        for (matrix::const_iterator it = _data.begin(); it != _data.end(); ++it) {
            n += it->second.size();
        }

        return n;
    }

    karger_graph& remove_self_loops() {

        for (matrix::iterator it = _data.begin(); it != _data.end(); ++it) {
            it->second.remove(it->first);
        }

        return *this;
    }

    karger_graph& merge_vertices(const size_t &v, const size_t &u) {

        matrix::const_iterator it_v = _data.find(v);
        matrix::const_iterator it_u = _data.find(u);

        if (it_v != _data.end() &&  it_u != _data.end()) {

            _data[v].merge(_data[u]);
            _data[v].remove(u);

            _data.erase(it_u);
        }

        return *this;
    }

    static void random_contraction_algorithm(karger_graph& km) {

        km.remove_self_loops();

        while (km.count_vertices() > 2) {

            vector<size_t> vertices = km.get_vertices();

            size_t v, u;
            do {
                v = vertices[rand() % vertices.size()];
                u = vertices[rand() % vertices.size()];
            } while (v == u);

            km.merge_vertices(v, u);
            km.remove_self_loops();
        }
    }

    friend istream& operator>>(istream& is, karger_graph& km) {

        string line;
        while (getline(is, line)) {

            karger_graph::matrix_row vertices;
            stringstream linestream(line);

            size_t v;
            while (linestream >> v) {
                vertices.push_back(v);
            }

            v = vertices.front();
            vertices.pop_front();

            km._data[v] = vertices;
        }

        return is;
    }
};

int main(int argc, char* argv[]) {

    karger_graph graph, minimum_graph;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in); ifs >> graph;
    }

    cout << "vertex count: " << graph.count_vertices() << '\n';
    cout << "edge count  : " << graph.count_edges() << '\n';

    srand(static_cast<unsigned int>(time(0)));

    size_t n = graph.count_vertices();
    float ln = log(static_cast<float>(n));

    size_t minimum_cut = UINT_MAX;
    size_t runs = static_cast<size_t>(n * n * ln);

    for (size_t i = 0; i < runs; ++i) {

        karger_graph copy = graph;
        karger_graph::random_contraction_algorithm(copy);

        size_t cut = copy.count_edges();

        if (cut < minimum_cut) {
            minimum_cut = cut;
            minimum_graph = copy;
        }
    }

    cout << "runs: " << runs << '\n';

    cout << "vertex count: " << minimum_graph.count_vertices() << '\n';
    cout << "edge count  : " << minimum_graph.count_edges() << '\n';

    cin.get();

    return 0;
}
