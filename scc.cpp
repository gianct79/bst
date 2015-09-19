/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <fstream>

#include <vector>
#include <stack>
#include <map>

#include <functional>
#include <algorithm>

using namespace std;

class scc_kosaraju {

    typedef vector<int> matrix_row;
    typedef vector <matrix_row> matrix;

    matrix _data;
    matrix _rev_data;

    int _v_max;

public:
    scc_kosaraju(const int &v) : _data(v), _rev_data(v), _v_max(v) {
    }

    int get_max_vertice() const {

        return _v_max;
    }

    int count_edges() const {

        int n = 0;
        for (auto i : _data) {
            n += i.size();
        }

        return n;
    }

    friend istream &operator>>(istream &is, scc_kosaraju &g) {

        int k, v;

        while (is >> k) {

            is >> v;
            g._data[k - 1].push_back(v - 1);
            g._rev_data[v - 1].push_back(k - 1);
        }

        return is;
    }

    void dfs(const matrix &g, const int &u, const int &s, vector<bool> &used, vector<int> &res, vector<int> &lead) {

        stack<int> tovisit;
        tovisit.push(u);

        while (tovisit.size()) {

            int c = tovisit.top();
            used[c] = true;

            bool allvisited = true;

            for (auto j : g[c]) {

                if (!used[j]) {

                    allvisited = false;
                    tovisit.push(j);
                }
            }

            if (allvisited) {

                tovisit.pop();
                lead[c] = s;
                res.push_back(c);
            }
        }
    }

    void compute_scc() {

        vector<bool> used(_v_max);
        vector<int> order;
        vector<int> leader(_v_max);

        for (int s = 0, i = _v_max - 1; i >= 0; --i) {

            if (!used[i]) {
                s = i;
                dfs(_rev_data, i, s, used, order, leader);
            }
        }

        fill(used.begin(), used.end(), false);
        fill(leader.begin(), leader.end(), 0);

        vector<int> components;

        for (int s = 0, i = _v_max - 1; i >= 0; --i) {

            int u = order[i];
            if (!used[u]) {
                s = u;
                dfs(_data, u, s, used, components, leader);
            }
        }

        sort(leader.begin(), leader.end();

        vector<int> stat(_v_max);
        int p = 0;
        for (int i = 0; i < _v_max - 1; ++i) {

            if (leader[i] != leader[i + 1]) {
                stat.push_back(i - p + 1);
                p = i + 1;
            }
        }

        stat.push_back(_v_max - p);

        vector<int> scc_idx(stat.size());
        copy(scc_idx, stat.begin(), stat.begin() + scc.idx.size());

        vector<int> scc_count(scc_idx.size());
        for (int i = 0; i < scc_idx.size(); i++) {
            scc_count[i] = i;
        }


        sort(scc_count2.begin(), scc_count2.end(), greater<int>());

        s = min<int>(5, scc_count2.size());

        for (int i = 0; i < s; i++) {
            cout << scc_count2[i] << ',';
        }
    }
};

int main(int argc, char *argv[]) {

    cout << "enter max vertex: ";

    int k;
    cin >> k;

    scc_kosaraju g(k);

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in);
        ifs >> g;
    }

    cout << "max vertex : " << g.get_max_vertice() << '\n';
    cout << "edge count : " << g.count_edges() << '\n';

    g.compute_scc();

    return 0;
}
