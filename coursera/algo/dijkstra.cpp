/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <locale>

#include <fstream>
#include <sstream>

#include <map>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

class index_min_pq {
    int NMAX, N, *heap, *index, *keys;

    void swap(int i, int j) {
        int t = heap[i];
        heap[i] = heap[j];
        heap[j] = t;
        index[heap[i]] = i;
        index[heap[j]] = j;
    }

    void bubbleUp(int k) {
        while (k > 1 && keys[heap[k / 2]] > keys[heap[k]]) {
            swap(k, k / 2);
            k = k / 2;
        }
    }

    void bubbleDown(int k) {
        int j;
        while (2 * k <= N) {
            j = 2 * k;
            if (j < N && keys[heap[j]] > keys[heap[j + 1]])
                j++;
            if (keys[heap[k]] <= keys[heap[j]])
                break;
            swap(k, j);
            k = j;
        }
    }

public:

    index_min_pq(int NMAX) {
        this->NMAX = NMAX;
        N = 0;
        keys = new int[NMAX + 1];
        heap = new int[NMAX + 1];
        index = new int[NMAX + 1];
        for (int i = 0; i <= NMAX; i++)
            index[i] = -1;
    }

    ~index_min_pq() {
        delete[] keys;
        delete[] heap;
        delete[] index;
    }

    bool isEmpty() {
        return N == 0;
    }

    bool contains(int i) {
        return index[i] != -1;
    }

    int size() {
        return N;
    }

    void insert(int i, int key) {
        N++;
        index[i] = N;
        heap[N] = i;
        keys[i] = key;
        bubbleUp(N);
    }

    int minIndex() {
        return heap[1];
    }

    int minKey() {
        return keys[heap[1]];
    }

    int delMin() {
        int min = heap[1];
        swap(1, N--);
        bubbleDown(1);
        index[min] = -1;
        heap[N + 1] = -1;
        return min;
    }

    int key(int i) {
        return keys[i];
    }

    void change(int i, int key) {
        keys[i] = key;
        bubbleUp(index[i]);
        bubbleDown(index[i]);
    }

    void decKey(int i, int key) {
        keys[i] = key;
        bubbleUp(index[i]);
    }

    void incKey(int i, int key) {
        keys[i] = key;
        bubbleDown(index[i]);
    }

    void delKey(int i) {
        int ind = index[i];
        swap(ind, N--);
        bubbleUp(ind);
        bubbleDown(ind);
        index[i] = -1;
    }
};


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

class graph {

public:

    typedef vector <edge> edge_list;
    typedef map<int, edge_list> adj_list;

    adj_list _adj;

    int m() const {
        return _adj.size();
    }

    int n() const {
        int n = 0;
        for (auto e : _adj) {
            n += e.second.size();
        }
        return n;
    }

    edge_list adj(int v) {
        return _adj[v];
    }

    edge_list edges() const {
        edge_list edges;
        for (auto e : _adj) {
            edges.insert(edges.end(), e.second.begin(), e.second.end());
        }
        return edges;
    }

    struct colon_is_space : ctype<char> {
        colon_is_space() : ctype<char>(get_table()) {
        }

        static ctype_base::mask const *get_table() {
            static ctype_base::mask rc[ctype::table_size];
            rc['\t'] = ctype_base::space;
            rc[','] = ctype_base::space;
            return &rc[0];
        }
    };

    friend istream &operator>>(istream &is, graph &g) {

        string line;
        while (getline(is, line)) {

            stringstream linestream(line);
            linestream.imbue(locale(is.getloc(), new graph::colon_is_space()));

            edge_list edges;

            int v;
            if (linestream) {
                linestream >> v;
            }

            int w, weight;
            while (linestream >> w) {
                linestream >> weight;
                edges.push_back(edge(v, w, weight));
            }
            g._adj[v] = edges;
        }
        return is;
    }
};

class dijkstra_sp {

    map<int, edge> _edge_to;
    map<int, int> _dist_to;
    index_min_pq _pq;

    void relax(graph &g, const int &v) {

        for (auto e : g.adj(v)) {
            int w = e.to();

            if (_dist_to[w] > _dist_to[v] + e.weight()) {
                _dist_to[w] = _dist_to[v] + e.weight();
                _edge_to[w] = e;

                if (_pq.contains(w)) {
                    _pq.change(w, _dist_to[w]);
                }
                else {
                    _pq.insert(w, _dist_to[w]);
                }
            }
        }
    }

public:

    dijkstra_sp(graph &g, const int &s) : _pq(g.m()) {

        for (auto e : g._adj) {
            _dist_to[e.first] = INT_MAX;
        }
        _dist_to[s] = 0;

        _pq.insert(s, 0);
        while (!_pq.isEmpty()) {
            relax(g, _pq.delMin());
        }
    }

    int dist(int v) {
        return _dist_to[v];
    }

    bool hasPath(int v) {
        return _dist_to[v] < INT_MAX;
    }

    stack <edge> path(int v) {
        stack <edge> path;
        for (auto e = _edge_to[v]; e.to() != 0; e = _edge_to[e.from()]) {
            path.push(e);
        }
        return path;
    }
};

int main(int argc, char *argv[]) {

    graph g;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in);
        ifs >> g;
    }

    cout << "vertex count: " << g.m() << '\n';
    cout << "edge count  : " << g.n() << '\n';

    //int s;
    //cout << "s vertex: ";

    //cin >> s;
    dijkstra_sp sp(g, 1);

    //cout << "type vertices\n";
    vector<int> ss = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
    //while (cin >> s) {
    for (auto s : ss) {
        cout << sp.dist(s) << ',';
    }

    cin.get();

    return 0;
}
