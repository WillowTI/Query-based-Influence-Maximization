//
// Created by lenovo on 2019/10/18.
//

#ifndef QIC_IJCORE_H
#define QIC_IJCORE_H

#include "bits/stdc++.h"
#include "graph.h"
using namespace std;
set<int> ij_core [33][33];
set<int> diff_j[32][32];
set<int> diff_i[32];
vector<int> ij_core_i_deg;
vector<int> ij_core_i_node;

void calc_diff() {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            set_difference(ij_core[i][j].begin(), ij_core[i][j].end(),
                           ij_core[i][j + 1].begin(), ij_core[i][j + 1].end(), inserter(diff_j[i][j], diff_j[i][j].begin()));
        }
    }

    for (int i = 0; i < 32; i++) {
        set_difference(ij_core[i][0].begin(), ij_core[i][0].end(),
                       ij_core[i + 1][0].begin(), ij_core[i + 1][0].end(), inserter(diff_i[i], diff_i[i].begin()));
    }

    freopen("diff_j.txt", "w", stdout);
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            cout << i << " " << j << " " << diff_j[i][j].size() << endl;
            for (int x: diff_j[i][j]) {
                cout << x << " ";
            }
            cout << endl;
        }
    }

//    freopen("diff_i.txt", "w", stdout);
//    for (int i = 0; i < 32; i++) {
//        cout << i << " " << diff_i[i].size() << endl;
//        for (int x: diff_i[i]) {
//            cout << x << " ";
//        }
//        cout << endl;
//    }
}

// 从文件读所有的 ij-core
void get_sample_ij_core() {
    freopen("all_ij_core.txt", "r", stdin);
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            int i1, i2, n;
            cin >> i1 >> i2 >> n;
            for (int k = 0; k < n; k++) {
                int iii;
                cin >> iii;
                ij_core[i][j].insert(iii);
            }
        }
    }
}

// 从文件读
void get_diff_i() {
    freopen("diff_i.txt", "r", stdin);
    for (int i = 0; i < 32; i++) {
        int j, n;
        int x;
        cin >> j >> n;
        for (int k = 0; k < n; k++) {
            cin >> x;
            diff_i[i].emplace(x);
        }
    }
}

// 计算 i，也就是入度方向上的 core
void calc_diff_i(Graph g) {
    ij_core_i_node = vector<int>(g.n, 0);
    vector<int> bin(g.in_max + 1, 0);
    ij_core_i_deg = g.inDeg;
    for (int i = 0; i < g.n; i++) {
        bin[g.inDeg[i]]++;
    }

    int start = 0;
    int num = 0;
    for (int & i: bin) {
        num = i;
        i = start;
        start += num;
    }

    vector<int> pos(g.n);
    for (int i = 0; i < g.n; i++) {
        pos[i] = bin[g.inDeg[i]];
        ij_core_i_node[pos[i]] = i;
        bin[g.inDeg[i]]++;
    }

    for (int i = bin.size() - 1; i >= 1; i--) {
        bin[i] = bin[i - 1];
    }
    bin[0] = 0;

    for (int i = 0; i < g.n; i++) {
        int v = ij_core_i_node[i];
        for (int u: g.g[v]) {
            if (ij_core_i_deg[u] > ij_core_i_deg[v]) {
                int du = ij_core_i_deg[u];
                int pu = pos[u];
                int pw = bin[du];
                int w = ij_core_i_node[pw];
                if (u != w) {
                    pos[u] = pw;
                    pos[w] = pu;
                    ij_core_i_node[pu] = w;
                    ij_core_i_node[pw] = u;
                }
                bin[du]++;
                ij_core_i_deg[u]--;
            }
        }
    }
}




#endif //QIC_IJCORE_H
