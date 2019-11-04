#ifndef SFMT_GRAPH_H
#define SFMT_GRAPH_H
#include "head.h"
#include "sfmt.h"
#include "Argument.h"
using namespace std;
class Graph {
public:
    int n;//node
    int m;//edge
    int active_n;
    int in_max;
    int out_max;
    enum InfluModel {IC, LT, CONT};
    string folder;
    string graph_file;
    InfluModel influModel;
    vector<int> inDeg;
    vector<int> outDeg;
    vector<vector<int>> gT;
    vector<vector<int>> g;
    vector<vector<double>> probT;
    //当有(a, b, p)时，gT[b].add(a), probT[b].add(p)

    vector<bool> hasnode;
    //hasnode用来判断孤立点

    vector<bool> vis;

    Graph(string folder, string graph_file): folder(folder), graph_file(graph_file)
    {
        readNM();
        in_max = out_max = 0;
        g = vector<vector<int>>(n);
        gT = vector<vector<int>>(n);
        hasnode = vector<bool>(n, false);
        probT = vector<vector<double>>(n);
        inDeg = vector<int>(n, 0);
        outDeg = vector<int>(n, 0);
        vis = vector<bool>(n);
        readGraph();
        active_n = n;
        //system("sleep 10000");
    }

    Graph(int n) {
        in_max = out_max = 0;
        this->n = n;
        active_n = n;
        inDeg = vector<int>(n);
        outDeg = vector<int>(n);
        g = vector<vector<int>>(n);
        gT = vector<vector<int>>(n);
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

    void add_edge(int a, int b, double p)
    {
        probT[b].push_back(p);
        gT[b].push_back(a);
        g[a].push_back(b);
        inDeg[b]++;
        outDeg[a]++;
        in_max = max(in_max, inDeg[b]);
        out_max = max(out_max, outDeg[a]);
    }

    void add_edge(int a, int b) {
        gT[b].push_back(a);
        g[a].push_back(b);
        inDeg[b]++;
        outDeg[a]++;
        in_max = max(in_max, inDeg[b]);
        out_max = max(out_max, outDeg[a]);
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
            double p;
            int c = fscanf(fin, "%d%d%lf", &a, &b, &p);
            ASSERTT(c == 3, a, b, p, c);
            ASSERT( a < n );
            ASSERT( b < n );
            hasnode[a] = true;
            hasnode[b] = true;
            add_edge(a, b, p);
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

};

double sqr(double t)
{
    return t * t;
}
#endif //SFMT_GRAPH_H