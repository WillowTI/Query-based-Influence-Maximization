#include "bits/stdc++.h"
#include "head.h"

//#include "infgraph.h"
#include "imm.h"

#define DBG(x) do { cout<<"\e\[0;32mDEBUG: " << x << "\e[0m" << endl;} while (0)

using namespace std;

void Run(int argn, char **argv);
void run_with_parameter(InfGraph &g, const Argument & arg);
Graph init_graph(int argn, char **argv);


int main(int argn, char **argv) {
    OutputInfo info(argn, argv);
    Run(argn, argv);

//    Graph g = init_graph(argn, argv);


    return 0;
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