## Suggested Environment

Cygwin + CLion



## Environmental Variable

something like

-dataset nethept/ -k 50 -model IC -epsilon 0.1



## What has been done

+ raw Influence Maximization algorithm using RRSet

   + Input: a directed Graph G

   + Output: a number I denoting the Max Influence of G, the induced subgraph H which has Max Influence

+ ij-core algorithm in directed graph




## What is needed

+ FP-Tree data structure to optimize sampling procedure


## Other
+ 首先，给定 i 和 j，满足这对 ij-core 有多种方案。现在需要确定给定一个点和某个入度（或者出度），问这个点最多支持多大的出度（入度）。暴力做法会倾向于最大化这个支持的度，但是 hierachy 的做法会倾向于选择最小的度。保证答案正确，就是看上去还有优化的空间。
+ 测试的数据集很巧，i 轴方向上消失的点的顺序正好和给定 i，求 j 方向上的消失的顺序相同，相当于又求了一遍。
+ FP-Tree 开源的代码很多，拿来用就完事了。
+ SFMT 是日本某个高校或者实验室研究出来的伪随机数生成器，既然决定用伪随机数了，为什么不直接用自带的，不知道。 