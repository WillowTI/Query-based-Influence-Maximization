#include "bits/stdc++.h"
#include "head.h"

//#include "infgraph.h"
#include "imm.h"
#include "test.h"
#include "ugraph.h"
#include "ijcore.h"
#include "trie.h"
#define DBG(x) do { cout<<"\e\[0;32mDEBUG: " << x << "\e[0m" << endl;} while (0)

using namespace std;

void Run(int argn, char **argv);
void run_with_parameter(InfGraph &g, const Argument & arg);

vector<set<int>> get_candidate(InfGraph &graph);

void influence_max(set<int> &subgraph, InfGraph &graph, const Argument& arg);

int choose_least_influent_node(const set<int>& non_query);

Argument getArg(int argn, char **argv);

set<int> influence_max_ij_core(int i, int j, InfGraph graph, Argument arg);

bool cmp(int x, int y);

void delete_node(trie_node *node);

void down_delete(trie_node *node);

void visit(trie_node *node);

void brutal_maintain(InfGraph &graph, vector<bool> &sample_vis, int node);

void build_trie_from_disk();

void read_data_from_disk();

void trie_maintain(int node);

vector<vector<int>> hyperGT, hyperG;
int node_size = 15229;
trie tree = trie(node_size);
vector<int> degree;

int main(int argn, char **argv) {
//    OutputInfo info(argn, argv);
//    Run(argn, argv);
    read_data_from_disk();
    build_trie_from_disk();
//    trie_node* node = tree.linked_list[11428];
//    while (node != nullptr) {
//        cout << node->node_name << " " << node->node_cnt << endl;
//        node = node->list_next;
//    }
//    cout << "----------------" << endl;
    trie_maintain(11428);
    build_trie_from_disk();
    cout << "done" << endl;
    return 0;
}

void visit(trie_node *node) {
    while (node != nullptr) {
        cout << node->node_name << " " << node->node_cnt << endl;
        node = node->father;
    }
}

void delete_node(trie_node *node) {
    int cnt = node->node_cnt;
    trie_node* tmp = node;
    down_delete(node);
    node = node->father;
    while(node != nullptr) {
        degree[node->node_name] -= cnt;
        node->node_cnt -= cnt;
        node = node->father;
    }
    while(tmp->node_cnt <= 0 && tmp->father != nullptr && tmp->father->node_name != -1 && tmp->father->node_cnt <= 0) {
        tmp = tmp->father;
    }
    tree.clear_node(tmp);
}

void down_delete(trie_node *node) {
    if (node == nullptr) {
        return;
    }
    degree[node->node_name] -= node->node_cnt;
    node->node_cnt = 0;
    for (auto x: node->child) {
        down_delete(x);
    }
}

