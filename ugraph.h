#ifndef QIC_UGRAPH_H
#define QIC_UGRAPH_H
#include "head.h"
#include "sfmt.h"
using namespace std;
class uGraph {
public:
    int n;//node
    int m;//edge
    int deg_max;
    enum InfluModel {IC, LT, CONT};
    string folder;
    string graph_file;
    InfluModel influModel;
    vector<int> deg;
    vector<vector<int>> gT;
    vector<bool> hasnode;
    //hasnode用来判断孤立点

    vector<int> kcore_node;
    vector<int> kcore_deg;

    uGraph(string folder, string graph_file): folder(folder), graph_file(graph_file)
    {
        readNM();
        deg_max = 0;
        gT = vector<vector<int>>(n);
        hasnode = vector<bool>(n, false);
        deg = vector<int>(n, 0);
        kcore_node = vector<int>(n);

        readGraph();
        //system("sleep 10000");
    }


    void setInfuModel(InfluModel p) {
        influModel = p;
        TRACE(influModel == IC);
        TRACE(influModel == LT);
        TRACE(influModel == CONT);
    }


    void readNM()
    {
        ifstream cin((folder + "attribute.txt").c_str());
        ASSERT(!cin == false);
        string s;
        while (cin >> s)
        {
            if (s.substr(0, 2) == "n=")
            {
                n = atoi(s.substr(2).c_str());
                continue;
            }
            if (s.substr(0, 2) == "m=")
            {
                m = atoi(s.substr(2).c_str());
                continue;
            }
            ASSERT(false);
        }
        TRACE(n, m);
        cin.close();
    }

    void add_edge(int a, int b)
    {
        gT[b].push_back(a);
        gT[a].push_back(b);
        deg[b]++;
        deg[a]++;
        deg_max = max(deg_max, deg[b]);
        deg_max = max(deg_max, deg[a]);
    }

    void readGraph()
    {
        FILE *fin = fopen((graph_file).c_str(), "r");
        ASSERT(fin != false);
        int readCnt = 0;
        for (int i = 0; i < m; i++)
        {
            readCnt++;
            int a, b;
            int c = fscanf(fin, "%d%d", &a, &b);
            ASSERT( a < n );
            ASSERT( b < n );
            hasnode[a] = true;
            hasnode[b] = true;
            add_edge(a, b);
        }
        TRACE_LINE_END();
        int s = 0;
        for (int i = 0; i < n; i++)
            if (hasnode[i])
                s++;
        INFO(s);
        ASSERT(readCnt == m);
        fclose(fin);
    }

    // 利用 hierarchy 的性质计算给定无向图的 k-core
    // O(m + n)
    // kcore_node 存储从小到大排列的点
    // kcore_deg 计算点 i 支持的最大 k-core 的 k，注意，和 kcore_node 不是对应的关系
    // 需要用 kcore_node 作为索引
    void kcore() {
        vector<int> bin(deg_max + 1, 0); // 注意，需要deg_max + 1的大小
        kcore_deg = deg;

        for (int i = 0; i < n; i++) {
            bin[deg[i]]++;
        }

        int start = 0;
        int num = 0;
        for (int & i : bin) {
            num = i;
            i = start;
            start += num;
        }
        // bin[i] 存储度为 i 的点的起点位置

        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[i] = bin[deg[i]];
            kcore_node[pos[i]] = i;
            bin[deg[i]]++;
        }
        // pos[i] 存储点 i 的位置
        // kcore_node[i] 是 pos 的取反，也就是点 i 在哪个位置
        // bin[i] 变为点 i + 1 的起点位置，没有意义

        for (int i = bin.size() - 1; i >= 1; i--) {
            bin[i] = bin[i - 1];
        }
        bin[0] = 0;
        // 恢复 bin 为存储度为 i 的点的起点位置

        for (int i = 0; i < n; i++) {
            int v = kcore_node[i];
            for (int u: gT[v]) {
                if (kcore_deg[u] > kcore_deg[v]) {
                    int du = kcore_deg[u];
                    int pu = pos[u];
                    int pw = bin[du];
                    int w = kcore_node[pw];
                    // 获取与 u 相同度数，且排在最前的点，如果不是 u，交换
                    // 相当于把 u 放在最前面
                    if (u != w) {
                        pos[u] = pw;
                        pos[w] = pu;
                        kcore_node[pu] = w;
                        kcore_node[pw] = u;
                    }
                    bin[du]++;
                    kcore_deg[u]--;
                }
            }
        }
    }
};
#endif //QIC_UGRAPH_H