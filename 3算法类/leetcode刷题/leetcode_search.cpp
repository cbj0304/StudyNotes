#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

/*
搜索问题：
1. 图 深度优先搜索 DFS
2. 图 广度优先搜索 BFS
3. 回溯法（暴力搜索 + 减枝）
*/

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

思路：
方向数组，代表四个新的位置（上下左右）。

DFS

BFS : 用队列实现。
1. 设置mark矩阵（和grid结构相同），用于标记哪个位置被访问过。
2. 遍历地图上所有点，如果该点是陆地且未被访问过，则用BFS遍历，并标记mark矩阵，每次遍历完陆地数量+1。
每轮BFS实现：
选一个未被访问过的陆地坐标(x,y)放入队列；
只要队列非空，执行以下操作：
从队列中取出队头元素并标记mark矩阵为被访问过，
同时探索其四个方向，如果是陆地且未被访问则放入队列。
*/

class Solution200 {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }
        // 初始化mark矩阵
        for(int i=0; i<grid.size(); i++) {
            _mark.push_back(vector<char>(grid[i].size(), '0'));
        }

        _island_num = 0;
        int index_x=-1, index_y=-1;   
        bool findflag = false;
        // 查找探索的起点
        for(int i=0; i<grid.size(); i++) {
            for(int j=0;j<grid[i].size(); j++) {
                if (grid[i][j] == '1' && _mark[i][j] == '0') {
                    BFS(grid, i, j);
                    _island_num++;
                }
            }            
        }
        
        return _island_num;
    }
private:
    vector<vector<char>> _mark;
    int _island_num;
    void BFS(const vector<vector<char>>& grid, int x, int y) {

        cout << "=====" << x << ", " << y << endl;

        // 方向坐标
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, -1, 1}; 

        queue<pair<int, int>> q;
        q.push(make_pair(x, y));
        cout << "push queue -> " << x << ", " << y << endl; 

        while(!q.empty()) {
            pair<int, int> pos = q.front();
            _mark[pos.first][pos.second] = '1';
            q.pop();
            for(int i=0; i<4; i++) {
                int new_x = pos.first + dx[i];
                int new_y = pos.second + dy[i];
                cout << "(new) x y -> " << new_x << ", " << new_x << endl; 
                if (new_x >= 0 && new_y >=0 
                    && new_x < grid.size()
                    && new_y < grid[new_x].size()
                    && grid[new_x][new_y] == '1'
                    && _mark[new_x][new_y] == '0') {
                        q.push(make_pair(new_x, new_y));
                        cout << "(new) push queue -> " << new_x << ", " << new_x << endl; 
                    }
            }

        }
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

抽象：
把一堆数字放入四个位置，每个位置的和为固定值target。
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
        // 把nums.size() 个数字尝试往四个盒子中放置
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

/*
leetcode79
给定一个二维网格和一个单词，找出该单词是否存在于网格中。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，
其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

给定 word = "ABCCED", 返回 true.
给定 word = "SEE", 返回 true.
给定 word = "ABCB", 返回 false.

思路：
深度优先搜索DFS
方向向量
*/

class solution79 {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (word.size() == 0 || board.size() == 0 || board[0].size() == 0) {
            return false;
        }

        // 初始化mark数组，标记哪个位置被访问过
        for(int i=0; i<board.size(); i++) {
            _mark.push_back(vector<bool>(board[i].size(), false));
        }

        // 从第一个字母开始深度优先遍历，查找整个单词
        _find = false;
        for(int i=0; i<board.size(); i++) {
            for(int j=0; j<board[i].size(); j++) {
                if (board[i][j] == word[0]) {
                    DFS(board, i, j, word, 1);
                }
            }
        }

        return _find;
    }
private:
    vector<vector<bool>> _mark;
    bool _find;
    // 以(x,y)为起点，深度优先搜索单词的每个字母
    void DFS(const vector<vector<char>> & board, int x, int y, const string word, int index) {

        if (index == word.length() || _find == true) {
            _find = true;
            return;
        }

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        for(int i=0; i<4;i++) {

            int new_x = x + dx[i];
            int new_y = y + dy[i];

            if (new_x>=0 && new_x < board.size()
                && new_y >= 0 && new_y < board[new_x].size()
                && _mark[new_x][new_y] == false
                && index < word.length()
                && board[new_x][new_y] == word[index]) {
                    _mark[new_x][new_y] = true;
                    DFS(board, new_x, new_y, word, index+1);
                    _mark[new_x][new_y] = false;  // 恢复现场
                }
        }
    }
};

int main()
{
    // Solution200 st200;
    // vector<vector<char>> grid = {
    //     {'1', '1', '1', '1', '0'}, 
    //     {'1', '1', '0', '1', '0'}, 
    //     {'1', '1', '0', '0', '0'},
    //     {'0', '0', '0', '0', '0'}};

    // cout << st200.numIslands(grid) << endl;

    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    solution79 st79;
    cout << "ABCCED -> " << st79.exist(board, "ABCCED") << endl;
    cout << "SEE -> " << st79.exist(board, "SEE") << endl;
    cout << "ABCB -> " << st79.exist(board, "ABCB") << endl;

    system("pause");
    return 0;
}