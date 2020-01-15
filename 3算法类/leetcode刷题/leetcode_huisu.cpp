#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <set>

using namespace std;

/*
回溯法
类似于：
暴力枚举 + 减枝
递归法 + 限制条件
深度优先搜索树空间

排列组合数、求子集、求组合和问题。
选与不选的问题，暴力枚举一棵满二叉树。
https://blog.csdn.net/gaorutao0923/article/details/97132767

回溯法的概念：
回溯法也称为试探法，它并不考虑问题规模的大小，而是从问题的最明显的最小规模开始逐步求解出可能的答案，迭代地逼近最终问题的解。
这种迭代类似于穷举并且是试探性的，因为当目前的可能答案被测试出不可能可以获得最终解时，则撤销当前的这一步求解过程，回溯到上一步寻找其他求解路径。
（穷举法要将一个解的各个部分全部生成后，才检查是否满足条件）。
为了能够撤销当前的求解过程，必须保存上一步以来的求解路径，这一点相当重要。

回溯和递归：
回溯是一种算法思想，它的求解过程实质上是先序遍历一棵“状态树”的过程。因此可以用递归这种算法结构实现。

回溯和穷举：
回溯 = 暴力枚举 + 减枝。
*/

/*
leetcode-17
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

思路：
递归+回溯
深度搜索树DFS

此题也可以用正向迭代的方式实现，两重for循环。


回溯是一种思想，求解本质是先序遍历一棵树（DFS），求解树的有效路径问题。
所有可以画成一棵状态树，可通过暴力枚举实现的题目，可以用此框架。
全排列问题：
每次取出一个未访问过的元素放入path，递归取下一个元素，直到处理到最后一个元素为止。
求子集的问题：
每个元素都有取或者不取两种可能。
！！！！！ 暴力枚举一般都需要恢复现场，进行下一轮的递归。


leetcode-46
给定一个没有重复数字的序列，求所有的全排列。
输入: [1,2,3]
输出: [ [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1] ]


leetcode-47
给定一个可包含重复数字的序列，求所有的全排列。
说明：解集不能包含重复的子集。
输入: [1,1,2]
输出: [ [1,1,2], [1,2,1], [2,1,1] ]

leetcode-78
给定一个没有重复数字的序列，求所有的子集。
说明：解集不能包含重复的子集。
输入: nums = [1,2,3]
输出: [ [3], [1], [2], [1,2,3], [1,3], [2,3], [1,2], [] ]

leetcode-39
给定一个无重复元素的数组 candidates 和一个目标数 target，
找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。
说明：解集不能包含重复的子集。

leetcode-40
给定一个数组 candidates 和一个目标数 target ，
找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。

leetcode-17
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

leetcode-22
生成括号：
n 代表括号的对数, 求所有有效的括号组合。
例如，给出 n = 3，生成结果为：
[ "((()))", "(()())", "(())()", "()(())", "()()()" ]
*/
class Solution17 {
public:
    Solution17() {
        _map = {
            {'2', {"a", "b", "c"}},
            {'3', {"d", "e", "f"}},
            {'4', {"g", "h", "i"}},
            {'5', {"j", "k", "l"}},
            {'6', {"m", "n", "o"}},
            {'7', {"p", "q", "r", "s"}},
            {'8', {"t", "u", "v"}},
            {'9', {"w", "x", "y", "z"}}
        };
    }
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) {
            return _res;
        }

        string tmpstr("");
        findCombination(digits, 0, tmpstr);
        return _res;
    }
private:
    // 数字字符对应的字母集合
    map<char, vector<string>> _map;
    vector<string> _res;
    void findCombination(const string & digits, int index, string & curStr) {
        cout << "index=" << index << " str=" << curStr << endl; 
        if (index == digits.size()) {
            _res.push_back(curStr);
            cout << "return curStr=" << curStr << endl;
            return;
        }

        char ch = digits[index];
        if (_map.find(ch) != _map.end()) {
            vector<string> letters = _map[ch];
            for(auto it = letters.begin(); it != letters.end(); it++) {
                cout << "index=" << index << " letters=" << *it << endl;
                string s = curStr + *it;
                findCombination(digits, index+1, s);
            }
        }
    }
};

