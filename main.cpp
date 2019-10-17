#include "bits/stdc++.h"
#include "head.h"

//#include "infgraph.h"
#include "imm.h"
#include "ugraph.h"

#define DBG(x) do { cout<<"\e\[0;32mDEBUG: " << x << "\e[0m" << endl;} while (0)

using namespace std;

void Run(int argn, char **argv);
void run_with_parameter(InfGraph &g, const Argument & arg);
Graph init_graph(int argn, char **argv);
void get_sample_ij_core();
void calc_diff();


set<int> ij_core [32][32];
set<int> diff_j[31][31];
set<int> diff_i[31];

int main(int argn, char **argv) {
//    OutputInfo info(argn, argv);
//    Run(argn, argv);

//    uGraph g("", "undirected.txt");
//    g.kcore();
//    vector<int> node = g.kcore_node;
//    vector<int> deg = g.kcore_deg;
//    for (int x: node) {
//        cout << x <<  " " << deg[x] << endl;
//    }



    return 0;
}

void calc_diff() {
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 31; j++) {
            set_difference(ij_core[i][j].begin(), ij_core[i][j].end(),
                           ij_core[i][j + 1].begin(), ij_core[i][j + 1].end(), inserter(diff_j[i][j], diff_j[i][j].begin()));
        }
    }

    for (int i = 0; i < 31; i++) {
        set_difference(ij_core[i][0].begin(), ij_core[i][0].end(),
                       ij_core[i + 1][0].begin(), ij_core[i + 1][0].end(), inserter(diff_i[i], diff_i[i].begin()));
    }

//    freopen("diff_j.txt", "w", stdout);
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 31; j++) {
            cout << i << " " << j << " " << diff_j[i][j].size() << endl;
            for (int x: diff_j[i][j]) {
                cout << x << " ";
            }
            cout << endl;
        }

    }
}

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
//            cout << i1 << " " << i2 << " " << n << endl;
        }
    }
}

Graph init_graph(int argn, char **argv) {
    Argument arg;
    for (int i = 0; i < argn; i++) {
        if (argv[i] == string("-help") || argv[i] == string("--help") || argn == 1) {
            cout << "./tim -dataset *** -epsilon *** -k ***  -model IC|LT|TR|CONT " << endl;
            return Graph("", "");
        }
        if (argv[i] == string("-dataset"))
            arg.dataset = argv[i + 1];
        if (argv[i] == string("-epsilon"))
            arg.epsilon = atof(argv[i + 1]);
        if (argv[i] == string("-T"))
            arg.T = atof(argv[i + 1]);
        if (argv[i] == string("-k"))
            arg.k = atoi(argv[i + 1]);
        if (argv[i] == string("-model"))
            arg.model = argv[i + 1];
        ASSERT(arg.dataset != "");
        ASSERT(arg.model == "IC" || arg.model == "LT" || arg.model == "TR" || arg.model=="CONT");
    }
    string graph_file;
    if (arg.model == "IC") {
        graph_file = arg.dataset + "graph_ic.inf";
    } else if (arg.model == "LT") {
        graph_file = arg.dataset + "graph_lt.inf";
    } else if (arg.model == "TR") {
        graph_file = arg.dataset + "graph_tr.inf";
    } else if (arg.model == "CONT") {
        graph_file = arg.dataset + "graph_cont.inf";
    } else {
        ASSERT(false);
    }
    Graph g(arg.dataset, graph_file);
    return g;
}

void Run(int argn, char **argv) {
    Argument arg;
    for (int i = 0; i < argn; i++) {
        if (argv[i] == string("-help") || argv[i] == string("--help") || argn == 1) {
            cout << "./tim -dataset *** -epsilon *** -k ***  -model IC|LT|TR|CONT " << endl;
            return ;
        }
        if (argv[i] == string("-dataset"))
            arg.dataset = argv[i + 1];
        if (argv[i] == string("-epsilon"))
            arg.epsilon = atof(argv[i + 1]);
        if (argv[i] == string("-T"))
            arg.T = atof(argv[i + 1]);
        if (argv[i] == string("-k"))
            arg.k = atoi(argv[i + 1]);
        if (argv[i] == string("-model"))
            arg.model = argv[i + 1];
        ASSERT(arg.dataset != "");
        ASSERT(arg.model == "IC" || arg.model == "LT" || arg.model == "TR" || arg.model=="CONT");
    }
    string graph_file;
    if (arg.model == "IC") {
        graph_file = arg.dataset + "graph_ic.inf";
    } else if (arg.model == "LT") {
        graph_file = arg.dataset + "graph_lt.inf";
    } else if (arg.model == "TR") {
        graph_file = arg.dataset + "graph_tr.inf";
    } else if (arg.model == "CONT") {
        graph_file = arg.dataset + "graph_cont.inf";
    } else {
        ASSERT(false);
    }
    InfGraph g(arg.dataset, graph_file);


    if (arg.model == "IC")
        g.setInfuModel(InfGraph::IC);
    else if (arg.model == "LT")
        g.setInfuModel(InfGraph::LT);
    else if (arg.model == "TR")
        g.setInfuModel(InfGraph::IC);
    else if (arg.model == "CONT")
        g.setInfuModel(InfGraph::CONT);
    else
        ASSERT(false);

    INFO(arg.T);

    run_with_parameter(g, arg);

}

void run_with_parameter(InfGraph &g, const Argument & arg)
{
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << arg.dataset << " k=" << arg.k << " epsilon=" << arg.epsilon <<   " " << arg.model << endl;

    Imm::InfluenceMaximize(g, arg);

//    cout << g.in_max << " " << g.out_max << endl;
}