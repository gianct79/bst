/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <time.h>
#include <math.h>

using namespace std;

template <class T>
class karger_graph {

    vector<vector<T>> _data;

public:

    size_t get_size() const {
        return _data.size();
    }

    size_t count_vertices() const {
        return _data.size();
    }

    size_t count_edges() const {

        size_t n = 0;
        for (size_t i = 0; i < get_size(); ++i) {
            n += _data[i].size() - 1;
        }

        return n;
    }

    karger_graph& remove_self_loops() {

        for (size_t i = 0; i < get_size(); ++i) {

            vector<T> vertices;
            vertices.push_back(_data[i][0]);

            for (size_t j = 1; j < _data[i].size(); ++j) {
                if (_data[i][j] != vertices[0]) {
                    vertices.push_back(_data[i][j]);
                }
            }
            _data[i] = vertices;
        }

        return *this;
    }

    karger_graph& merge_vertices(size_t u, size_t v) {

        if (u < get_size() && v < get_size()) {

            for (size_t i = 0; i < _data[v].size(); ++i) {
                _data[u].push_back(_data[v][i]);
            }
        }

        return *this;
    }

    static void random_contraction_algorithm(karger_graph& km) {

        km.remove_self_loops();

        while (km.count_vertices() > 2) {

            size_t u, v;
            do {
                u = rand() % km.get_size();
                v = rand() % km.get_size();
            } while (u == v);

            km.merge_vertices(u, v);
            km.remove_self_loops();
        }
    }

    friend istream& operator>>(istream& is, karger_graph& km) {

        string line;
        while (getline(is, line)) {

            vector<T> vertices;
            stringstream linestream(line);

            T v;
            while (linestream >> v) {
                vertices.push_back(v);
            }

            km._data.push_back(vertices);
        }

        return is;
    }
};

int main(int argc, char* argv[]) {

    karger_graph<short> graph, minimum_graph;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in); ifs >> graph;
    }

    cout << "vertex count: " << graph.count_vertices() << '\n';
    cout << "edge count  : " << graph.count_edges() << '\n';

    srand(static_cast<unsigned int>(time(0)));

    size_t n = graph.count_vertices();

    float ln = log(static_cast<float>(n));
    size_t runs = static_cast<size_t>(n * n * ln), minimum_cut = UINT_MAX;

    for (size_t i = 0; i < runs; ++i) {

        karger_graph<short> copy = graph;
        karger_graph<short>::random_contraction_algorithm(copy);

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
