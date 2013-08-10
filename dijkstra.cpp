/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

#include <iostream>
#include <locale>

#include <fstream>
#include <sstream>

#include <map>

using namespace std;

class graph {

    typedef map<int,int> row_data;
    typedef map<int, row_data> data;

    data _data;

public:

    size_t count_vertices() const {
        return _data.size();
    }

    size_t count_edges() const {

        size_t n = 0;

        for (auto e = _data.begin(); e != _data.end(); ++e) {
            n += e->second.size();
        }

        return n;
    }

    struct colon_is_space : ctype<char> {
        colon_is_space() : ctype<char>(get_table()) {
        }

        static ctype_base::mask const* get_table() {
            static ctype_base::mask rc[ctype::table_size];
            rc['\t'] = ctype_base::space;
            rc[','] = ctype_base::space;
            return &rc[0];
        }
    };

    friend istream& operator>>(istream& is, graph& g) {

        string line;
        while (getline(is, line)) {

            stringstream linestream(line);
            linestream.imbue(locale(is.getloc(), new colon_is_space()));

            graph::row_data edges;

            int s;
            if (linestream) {
                linestream >> s;
            }

            int v, c;
            while (linestream >> v) {
                linestream >> c;
                edges[v] = c;
            }

            g._data[s] = edges;
        }

        return is;
    }
};

int main(int argc, char* argv[]) {

    graph graph;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in); ifs >> graph;
    }

    cout << "vertex count: " << graph.count_vertices() << '\n';
    cout << "edge count  : " << graph.count_edges() << '\n';

    cin.get();

    return 0;
}
