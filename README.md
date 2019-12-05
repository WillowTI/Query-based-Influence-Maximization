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

## Other
+ 给定 i 和 j，满足这对 ij-core 有多种方案。现在需要确定给定一个点和某个入度（或者出度），问这个点最多支持多大的出度（入度）。暴力做法会倾向于最大化这个支持的度，但是 hierachy 的做法会倾向于选择最小的度。保证答案正确，就是看上去还有优化的空间。
+ 测试的数据集很巧，i 轴方向上消失的点的顺序正好和给定 i，求 j 方向上的消失的顺序相同，相当于又求了一遍。
+ 关于影响力的计算，给定一个点集，一种计算方法是看在 RRSet 中有多少项是包含其中一个点的，除以 RRSet 的大小，归一化；另一种方法是通过 RRSet 计算有多少点被激活了，除以点的总数，归一化
+ 原作者先做 ij-core，再做 IM，但是 IM 的时候是删除影响力最小的点。我的想法：既然都有子图了，纳入影响力最大的点应该比较好（这个可以做实验验证）
+ 从原图到子图，有很多点删除了，需要做一次映射，这样 FP-Tree 节点的大小也能省下来
+ FP-Tree 要用带链的，就是把节点值相同的用链表或者数组保存下来；每个节点还要保存指向父节点的指针，这样删除的时候会方便很多
+ ij-core 还是要转换为节点最多支持多少度，时间能快一点
+ 构造 FP-Tree 的时候要给每一项都排序，时间开销怕是爆炸
+ 原作者的代码属实不行