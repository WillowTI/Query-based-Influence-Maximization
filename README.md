## Suggested Environment

Cygwin + CLion



## Environmental Variable

something like

-dataset nethept/ -k 50 -model IC -epsilon 0.1



## What has been done

+ raw Influence Maximization algorithm using RRSet

   + Input: a directed Graph G

   + Output: a number I denoting the Max Influence of G, the induced subgraph H which has Max Influence

+ O(m) k-core algorithm in undirected graph




## What is needed

+ FP-Tree data structure to optimize sampling procedure

+ ij-core in directed graph

  

## Other

diff_i 记录从 i 到 i + 1 消失的点

ij-core 从 j 方向上的增长写炸了
原本想的是 j 方向只考虑出度的变化，那么只要维护出度就可以了，就像 i 方向只要考虑入度就可以了
但是之前写的 i 方向是在 j = 0 的情况下，出度至少为 0 这是废话，所以铁定不用考虑
说回这个问题，有一种情况是在删除某个点（记为 n1）的时候，此时这个点支持(i, j)的core
有一条边（n1->n2），那么 n2 的入度要减一
可能这一减，n2 的入度就不够满足至少为 i 这个条件，那么就能得出 n2 只能支持到(i, j)的结论吗？
不行，因为虽然说后面的点支持的(i, j)总体会变小，跟其当前的(i, j)值相比
但不能说它就这样了，这时的 j 值它肯定是支持的，但不一定是最大的
Solution：
当前想到的办法是遍历当前要删除的具有相同 j 的点，枚举，递归，最后看每个点最大支持的度怎么样
换句话说就是尝试不同的删除路线，挑一个最好的结果
保证答案是正确的
但是递归的复杂度太高了，甚至不如暴力解
啧，难搞
