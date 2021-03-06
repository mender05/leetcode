# 60 - Permutation Sequence

##问题描述
给定一个数字 0 < n < 10，求[1, n]这n个数字的排列中第k大的那个排列。
例如，n=3，k=2，总共的排列是：
* 123
* 132
* 213
* 231
* 312
* 321
第2大的是132.

#算法思想
利用分组的思想来做。例如n=6，k=16。

首先，由于我们只需要知道第16个排列，最多只用4位数就可以得到大于16个排列（3!<16<4!）。因此，第16个排列看起来应该是：`1,2,x,x,x,x`。

问题转化：从123456的排列中，求出第16大的排列 -> 从3456的排列中，选出第16大的排列。

我们对3456形成的24个排列进行分组，第一组以3开头，第二组以4开头，第三组以5开头，第四组以6开头：

| 第一组 | 第二组 | 第三组 | 第四组 |
|--------|--------|--------|--------|
| 3456   | 4356   | 5346   | ...    | 
| 3465   | 4365   | 5364   | ...    |
| 3546   | 4536   | 5436   | ...    |
| 3564   | 4563   | 5463   | ...    |
| 3645   | 4635   | 5634   | ...    |
| 3654   | 4653   | 5643   | ...    |

每一组组内是有序的，每组的排列数是3!，所以第16大的排列应该位于**第3组**，即16/(3!)取上界。组内的**偏移量是4=16%(3!)**。

所以，我们现在可以确定的是`1,2,x,x,x,x`中的第一个'x'应该是`3,4,5,6`中的**第3个数字**。

因此，问题转化为求'3,4,6'第排列里，**第4大**的排列。解法与上面完全一样，除法求分组，取mod求偏移。