/*
leetcode-39
组合总和
给定一个无重复元素的数组 candidates 和一个目标数 target，
找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。

说明：
    所有数字（包括 target）都是正整数。
    解集不能包含重复的组合。 

输入: candidates = [2,3,6,7], target = 7,
所求解集为: [ [7], [2,2,3] ]
*/
class Solution39 {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        if (candidates.size() <= 0) {
            return _res;
        }
        vector<int> path;
        int sum = 0;
        findcombination(candidates, target, 0, path, sum);
        return _res;
    }
private:
    vector<vector<int>> _res;
    void findcombination(const vector<int> & candidates, int target, 
            int start, vector<int> & curPath, int curSum) {
        if (curSum > target) {
            return;
        } else if (curSum == target) {
            _res.push_back(curPath);
            return;   // 当前这条路径结束
        }

        for(int i=start; i<candidates.size(); i++) {
            curPath.push_back(candidates[i]);
            curSum += candidates[i];
            findcombination(candidates, target, i, curPath, curSum);
            curPath.pop_back();
            curSum -= candidates[i];
        }
    }
};

/*
leetcode-40
组合数
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。

说明：
    所有数字（包括目标数）都是正整数。
    解集不能包含重复的组合。 
输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为: [ [1, 7], [1, 2, 5], [2, 6], [1, 1, 6] ]
*/

class Solution40 {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        if (candidates.size() == 0) {
            return _res;
        }
        // 排序是为了把相同的元素放在一起，用于后边减枝去重
        sort(candidates.begin(), candidates.end());

        vector<int> path;
        int sum = 0;
        findCombination(candidates, target, 0, path, sum);
        return _res;
    }
private:
    vector<vector<int>> _res;
    void findCombination(const vector<int>& candidate, int target, int start, 
            vector<int> & curpath, int & curSum) {
        
        if (curSum > target) {
            return;
        } else if (curSum == target) {
            _res.push_back(curpath);
            return;
        } else {
            // i每次从index开始，不用定义visit数组了
            for (int i=start;i<candidate.size(); i++) {

                // 减枝
                if (curSum + candidate[i] > target) {
                    break;
                }
                // 此步是为了去重，相同值保证先后顺序
                if (i>start && candidate[i] == candidate[i-1]) {
                    continue;
                }
                
                curpath.push_back(candidate[i]);
                curSum += candidate[i];
                findCombination(candidate, target, i+1, curpath, curSum);
                // 恢复现场
                curpath.pop_back();
                curSum -= candidate[i];
            }
        }
    }
};

/*
leetcode-46
全排列
给定一个没有重复数字的序列，返回其所有可能的全排列。
输入: [1,2,3]
输出: [ [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1] ]
*/

class Solution46 {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.size() == 0) {
            return _res;
        }

        vector<bool> visited;
        visited.reserve(nums.size());
        visited.assign(nums.size(), false);

        vector<int> path;
        findCombination(nums, 0, path, visited);
        return _res;
    }
private:
    vector<vector<int>> _res;

    void findCombination(vector<int>& nums, int index, 
            vector<int>& curPath, vector<bool> & visited) {
        if (index == nums.size()) {
            _res.push_back(curPath);
            return;    // 选够所有的元素，此条路径退出
        }

        for(int i=0; i<nums.size(); i++) {
            if (visited[i] == 1) {
                continue;
            }
            // cout << "use=" << nums[i] << endl;
            curPath.push_back(nums[i]);
            visited[i] = true;
            findCombination(nums, index+1, curPath, visited);
            curPath.pop_back();
            visited[i] = false;    // 恢复现场
        }
    } 
};

/*
leetcode-47
全排列II
给定一个可包含重复数字的序列，返回所有不重复的全排列。

输入: [1,1,2]
输出: [ [1,1,2], [1,2,1], [2,1,1] ]
*/

class Solution47 {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if (nums.size() == 0) {
            return _res;
        }

        // 为了去重，把所有的数放在一起
        sort(nums.begin(), nums.end());

        vector<int> path;
        vector<bool> visited(nums.size(), false);
        findCombination(nums, 0, path, visited);
        return _res;
    }

