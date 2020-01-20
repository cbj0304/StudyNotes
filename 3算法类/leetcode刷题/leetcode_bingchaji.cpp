#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

using namespace std;

/*
并查集：
B站: https://www.bilibili.com/video/av12408792
作用检查图上是否有环。

什么是并查集？
用一维数组保存当前节点的父节点的树结构。
并查集是用数组实现将点编为一个个集合的简单树形结构。

功能：
1. 合并集合？
2. 查找某个点所在集合所拥有点的数量？
3. 询问某两个点是否处于同一个集合等操作？
扩展：查找连通图的数量。

实现：
定义并查集数组为parent, 这些点被分成了若干组，每个组只有一个根节点，
每个parent[根节点编号]的值永远为负数，负数的绝对值记录当前组内点数。
每个parent[非根节点编号]的值要设置为一个同组其它点的编号，并且保证每个点都能顺着记录下的那个同组其它编号的值找到组长。
*/

/*
简单并查集模板
查找两个点是否在同一个并查集；Find
合并两个点所在的并查集；Union
查找一个并查集中点的数量；Count
*/

class BCJ {
public:
    BCJ() {
        _parent.assign(10000, -1);   // 初始化状态是一堆孤立的点，每个集合节点数量为1
    }

    // 查找两个点是否属于同一个集合
    // 优化：遍历过程中使用路径压缩算法（父节点更新为根节点），使树更加扁平，优化查询效率。
    bool Find(int x, int y) {
        int px = FindParent(x);
        int py = FindParent(y);
        return px == py;
    }

    // 合并两个并查集
    // 优化：将size小的数合并到size大的树上，使树更加平衡，优化查询效率。
    void Union(int x, int y) {
        int px = FindParent(x);
        int py = FindParent(y);
        // y所在集合的根节点指向x所在集合的根节点，并更新集合中节点数量
        _parent[px] += _parent[py];    // 两个都是负数，可以相加
        _parent[py] = px;
    }

    // x所在并查集的节点个数
    int Count(int x) {
        return -_parent[FindParent(x)];
    }

private:
    vector<int> _parent;
    int FindParent(int x) {
        if (_parent[x] < 0) {
            return x;
        }
        return FindParent(_parent[x]);
    }
};


/*
leetcode-547
班上有 N 名学生。其中有些人是朋友，有些则不是。他们的友谊具有是传递性。
如果已知 A 是 B 的朋友，B 是 C 的朋友，那么我们可以认为 A 也是 C 的朋友。
所谓的朋友圈，是指所有朋友的集合。
给定一个 N * N 的矩阵 M，表示班级中学生之间的朋友关系。
如果M[i][j] = 1，表示已知第 i 个和 j 个学生互为朋友关系，否则为不知道。
你必须输出所有学生中的已知的朋友圈总数。

输入: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
输出: 2 
说明：已知学生0和学生1互为朋友，他们在一个朋友圈。
第2个学生自己在一个朋友圈。所以返回2。


思路：
传入代表朋友友谊的二维数组M，设置并查集大小；
对于任意两个人ij，如果他们存在友谊（M[i][j]=1），则将他们合并，返回并查集的个数。
*/

class Solution547 {
public:
    int findCircleNum(vector<vector<int>>& M) {
        if (M.size() <=0 || M[0].size() <=0) {
            return 0;
        }
        int row = M.size();
        int col = M[0].size();
        assert(row == col);      // 一定是方阵
        _parent.assign(row, -1);

        // 合并
        for(int i = 0; i < row; i++) {
            for (int j = i+1; j < row; j++) {
                if (M[i][j] == 1) {  // 关系是相互的，算一半就行了
                    Union(i, j);
                }
            }
        }

        // 查找有多少个并差集
        int _count = 0;
        for(int i=0; i<row; i++) {
            if (_parent[i] < 0) {
                _count++;
            }
        }
        return _count;

    }
private:
    vector<int> _parent;
    // 返回x的父节点
    int FindParent(int x) {
        if (_parent[x] < 0) {
            return x;
        }
        return FindParent(_parent[x]);
    }
    // 判断x y是否属于一组
    int Find(int x, int y) {
        int px = FindParent(x);
        int py = FindParent(y);

        // 优化效率,使树变得扁平
        // _parent[x] = px;
        // _parent[y] = py;

        return px == py;
    }
    // 合并两个并查集
    void Union(int x, int y) {
        if (!Find(x, y)) {
            int px = FindParent(x); 
            int py = FindParent(y);

            // 优化效率： 小树合到大树上去
            if (abs(_parent[px]) > abs(_parent[py])) {
                _parent[px] += _parent[py];
                _parent[py] = px;
            } else {
                _parent[py] += _parent[px];
                _parent[px] = py;
            }
        }
    }
};

int main()
{
    // BCJ bcj;
    // bcj.Union(1, 2);
    // bcj.Union(4, 5);
    // bcj.Union(1, 5);
    // //           0   1   2   3   4  5
    // // vector   -1  -2   1  -1  -2  4
    // // vector   -1  -4   1  -1   1  4
    // cout << bcj.Count(3) << endl;
    // cout << bcj.Count(2) << endl;

    // cout << bcj.Find(1, 3) << endl;
    // cout << bcj.Find(2, 4) << endl;

    Solution547 st547;
    vector<vector<int>> M = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1} 
    };
    cout << st547.findCircleNum(M) << endl;


    system("pause");
    return 0;
}