Argument getArg(int argn, char **argv) {
    Argument arg = Argument();
    for (int i = 0; i < argn; i++) {
        if (argv[i] == string("-help") || argv[i] == string("--help") || argn == 1) {
            cout << "./tim -dataset *** -epsilon *** -k ***  -model IC|LT|TR|CONT " << endl;
            return arg;
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
    return arg;
}

void Run(int argn, char **argv) {
    Argument arg = getArg(argn, argv);
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
    if (arg.model == "IC") {
        g.setInfuModel(InfGraph::IC);
    } else if (arg.model == "LT") {
        g.setInfuModel(InfGraph::LT);
    } else if (arg.model == "TR") {
        g.setInfuModel(InfGraph::IC);
    } else if (arg.model == "CONT") {
        g.setInfuModel(InfGraph::CONT);
    } else {
        ASSERT(false);
    }
    INFO(arg.T);
    run_with_parameter(g, arg);
}

void run_with_parameter(InfGraph &g, const Argument & arg)
{
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << arg.dataset << " k=" << arg.k << " epsilon=" << arg.epsilon <<   " " << arg.model << endl;

    read_data_from_disk();
    Imm::InfluenceMaximize(g, arg);//用于采样，在线算法，和直接从硬盘比较运行速度

    //获取候选子图
    vector<set<int>> candidate;
    candidate = get_candidate(g);
    set<int> ans;
    double max_influence = 0.0;
    //遍历所有候选子图，分别删除影响力最低的点，直至size不超过budget，选择影响力最大的点集作为最终结果
    cout << "1111" << endl;
    for (auto subgraph: candidate) {
        influence_max(subgraph, g, arg);//subgraph在这个函数中被改变
        double tmp_influence = g.Influence_IC_RRSet(subgraph);
        if (tmp_influence > max_influence) {
            max_influence = tmp_influence;
            ans = subgraph;
        }
        cout << "1111" << endl;
    }
    assert(cover(g.query, ans));
//    cout << "query set is covered" << endl;
//    freopen("sample_ans.txt", "w", stdout);
    cout << "size: " << ans.size() << endl;
    cout << "nodes: ";
    for (int x: ans) {
        cout << x << " ";
    }
    cout << endl;
    cout << "influence: " << max_influence << endl;

}

void read_data_from_disk() {
    freopen("pattern.txt", "r", stdin);
//    freopen("small_pattern.txt", "r", stdin);
    int pattern_size;
    cin >> pattern_size;
    degree = vector<int>(node_size);
    hyperGT = vector<vector<int>>(pattern_size);
    hyperG = vector<vector<int>>(node_size);
    for (int i = 0; i < pattern_size; i++) {
        int nn;
        cin >> nn;
        while (nn--) {
            int x;
            cin >> x;
            hyperGT[i].emplace_back(x);
            hyperG[x].emplace_back(i);
            degree[x]++;
        }
    }
}

void influence_max(set<int> &subgraph, InfGraph &graph, const Argument& arg) {
    if (!graph.isSampled) {
        Imm::InfluenceMaximize(graph, arg);
    }
    if (!cover(graph.query, subgraph)) {
        cout << "Query set cannot be covered!" << endl;
        return;
    }
    build_trie_from_disk();
    set<int> non_query;
    set_difference(subgraph.begin(), subgraph.end(), graph.query.begin(), graph.query.end()
    , inserter(non_query, non_query.begin()));
    vector<bool> sample_vis = vector<bool>(graph.hyperGT.size());
    while (subgraph.size() > graph.budget) {
        int node = choose_least_influent_node(non_query);
        subgraph.erase(node);
        non_query.erase(node);
//        brutal_maintain(graph, sample_vis, node);
        trie_maintain(node);
    }
}

void trie_maintain(int node) {
    trie_node* head = tree.linked_list[node];
    while (head != nullptr) {
        delete_node(head);
        head = head->list_next;
    }
}

void build_trie_from_disk() {
    tree.clear();
    tree = trie(node_size);
    for (const auto & i : hyperGT) {
        tree.insert(i);
    }
}

void brutal_maintain(InfGraph &graph, vector<bool> &sample_vis, int node) {
    for (auto v: graph.hyperG[node]) {
        if (sample_vis[v]) {
            continue;
        }
        sample_vis[v] = true;
        for (auto u: graph.hyperGT[v]) {
            degree[u]--;
        }
    }
}

int choose_least_influent_node(const set<int>& non_query) {
    if (non_query.empty()) {
        cout << "Empty Set!" << endl;
        return -1;
    }
    int deg_min = INT_MAX, ret_node = 0;
    for (int x: non_query) {
        if (degree[x] < deg_min) {
            deg_min = degree[x];
            ret_node = x;
        }
    }
    return ret_node;
}

vector<set<int>> get_candidate(InfGraph &graph) {
    vector<set<int>> candidate = vector<set<int>>();
    calc_diff(graph);
    set<int> all_node;
    for (int i = 0; i < graph.n; i++) {
        all_node.emplace(i);
    }
    int degeneracy = 0;
    for (int i = -1; i < max_i; i++) {
        set<int> i_node = ij_core_i_node[i];
        if (intersect(graph.query, i_node)) {
            break;
        }
        set<int> tmp;
        set_difference(all_node.begin(), all_node.end(), i_node.begin(), i_node.end(),
                inserter(tmp, tmp.begin()));
        all_node = tmp;
        for (int j = 0; j <= max_j[i + 1]; j++) {
            set<int> j_node = ij_core_all_node[make_pair(i + 1, j)];
            if (i + j + 1 == degeneracy) {
                candidate.emplace_back(tmp);
            } else if (i + j + 1 > degeneracy) {
                degeneracy = i + j + 1;
                candidate.clear();
                candidate.emplace_back(tmp);
            }
            degeneracy = max(degeneracy, i + j + 1);
            if (intersect(graph.query, j_node)) {
                break;
            }
            set<int> tmp_result;
            set_difference(tmp.begin(), tmp.end(), j_node.begin(), j_node.end(), inserter(tmp_result, tmp_result.begin()));
            tmp = tmp_result;
        }
    }
    return candidate;
}

set<int> influence_max_ij_core(int i, int j, InfGraph graph, Argument arg) {
    set<int> subgraph = get_ij_core(graph, 20, 9);
    if (!cover(graph.query, subgraph)) {
        return subgraph;
    }
    influence_max(subgraph, graph, arg);
    return subgraph;
}

bool cmp(int x, int y) {
    if (degree[x] != degree[y]) {
        return degree[x] < degree[y];
    } else {
        return x < y;
    }
}