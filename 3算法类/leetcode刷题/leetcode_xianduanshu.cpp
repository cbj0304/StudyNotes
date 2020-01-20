#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator> 

using namespace std;

/*
线段树
区间和的查询
leetcode-307
给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。
update(i, val) 函数可以通过将下标为 i 的数值更新为 val，从而对数列进行修改。


Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8

思路：
涉及树的操作一般都是用递归的思想。
线段树可以看做是一棵满二叉树，满二叉树可以用数组表示，其中
第i个节点的父节点为 2i+1 2i+2
第i个节点的子节点为 (i-1)/2
*/

class NumArray {
public:
    NumArray(vector<int>& nums) {
        if(nums.size()==0) {
            return;
        }
        _nums = nums;
        // 一般线段树数组大小是原数组大小的4倍
        // vector初始化后才可以通过下标访问和赋值，初始化方法如：
        // _tree.assign(nums.size() * 4, 0);   vector<int> tree(100, 0);  for-push_back  
        for(int i=0; i<nums.size()*4;i++) {
            _tree.push_back(0);
        }
        createTree(_nums, 0, _nums.size()-1, _tree, 0);
    }
    
    void update(int i, int val) {
        if (_nums.size() > 0) {
            _update(_nums, 0, _nums.size()-1, _tree, 0, i, val);   
        }
    }
    
    int sumRange(int i, int j) {
        if (_nums.size() == 0) {
            return 0;
        }
        return _sumRange(_nums, 0, _nums.size()-1, _tree, 0, i, j);
    }

    void printTree() {
        copy(_tree.begin(), _tree.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    
private:
    vector<int> _tree;
    vector<int> _nums;
    // 根据数组构建线段树
    void createTree(const vector<int>& nums, int low, int high, vector<int>& tree, int node) {
        if (low == high) {
            tree[node] = nums[low];
            return;
        }
        int mid = (low + high) / 2;
        // cout << "[low, mid, high]= " << low << ", " << mid << ", " << high << endl;
        // !!!  vector的下标操作不添加元素
        // 先通过push_back()函数加入元素后，才能采用下标的方式。
        // 下标方式仅能对确知已存在的元素进行下标操作。
        // tree[node] = accumulate(nums.begin()+low, nums.begin()+high+1, 0);   // 计算累加和,头文件numeric
        int left_node = 2 * node + 1;
        int right_node = 2 * node + 2;
        createTree(nums, low, mid, tree, left_node);
        createTree(nums, mid+1, high, tree, right_node);
        tree[node] = tree[left_node] + tree[right_node];   // 直接左右节点相加即可
    }

    // 递归求和
    int _sumRange(const vector<int>& nums, int low, int high, vector<int>& tree, int node, 
            int i, int j) {
        // 不在范围内
        if (i > high || j < low) {
            return 0;
        }
        // 包含全部节点
        if (i<=low && j>= high) {
            return tree[node];
        }
        // // 找到匹配区间
        // if (i==low && j==high) {
        //     return tree[node];
        // }
        int mid = (low + high) / 2;
        int left_node = 2 * node + 1;
        int right_node = 2 * node + 2;
        if (j <= mid) {
            return _sumRange(nums, low, mid, tree, left_node, i, j);
        } else if (i > mid) {
            return _sumRange(nums, mid+1, high, tree, right_node, i, j);
        } else {
            int left = _sumRange(nums, low, mid, tree, left_node, i, j);
            int right = _sumRange(nums, mid+1, high, tree, right_node, i, j);
            return left + right;
        }   
    }

    // 递归更新
    void _update(const vector<int>& nums, int low, int high, vector<int>& tree, int node,
            int i, int val) {
        
        // 找到更新点
        if (low == high && i == low) {
            tree[node] = val;
            return;
        }

        int mid = (low + high) / 2;
        int left_node = 2 * node + 1;
        int right_node = 2 * node + 2;
        if (i <= mid) {
            _update(nums, low, mid, tree, left_node, i, val);
        } else {
            _update(nums, mid+1, high, tree, right_node, i, val);
        }
        tree[node] = tree[left_node] + tree[right_node];
    }
};

int main()
{
    vector<int> nums = {0, 9, 5, 7, 3};
    NumArray na(nums);
    cout << na.sumRange(4, 4) << endl;
    cout << na.sumRange(2, 4) << endl;
    cout << na.sumRange(3, 3) << endl;
    na.update(0, 1);
    na.printTree();
    cout << na.sumRange(0, 0) << endl;
    
    system("pause");
    return 0;
}