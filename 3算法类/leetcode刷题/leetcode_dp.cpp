#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/*
leetcode-70
爬楼梯问题
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
注意：给定 n 是一个正整数。

输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶

思路：
1. 模型：dp[i]表示爬到第i阶有dp[i]种爬法。
2. 达到状态dp[i]有两种途径：
    从第i-1阶爬上来，有dp[i-1]种爬法；
    从第i-2阶爬上来，有dp[i-2]种爬法；
3. 状态转移方程与初始条件
    dp[i] = dp[i-1] + dp[i]
    dp[1] = 1;
    dp[2] = 2;
*/

class Solution70 {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        dp[2] = 2;

        for(int i=3; i<=n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};


/*
leetcode-198
打劫家舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。

输入: [2,7,9,3,1]
输出: 12
解释: 偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。

解题思路：
模型
    dp[i] 选完第i件物品时，偷盗的最大金额；
达到状态dp[i] 有两种路径：
    没有选第i件：最大价值是dp[i-1] 
    选了第i件：这时i-1是不能选的，最大价值是dp[i-2] + nums[i]
状态转移方程：
    最大金额为二者最大值：dp[i] = max(dp[i-1], dp[i-2] + nums[i])
*/

class Solution198 {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        } else if (nums.size() == 1) {
            return nums[0];
        } else if (nums.size() == 2) {
            return max<int>(nums[0], nums[1]);
        }

        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max<int>(nums[0], nums[1]);

        for (int i=2; i<nums.size(); i++) {
            dp[i] = max<int>(dp[i-1], dp[i-2]+nums[i]);
        }
        return dp[nums.size()-1];
    }
};

/*
leetcode-53
最大子段和
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

解题思路：
模型：dp[i]表示前i个元素最大和连续子序列；
达到状态i有两种路径：
    选择了i-1 最大和为 dp[i-1] + nums[i]
    没有选择i-1 最大和为 nums[i]

状态转移方程：
    dp[i] = max(dp[i-1] + nums[i], nums[i])
*/

class Solution53 {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        } else if (nums.size() ==  1) {
            return nums[0];
        }
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int maxd = dp[0];
        for(int i=1; i<nums.size(); i++) {
            dp[i] = max<int>(dp[i-1]+nums[i], nums[i]);
            if (dp[i] > maxd) {
                maxd = dp[i];
            }
        }
        return maxd;
    }
};

/*
leetcode-322
找零钱
给定不同面额的硬币 coins 和一个总金额 amount。
编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
如果没有任何一种硬币组合能组成总金额，返回 -1。

输入: coins = [1, 2, 5], amount = 11
输出: 3 
解释: 11 = 5 + 5 + 1

思路：
此题用暴力枚举+减枝 会超时。
如果所有硬币都是倍数的关系，可以用贪心算法，优先选最大面值。此处也不适用。

动态规划
解题思路：
模型：dp[i] 表示凑够钱数i需要的最少硬币数量。
到达状态dp[i]有三条路径：
dp[i-1] 再加上一个面值1的钱数；  dp[i] = dp[i-1] + 1
dp[i-2] 再加上一个面值2的钱数；  dp[i] = dp[i-2] + 1
dp[i-5] 再加上一个面值5的钱数；  dp[i] = dp[i-5] + 1

其中 dp[i-1] dp[i-2] dp[i-5] 不一定能凑成，不能凑成就是 -1
*/

class Solution322 {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end()); // 升序排序
        vector<int> dp(amount+1, 9999);
        cout << "dp size=" << dp.size() << endl;
        dp[0] = 0;

        for (int i=1; i<=amount;i++) {
            int minCount = 9999;
            int cur_i = i;
            for (int j=0; j < coins.size();j++) {  // 用各种硬币去尝试
                if (i < coins[j]) {
                    break;
                }
                minCount = min<int>(dp[i-coins[j]] + 1, minCount);
            }
            dp[i] = minCount;
        }

        if (9999 == dp[amount]) {
            dp[amount] = -1;
        }
        return dp[amount];
    }
};

/*
leetcode-300
最长上升子序列
给定一个无序的整数数组，找到其中最长上升子序列的长度。

输入: [10,9,2,5,3,7,101,18]
输出: 4 
解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。

思路分析：
暴力枚举（回溯）计算所有的子序列，取符合条件的最大长度。
会超出时间限制。

动态规划：
1. 模型 dp[i] 表示前i个元素中最长升序子序列。
2. 到达状态dp[i],需要从前边找k个位置找到比它小的位置，
    max{ dp[i-k1] + 1 , dp[i-k2] + 1 , dp[i-k3] + 1 ...}
    其中 j = i-k1, i-k2... 表示j比i小的且 dp[j] 小于dp[i] 位置。
3. 最终结果为 dp[i] 的最大值。
*/

class Solution300 {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums.size();
        }
        vector<int> dp(nums.size(), 1);
        int res = 1;
        for(int i=1; i<nums.size(); i++) {
            int maxdpi = 1;
            for(int j=0; j<i; j++) {
                if (nums[j] < nums[i]) {
                    maxdpi = max<int>(maxdpi, dp[j]+1);
                }
            }
            dp[i] = maxdpi;
            if (dp[i] > res) {
                res = dp[i];
            }
        }
        return res;
    }
};


/*
leetcode-64
最小路径和
给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
说明：每次只能向下或者向右移动一步。

输入:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 7
解释: 因为路径 1→3→1→1→1 的总和最小。

思路分析：
dp[i][j] 表示走到坐标[i,j]处的最小路径和。
达到dp[i][j]的上一个状态有两种可能： 
dp[i-1][j]
dp[i][j-1]
状态转移方程：
dp[i][j] = max{ dp[i-1][j] , dp[i][j-1]} + grid[i][j]
*/

class Solution64 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }

        vector<vector<int>> dp;
        for(int i=0; i<grid.size(); i++) {
            dp.push_back(vector<int>(grid[i].size(), 0));
        }

        dp[0][0] = grid[0][0];
        for(int i=1; i<grid.size();i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
            
        }

        for(int i=1; i<grid[0].size(); i++) {
            dp[0][i] = dp[0][i-1] + grid[0][i];
        }

        for(int i=1; i<grid.size(); i++) {
            for(int j=1; j<grid[0].size(); j++) {
                dp[i][j] = min<int>(dp[i-1][j] , dp[i][j-1]) + grid[i][j];
            }
        }

        return dp[grid.size()-1][grid[0].size()-1];
    }
};


int main()
{
    // Solution70 st70;
    // cout << st70.climbStairs(10) << endl;

    // Solution322 st322;
    // vector<int> coins = {2};
    // cout << st322.coinChange(coins, 1) << endl;

    Solution300 st300;
    vector<int> nums = {1,3,6,7,9,4,10,5,6};
    cout << st300.lengthOfLIS(nums) << endl;

    // Solution64 st64;
    // vector<vector<int>> grid = {{1,3,1}, {1,5,1}, {4,2,1}};
    // cout << st64.minPathSum(grid) << endl;

    system("pause");
    return 0;
}