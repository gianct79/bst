/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <list>
#include <map>

#include <random>

using namespace std;

class int_rand {

    random_device _rd;
    mt19937 _gen;

    uniform_int_distribution<> _dist;

public:
    int_rand(int lo, int hi) : _gen{_rd()}, _dist{lo, hi} {
    }

    int operator()() {
        return _dist(_gen);
    }
};

template<typename T>
T random_element(T begin, T end) {

    const size_t s = distance(begin, end);

    int_rand rnd(0, s - 1);

    advance(begin, rnd());

    return begin;
}

class karger_graph {

    typedef list <size_t> matrix_row;
    typedef map <matrix_row::value_type, matrix_row> matrix;

    matrix _data;

public:

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

    karger_graph &remove_self_loops() {

        for (matrix::iterator it = _data.begin(); it != _data.end(); ++it) {
            it->second.remove(it->first);
        }

        return *this;
    }

    karger_graph &merge_vertices(const size_t &v, const size_t &u) {

        if (v == u)
            return *this;

        for (matrix_row::const_iterator it_u = _data[u].begin(); it_u != _data[u].end(); ++it_u) {
            _data[v].push_back(*it_u);
        }

        _data.erase(u);

        for (matrix::iterator it_r = _data.begin(); it_r != _data.end(); ++it_r) {
            for (matrix_row::iterator it_c = it_r->second.begin(); it_c != it_r->second.end(); ++it_c) {
                if (*it_c == u)
                    *it_c = v;
            }
        }

        remove_self_loops();

        return *this;
    }

    static void random_contraction_algorithm(karger_graph &km) {

        while (km.count_vertices() > 2) {

            size_t v = random_element(km._data.begin(), km._data.end())->first;
            if (km._data[v].size() > 0) {
                size_t u = *random_element(km._data[v].begin(), km._data[v].end());
                km.merge_vertices(v, u);
            }
        }
    }

    friend istream &operator>>(istream &is, karger_graph &km) {

        string line;
        while (getline(is, line)) {

            karger_graph::matrix_row vertices;
            stringstream linestream(line);

            size_t k;
            if (linestream) {
                linestream >> k;
            }

            size_t v;
            while (linestream >> v) {
                km._data[v].remove(k); // remove duplicated edges
                vertices.push_back(v);
            }

            km._data[k] = vertices;
        }

        km.remove_self_loops();

        return is;
    }
};

int main(int argc, char *argv[]) {

    karger_graph graph;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in);
        ifs >> graph;
    }

    cout << "vertex count: " << graph.count_vertices() << '\n';
    cout << "edge count  : " << graph.count_edges() << '\n';

    size_t n = graph.count_vertices();

    size_t minimum_cut = graph.count_vertices();
    size_t runs = n * n;

    for (size_t i = 0; i < runs; ++i) {

        karger_graph copy = graph;
        karger_graph::random_contraction_algorithm(copy);

        size_t cut = copy.count_edges();

        if (cut < minimum_cut) {

            cout << "run #: " << i << '\n';
            cout << "vertex count: " << copy.count_vertices() << '\n';
            cout << "edge count  : " << cut << '\n';

            minimum_cut = cut;
        }
    }

    cout << "runs: " << runs << '\n';

    cin.get();

    return 0;
}
