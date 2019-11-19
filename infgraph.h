#ifndef SFMT_INFGRAPH_H
#define SFMT_INFGRAPH_H

#include "graph.h"
#include "Argument.h"

class InfGraph: public Graph
{
private:
    vector<bool> visit;
    vector<int> visit_mark;
public:
    vector<vector<int>> hyperG;//某个点在哪些次取样出现
    vector<vector<int>> hyperGT;//第i次取样取到了哪些点，包括起点
    deque<int> q;//用于BFS采样
    sfmt_t sfmtSeed;
    vector<set<int>> influence;
    set<int> seedSet;//保存最终结果，多次用到

    InfGraph(string folder, string graph_file): Graph(folder, graph_file)
    {
        sfmt_init_gen_rand(&sfmtSeed , 95082);
        init_hyper_graph();
        visit = vector<bool> (n);
        visit_mark = vector<int> (n);
        influence = vector<set<int>>(n);
    }

    void init_hyper_graph(){
        hyperG = vector<vector<int>>(n);
        hyperGT.clear();
    }

    void build_hyper_graph_r(int64 R, const Argument & arg)
    {
        if( R > INT_MAX ){
            cout<<"Error:R too large"<<endl;
            exit(1);
        }
        //INFO("build_hyper_graph_r", R);

        int prevSize = hyperGT.size();
        while ((int)hyperGT.size() <= R)
            hyperGT.push_back( vector<int>() );

        vector<int> random_number;
        for (int i = 0; i < R; i++)
        {
            random_number.push_back(  sfmt_genrand_uint32(&sfmtSeed) % n);
        }

        //trying BFS start from same node


        for (int i = prevSize; i < R; i++)
        {
            BuildHypergraphNode(random_number[i], i );
        }


        int totAddedElement = 0;
        for (int i = prevSize; i < R; i++)
        {
            for (int t : hyperGT[i])
            {
                hyperG[t].push_back(i);
                //hyperG.addElement(t, i);
                totAddedElement++;
            }
        }
    }

    /*
     * BFS starting from one node
     */

    int BuildHypergraphNode(int uStart, int hyperiiid)
    {
        int n_visit_edge = 1;
        ASSERT((int)hyperGT.size() > hyperiiid);
        hyperGT[hyperiiid].push_back(uStart);
        int n_visit_mark = 0;
        q.clear();
        q.push_back(uStart);
        ASSERT(n_visit_mark < n);
        visit_mark[n_visit_mark++] = uStart;
        visit[uStart] = true;
        while (!q.empty())
        {
            int expand = q.front();
            q.pop_front();
            if (influModel == IC)
            {
                int i = expand;
                for (int j = 0; j < (int)gT[i].size(); j++)
                {
                    //int u=expand;
                    int v = gT[i][j];
                    n_visit_edge++;
                    double randDouble = sfmt_genrand_real1(&sfmtSeed);
                    if (randDouble > probT[i][j])
                        continue;
                    if (visit[v])
                        continue;
                    if (!visit[v])
                    {
                        ASSERT(n_visit_mark < n);
                        visit_mark[n_visit_mark++] = v;
                        visit[v] = true;
                        influence[v].emplace(uStart);
                    }
                    q.push_back(v);
                    ASSERT((int)hyperGT.size() > hyperiiid);
                    hyperGT[hyperiiid].push_back(v);
                }
            }
            else if (influModel == LT)
            {
                if (gT[expand].size() == 0)
                    continue;
                ASSERT(gT[expand].size() > 0);
                n_visit_edge += gT[expand].size();
                double randDouble = sfmt_genrand_real1(&sfmtSeed);
                for (int i = 0; i < (int)gT[expand].size(); i++)
                {
                    ASSERT( i < (int)probT[expand].size());
                    randDouble -= probT[expand][i];
                    if (randDouble > 0)
                        continue;
                    //int u=expand;
                    int v = gT[expand][i];

                    if (visit[v])
                        break;
                    if (!visit[v])
                    {
                        visit_mark[n_visit_mark++] = v;
                        visit[v] = true;
                    }
                    q.push_back(v);
                    ASSERT((int)hyperGT.size() > hyperiiid);
                    hyperGT[hyperiiid].push_back(v);
                    break;
                }
            }
            else
                ASSERT(false);
        }
        for (int i = 0; i < n_visit_mark; i++)
            visit[visit_mark[i]] = false;
        return n_visit_edge;
    }


    //return the number of edges visited
    //选出前k个出现次数最多的点
    //统计各个点在采样中出现的次数，保存在degree中
    //每次选出出现次数最大的点，在采样集中把这个点出现的那一条采样删去
    //在degree中把一同出现的点次数减一
    void build_seedset(int k)
    {
        Counter cnt(1);
        vector< int > degree;
        vector< int> visit_local(hyperGT.size());

        seedSet.clear();
        for (int i = 0; i < n; i++)
        {
            degree.push_back( hyperG[i].size() );
        }
        ASSERT(k > 0);
        ASSERT(k < (int)degree.size());
        for (int i = 0; i < k; i++)
        {
            auto t = max_element(degree.begin(), degree.end());
            int id = t - degree.begin();
            seedSet.insert(id);
            degree[id] = 0;
            for (int t : hyperG[id])
            {
                if (!visit_local[t])
                {
                    visit_local[t] = true;
                    for (int node : hyperGT[t])
                    {
                        degree[node]--;
                    }
                }
            }
        }
        TRACE(seedSet);
    }
    //原图节点总个数 * 最终结果的点在多少个采样中出现 / 总采样个数
    double InfluenceHyperGraph()
    {
        set<int> s;
        TRACE(seedSet);
        for (auto t : seedSet)
        {
            for (auto tt : hyperG[t])
            {
                s.insert(tt);
            }
        }
        double inf = (double)n * s.size() / hyperGT.size();
        return inf;
    }

    //计算 seedSet 的影响力
    //根据采样的结果，seedSet 中所有点能影响到的点的数量
    int Influence_IC() {
        if (seedSet.empty()) {
            return 0;
        }
        set<int> influenced;
        for (auto & x: seedSet) {
            set_union(influenced.begin(), influenced.end(), influence[x].begin(),
                    influence[x].end(), inserter(influenced, influenced.begin()));
        }
        return influenced.size();
    }

};




#endif
