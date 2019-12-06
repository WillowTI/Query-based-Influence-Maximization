#include "bits/stdc++.h"
#include "head.h"

//#include "infgraph.h"
#include "imm.h"
#include "test.h"
#include "ugraph.h"
#include "ijcore.h"
#define DBG(x) do { cout<<"\e\[0;32mDEBUG: " << x << "\e[0m" << endl;} while (0)

using namespace std;

void Run(int argn, char **argv);
void run_with_parameter(InfGraph &g, const Argument & arg);

vector<set<int>> get_candidate(Graph &graph);

int main(int argn, char **argv) {
    OutputInfo info(argn, argv);
    Run(argn, argv);

//    uGraph g("", "undirected.txt");
//    g.kcore();
//    vector<int> node = g.kcore_node;
//    vector<int> deg = g.kcore_deg;
//    for (int x: node) {
//        cout << x <<  " " << deg[x] << endl;
//    }


// 计算i轴上的core的示例
//    Graph g = init_graph(argn, argv);
//    calc_diff_i(g);
//    vector<int> node = ij_core_i_node;
//    vector<int> deg = ij_core_i_deg;
//    map<int, vector<int>> calc;
//    for (int i = 0; i < g.n; i++) {
//        calc[deg[i]].emplace_back(i);
//    }
//    cout << endl;
//    map<int, vector<int>>::iterator iter;
//    for (iter = calc.begin(); iter != calc.end(); iter++) {
//        cout << iter->first << " " << iter->second.size() << endl;
//    }
//    Graph g = Graph("nethept/", "nethept/graph_ic.inf");
//    freopen("hierachy.txt", "w", stdout);
//    calc_diff(g);
//    for (int i = 0; i <= max_i; i++) {
//        for (int j = 0; j <= max_j[i]; j++) {
//            cout << i << " " << j << endl;
//            cout << ij_core_all_node[make_pair(i, j)].size() << endl;
//        }
//    }
//    for (int i = 0; i <= max_i; i++) {
//        cout << ij_core_all_node[]
//    }
    return 0;
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

//    Imm::InfluenceMaximize(g, arg);
    vector<set<int>> candidate;
    candidate = get_candidate(g);
}

vector<set<int>> get_candidate(Graph &graph) {
    vector<set<int>> candidate = vector<set<int>>();
    calc_diff(graph);
    set<int> all_node;
    for (int i = 0; i < graph.n; i++) {
        all_node.emplace(i);
    }
    int degeneracy = 0;
    for (int i = -1; i < max_i; i++) {
        set<int> i_node = ij_core_i_node[i];
        if (cover(graph.query, i_node)) {
            break;
        }
        set<int> tmp;
        set_difference(all_node.begin(), all_node.end(), i_node.begin(), i_node.end(),
                inserter(tmp, tmp.begin()));
        all_node = tmp;
        for (int j = 0; j <= max_j[i + 1]; j++) {
            set<int> tmp_result;
            set<int> j_node = ij_core_all_node[make_pair(i + 1, j)];
            set_difference(tmp.begin(), tmp.end(), j_node.begin(), j_node.end(), inserter(tmp_result, tmp_result.begin()));
            tmp = tmp_result;
            if (i + j + 1 == degeneracy) {
                candidate.emplace_back(tmp);
            } else if (i + j + 1 > degeneracy) {
                degeneracy = i + j + 1;
                candidate.clear();
                candidate.emplace_back(tmp);
            }
            degeneracy = max(degeneracy, i + j + 1);
            if (cover(graph.query, j_node)) {
                break;
            }
        }
    }
    return candidate;
}
