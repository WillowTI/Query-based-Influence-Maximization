//
// Created by lenovo on 2019/10/18.
//

#ifndef QIC_IJCORE_H
#define QIC_IJCORE_H

#include "bits/stdc++.h"
#include <vector>
#include "graph.h"
using namespace std;

set<int> ij_core [33][33];
set<int> diff_j[32][32];
set<int> diff_i[32];
vector<int> tmp_ij_core_i_deg;
vector<int> tmp_ij_core_i_node;
map<pair<int, int>, vector<int>> ij_core_all_node;
map<int, vector<int>> ij_core_i_node;
int max_i = 0;
vector<int> max_j;

void delete_node(Graph &graph, vector<int> &vector, std::vector<int> &out_deg, std::vector<int> &out_bin);
void calc_diff_brutal();
void get_sample_ij_core();
void get_diff_i();
void calc_diff(Graph g1);
void calc_diff_i(Graph g1);


void calc_diff_brutal() {
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
    tmp_ij_core_i_node = vector<int>(g.n, 0);
    vector<int> bin(g.in_max + 1, 0);
    tmp_ij_core_i_deg = g.inDeg;
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
        tmp_ij_core_i_node[pos[i]] = i;
        bin[g.inDeg[i]]++;
    }

    for (int i = bin.size() - 1; i >= 1; i--) {
        bin[i] = bin[i - 1];
    }
    bin[0] = 0;

    for (int i = 0; i < g.n; i++) {
        int v = tmp_ij_core_i_node[i];
        for (int u: g.g[v]) {
            if (tmp_ij_core_i_deg[u] > tmp_ij_core_i_deg[v]) {
                int du = tmp_ij_core_i_deg[u];
                int pu = pos[u];
                int pw = bin[du];
                int w = tmp_ij_core_i_node[pw];
                if (u != w) {
                    pos[u] = pw;
                    pos[w] = pu;
                    tmp_ij_core_i_node[pu] = w;
                    tmp_ij_core_i_node[pw] = u;
                }
                bin[du]++;
                tmp_ij_core_i_deg[u]--;
            }
        }
    }
}


void calc_diff(Graph g1) {
    Graph g = g1;
    calc_diff_i(g);
    for (int x: tmp_ij_core_i_node) {
        ij_core_i_node[tmp_ij_core_i_deg[x]].emplace_back(x);
    }
    ij_core_i_node[-1] = vector<int>();
//    ij_core_all_node = vector<vector<vector<int>>>(ij_core_i_node.size());
    for (auto & iter : ij_core_i_node) {
        max_i = max(max_i, iter.first);
    }
    vector<int> out_bin = vector<int>(g.out_max + 1);
    vector<int> out_deg = g.outDeg;

    for (int i = 0; i < g.n; i++) {
        out_bin[g.outDeg[i]]++;
    }

    for (int in = -1; in < max_i; in++) {
        vector<int> iter = ij_core_i_node[in];
        delete_node(g, iter, out_deg, out_bin);
        vector<int> tmp_out_deg = out_deg;
        vector<int> tmp_out_node = vector<int>(g.n);
        vector<int> tmp_out_bin = out_bin;

        int start = 0;
        int num = 0;
        for (int &i: tmp_out_bin) {
            num = i;
            i = start;
            start += num;
        }

        vector<int> out_pos(g.n);
        for (int i = 0; i < g.n; i++) {
            if (g.vis[i]) {
                continue;
            }
            out_pos[i] = tmp_out_bin[tmp_out_deg[i]];//点i放在什么位置
            tmp_out_node[out_pos[i]] = i;//把点从小到大按度排序
            tmp_out_bin[tmp_out_deg[i]]++;//维护下一个的位置
        }

        for (int i = tmp_out_bin.size() - 1; i >= 1; i--) {
            tmp_out_bin[i] = tmp_out_bin[i - 1];
        }
        tmp_out_bin[0] = 0;

        for (int i = 0; i < g.n; i++) {
            int v = tmp_out_node[i];
            if (g.vis[v]) {
                continue;
            }
            for (int u: g.gT[v]) { //访问入的邻居
                if (g.vis[u]) {
                    continue;
                }
                if (tmp_out_deg[u] > tmp_out_deg[v]) {
                    int du = tmp_out_deg[u];
                    int pu = out_pos[u];
                    int pw = tmp_out_bin[du];
                    int w = tmp_out_node[pw];
                    if (u != w) {
                        out_pos[u] = pw;
                        out_pos[w] = pu;
                        tmp_out_node[pu] = w;
                        tmp_out_node[pw] = u;
                    }
                    tmp_out_bin[du]++;
                    tmp_out_deg[u]--;
                }
            }
        }
        int tmp_size = -1;
        for (int i = 0; i < g.n; i++) {
            if (g.vis[i]) {
                continue;
            }
            tmp_size = max(tmp_size, tmp_out_deg[i]);
        }
        int tmp_max = -1;
        for (int i = 0; i < g.n; i++) {
            if (g.vis[i]) {
                continue;
            }
            tmp_max = max(tmp_max, tmp_out_deg[i]);
            ij_core_all_node[make_pair(in + 1, tmp_out_deg[i])].emplace_back(i);
        }
        max_j.emplace_back(tmp_max);
    }
}

void delete_node(Graph &graph, vector<int> &vector, std::vector<int> &out_deg, std::vector<int> &out_bin) {
    for (int &x: vector) {
        graph.vis[x] = true;
    }

    // remove xx->vector
    for (int &x: vector) {
        for (int &out: graph.gT[x]) {
            if (!graph.vis[out]) {
                out_bin[out_deg[out]]--;
                out_deg[out]--;
                out_bin[out_deg[out]]++;
            }
        }
        out_bin[out_deg[x]]--;
    }
    graph.active_n -= vector.size();
}



#endif //QIC_IJCORE_H