private:
    vector<vector<int>> _res;
    void findCombination(const vector<int> & nums, int index, 
        vector<int>& path, vector<bool>& visited) {
        
        if (index == nums.size()) {
            _res.push_back(path);
            return;
        }

        for(int i=0; i<nums.size(); i++) {
            if (visited[i] == true) continue;

            // 去重，人为规定相同数字的相对顺序不变
            if (i > 0 && nums[i] == nums[i-1] && visited[i-1] == false) {
                continue;
            }
            path.push_back(nums[i]);
            visited[i] = true;
            findCombination(nums, index+1, path, visited);
            path.pop_back();
            visited[i] = false;
        }
    }
};

/*
leetcode-78
计算子集
给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。

输入: nums = [1,2,3]
输出: [ [3], [1], [2], [1,2,3], [1,3], [2,3], [1,2], [] ]

思路：
1. 位运算法
2. 回溯法
*/

class Solution78 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        if (nums.size() == 0) {
            return _res;
        }

        vector<int> path;
        findCombination(nums, 0, path);
        return _res;
    }

private:
    vector<vector<int>> _res;
    void findCombination(vector<int>& nums, int index, vector<int> & curpath) {
        if (index == nums.size()) {
            _res.push_back(curpath);
            return;
        }

        curpath.push_back(nums[index]);   // 选index
        findCombination(nums, index+1, curpath);
        curpath.pop_back();              // 不选index
        findCombination(nums, index+1, curpath);
    }
};

/*
leetcode-22
生成括号：
给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
例如，给出 n = 3，生成结果为：
[ "((()))", "(()())", "(())()", "()(())", "()()()" ]
*/

class Solution22 {
public:
    vector<string> generateParenthesis(int n) {
        if (n==0) {
            return _res;
        }

        string path("");
        findCombination(n, 0, 0, path);
        return _res;
    }
private:
    vector<string> _res;
    void findCombination(const int n, int left_cnt, int right_cnt, string &curpath) {
        if (left_cnt > n  || right_cnt > n) {
            return;
        }
        if (left_cnt == n && right_cnt == n) {
            _res.push_back(curpath);
            return;
        }
        if (left_cnt > right_cnt) {
            curpath = curpath + ")";
            findCombination(n, left_cnt, right_cnt+1, curpath);
            curpath.pop_back();
        }
        curpath = curpath + "(";
        findCombination(n, left_cnt+1, right_cnt, curpath);
        curpath.pop_back();
    }
};

int main()
{
    // Solution17 st17;
    // string s = "234";
    // vector<string> v = st17.letterCombinations(s);
    // cout << "==============output" << endl;
    // copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));

    // Solution39 st39;
    // vector<vector<int>> v;
    // vector<int> candidate = {2,3,5};
    // int target = 8;
    // v = st39.combinationSum(candidate, target);

    // for (auto it = v.begin(); it!=v.end(); it++) {
    //     cout << endl;
    //     copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
    // }

    // Solution46 st46;
    // vector<int> nums = {1, 2, 3};
    // vector<vector<int>> v = st46.permute(nums);

    // for (auto it = v.begin(); it!=v.end(); it++) {
    //     cout << endl;
    //     copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
    // } 

    // Solution40 st40;
    // vector<int> candidate = {10,1,2,7,6,1,5};
    // int target = 8;
    // vector<vector<int>> v  = st40.combinationSum2(candidate, target);

    // for (auto it = v.begin(); it!=v.end(); it++) {
    //     cout << endl;
    //     copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
    // }

    // Solution78 st78;
    // vector<int> nums = {1,2,3};
    // vector<vector<int>> v = st78.subsets(nums);

    // for (auto it = v.begin(); it!=v.end(); it++) {
    //     cout << endl;
    //     copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
    // }

    // Solution47 st47;
    // vector<int> nums = {1,1,2};
    // vector<vector<int>> v = st47.permuteUnique(nums);

    // for (auto it = v.begin(); it!=v.end(); it++) {
    //     cout << endl;
    //     copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
    // }

    Solution22 st22;
    vector<string> v = st22.generateParenthesis(3);
    copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));

    system("pause");
    return 0;
}