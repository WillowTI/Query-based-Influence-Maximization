//
// Created by lenovo on 2019/11/4.
//

#ifndef QIC_TEST_H
#define QIC_TEST_H

#include "graph.h"
Graph read_subgraph(char* file);
Graph build_subgraph();

int n = 15229;
int m = 62752;
vector<bool> vis = vector<bool>(15229);
Graph read_subgraph(char* file) {
    freopen(file, "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        int sz;
        cin >> sz;
        while (sz--) {
            int x;
            cin >> x;
            vis[x] = true;
        }
    }
    return build_subgraph();
}

Graph build_subgraph() {
    freopen("nethept/graph_ic.inf", "r", stdin);
    Graph ret = Graph(n);
    int mm = m;
    while (mm--) {
        int a, b;
        double c;
        cin >> a >> b >> c;
        if (!vis[a] && !vis[b]) {
            ret.add_edge(a, b);
        }
    }
    int in_min = m;
    int out_min = m;
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        in_min = min(in_min, ret.inDeg[i]);
        out_min = min(out_min, ret.outDeg[i]);
    }
    cout << in_min << " " << out_min << endl;
    return ret;
}

#endif //QIC_TEST_H
