#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <set>

using namespace std;

/*
递归、回溯、分治：
求子集（回溯法、位运算法）
组合数之和（回溯法、减枝）
生成括号（递归设计）
逆序数（二叉搜索树、分治法与归并排序）
*/

/*
leetcode-78
求子集
给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
输入: nums = [1,2,3]
输出:
[ [3], [1], [2], [1,2,3], [1,3], [2,3], [1,2], [] ]

思路：
方法1：使用位运算法实现。
方法2：回溯试探法。

*/

class Solution78 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int count = nums.size();
        vector<vector<int>> res;
        
        for(size_t i=0; i<=pow(2, count)-1;i++) {
            vector<int> tmp;
            for(int j=0; j<count;j++) {
                if (1<<j & i) {
                    tmp.push_back(nums[j]);
                }
            }
            res.push_back(tmp);
        }
        return res;
    }

};

/*
leetcode-90
求子集
给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。

输入: [1,2,2]
输出:
[ [2], [1], [1,2,2], [2,2], [1,2], [] ]
*/

class Solution90 {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int count = nums.size();
        vector<vector<int>> res;
        set<multiset<int>> rmdup;  // 如果用set<vector<int>>去重，需要先对vector排序
        
        for(size_t i=0; i<=pow(2, count)-1;i++) {
            vector<int> tmp;
            multiset<int> settmp;
            for(int j=0; j<count;j++) {
                if (1<<j & i) {
                    tmp.push_back(nums[j]);
                    settmp.insert(nums[j]);
                }
            }
            if (rmdup.find(settmp) != rmdup.end()) {
                copy(settmp.begin(), settmp.end(), ostream_iterator<int>(cout, " "));
                cout << "dup---" << endl;
                continue;
            }
            res.push_back(tmp);
            rmdup.insert(settmp);           
        }
        return res;
    }
};


/*
回溯类型整理继续看代码 leetcide_huisu.cpp 。。。
*/

int main()
{
    // Solution78 st78;
    // vector<int> nums = {1,2,3};
    // vector<vector<int>> v = st78.subsets(nums);
    // for(auto it=v.begin(); it!=v.end();it++) {
    //     copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
    //     cout << endl;
    // }

    Solution90 st90;
    vector<int> nums = {1,2,2};
    vector<vector<int>> v = st90.subsetsWithDup(nums);
    for(auto it=v.begin(); it!=v.end();it++) {
        copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }

    system("pause");
    return 0;
}