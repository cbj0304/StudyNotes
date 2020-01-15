#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

/*
leetcode-200
搜索独立小岛
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。
一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。
你可以假设网格的四个边均被水包围。

输入:
11000
11000
00100
00011

输出: 3
*/

class Solution200 {
public:
    int numIslands(vector<vector<char>>& grid) {
        
    }
};


/*
leetcode-473
火柴拼正方形
你知道小女孩有多少根火柴，请找出一种能使用所有火柴拼成一个正方形的方法。
不能折断火柴，可以把火柴连接起来，并且每根火柴都要用到。
输入为小女孩拥有火柴的数目，每根火柴用其长度表示。输出即为是否能用所有的火柴拼成正方形。

输入: [1,1,2,2,2]
输出: true
解释: 能拼成一个边长为2的正方形，每边两根火柴。
*/

class Solution473 {
public:
    bool makesquare(vector<int>& nums) {
        int sum = 0;
        for (auto it=nums.begin(); it != nums.end(); it++) {
            sum += *it;
        }
        if (sum == 0 || sum % 4 != 0) {
            return false;
        }
        int single = sum / 4;
        // 遍历可能的组合数
        sort(nums.begin(), nums.end(), greater<int>());   // 从大到小排序
        for (int i=0; i<nums.size(); i++) {
            cout << nums[i] << endl;
        }
        // 回溯：放不放的问题
        int bukets[4] = {};
        return generate1(0, nums, single, bukets) ;
        
    }
private:
    // 测试i在buket里放不放
    bool generate1(int i, vector<int> &nums, int target, int bukets[]) {
        if (i >= nums.size()) {
            return (bukets[0] == target && bukets[1] == target 
                    && bukets[2] == target && bukets[3] == target);
        }

        // 尝试四个桶要不要放i
        for (int j=0; j<4;j++) {
            if (bukets[j] + nums[i] > target) {
                continue; // i不能放
            }
            bukets[j] += nums[i];
            if (generate1(i+1, nums, target, bukets)) {
                return true;
            }
            bukets[j] -= nums[i];
        }
        return false;
    }
};

int main()
{
    system("pause");
    return 0;
}