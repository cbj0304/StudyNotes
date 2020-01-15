#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>

using namespace std;

/*
贪心算法：
分糖果问题
摇摆序列
移除k个数字
跳跃游戏
射击气球
最优加油方法
*/

/*
leetcode-455
分发饼干
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
对每个孩子 i ，都有一个胃口值 gi ，这是能让孩子们满足胃口的饼干的最小尺寸；
并且每块饼干 j ，都有一个尺寸 sj 。
如果 sj >= gi ，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。
你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

注意：
你可以假设胃口值为正。
一个小朋友最多只能拥有一块饼干。
*/

class Solution455 {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // 胃口值排序
        // 饼干尺寸排序，用最小的尺寸依次查找符合条件的孩子并累计满足的孩子数
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int count = 0;  // 记录以满足的孩子的下标
        int start = 0;
        for(size_t i=0; i<s.size(); i++) {
            for (int j=start; j<g.size();j++) {
                if (s[i] >= g[j]) {
                    // 饼干i满足孩子j
                    count++;
                    start = ++j;
                    break;   // 退出内层循环，继续尝试下一个饼干
                }
            }
        }
        return count; 
    }
};

/*
leetcode-376
摇摆序列
如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为摆动序列。
第一个差（如果存在的话）可能是正数或负数。少于两个元素的序列也是摆动序列。
例如， [1,7,4,9,2,5] 是一个摆动序列，因为差值 (6,-3,5,-7,3) 是正负交替出现的。

给定一个整数序列，返回作为摆动序列的最长子序列的长度。 
通过从原始序列中删除一些（也可以不删除）元素来获得子序列，剩下的元素保持其原始顺序。

贪心思路：
保留连续递增序列的收尾元素，这样更可能使得尾部的后一个元素成为摇摆序列。

实现：
状态转移。
当状态发生变化时，累加。
*/

class Solution376 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        enum State {BEGIN=1, UP=2, DOWN=3};

        int STATE = BEGIN;
        int res = 0;

        for(int i=1; i<nums.size();i++) {
            switch (STATE)
            {
            case BEGIN:
                if (nums[i]-nums[i-1] > 0) {
                    STATE = UP;
                    res++;
                } 
                if (nums[i]-nums[i-1] < 0) {
                    STATE = DOWN;
                    res++;
                }
                break;
            case UP:
                if (nums[i]-nums[i-1] < 0) {
                    STATE = DOWN;
                    res++;
                }
                break;
            case DOWN:
                if (nums[i] - nums[i-1] > 0) {
                    STATE = UP;
                    res++;
                }
                break;
            default:
                break;
            }
        }
        return res+1;
    }
};

/*
leetcode-402
移除k个数字
给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。
注意:
    num 的长度小于 10002 且 ≥ k。
    num 不会包含任何前导零。

基本思路：
如果删除数字后的数字最小，那么需要最高位最小，然后次高位最小。。。

也可以使用栈实现：
*/

class Solution402 {
public:
    string removeKdigits(string num, int k) {
        vector<int> _old, _new;
        string2vect(num, _old);
        int new_index = 0;
        for(int i=0; i<num.size()-k;i++) {
            // 新数字中第i位置，需要从老数字 [i, i+3] 范围内取最小的一个
            new_index = max<int>(new_index, i);
            int data = findmin(_old, new_index, i+k);
            _new.push_back(data);
        }
        string res;
        vect2string(res, _new);
        return res;
    }

    string removeKdigits2(string num, int k) {
        // 使用栈实现，只要还可以删除，而且待放入的元素更小就替换
        if (num.length() <= 0) {
            return "0";
        }
        vector<int> _old;
        string2vect(num, _old);

        vector<int> s;          // 用vector当一个栈用
        s.push_back(_old[0]);
        int deleteCnt = 0;

        for(int i=1; i<_old.size(); i++) {
            while (!s.empty() && s.back() > _old[i] && deleteCnt < k) {
                s.pop_back();
                deleteCnt++;
            } 
            s.push_back(_old[i]);
        }
        while(deleteCnt < k) {
            s.pop_back();
            deleteCnt++;
        }
        string res;
        vect2string(res, s);
        return res;
    }
private:
    void string2vect(string & num, vector<int> & vec) {
        for(int i=0; i<num.length();i++) {
            int data = num[i] - '0' + 0;
            vec.push_back(data);
        }
    }

    void vect2string(string & num, vector<int> & vec) {
        for(auto it=vec.begin(); it!=vec.end();it++) {
            if (num.empty() && *it == 0) {
                continue;
            }
            num += *it - 0 + '0'; 
        }
        if (num == "") {
            num = "0";
        }
    }

    int findmin(vector<int> & _old, int & start, int end) {
        int min = _old[start];
        int min_index = start;
        for(size_t i=start+1; i<=end; i++) {
            if (_old[i] < min) {
                min = _old[i];
                min_index = i;
            }
        }
        start = min_index+1;
        return min;
    }
};

/*
leetcode-55
跳跃游戏
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个位置。
输入: [2,3,1,1,4]
输出: true
解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。

思路：每次从可跳跃的范围内找一个最大的步数，以此为起点继续跳跃。
*/

class Solution55 {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size()==1 && nums[0]==0) {
            return true;
        }
        int index = 0;
        while(index < nums.size() && nums[index] != 0) {
            int range = nums[index];   // 当前可跳跃的范围是(index, index+range]
            if (index+range >= nums.size()-1) {
                return true;
            }
            // 贪心：每次从当前范围内找一个最大可跳到的位置，作为下一次跳跃的起点
            int max = 0;
            int max_index = 0;
            for(int i=index+1; i<=index+range && i< nums.size();i++) {
                if (max == 0 || nums[i] + i >= max) {
                    max = nums[i] + i;
                    max_index = i;
                }
            }
            index = max_index;
        }
        return false;
    }
};

/*
leetcode-45
跳跃游戏II
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。

*/

class Solution45 {
public:
    int jump(vector<int>& nums) {
        if (nums.size() <=1) {
            return 0;
        }
        int index = 0;
        int step = 0;

        while(index < nums.size() && nums[index] != 0) {
            int range = nums[index];   // 当前可跳跃的范围是(index, index+range]
            if (index+range >= nums.size()-1) {
                step++;    // 这时候再跳一次就到了
                break;
            }
            // 贪心：每次从当前范围内找一个最大可跳到的位置，作为下一次跳跃的起点
            int max = 0;
            int max_index = 0;
            for(int i=index+1; i<=index+range && i< nums.size();i++) {
                if (max == 0 || nums[i] + i >= max) {
                    max = nums[i] + i;
                    max_index = i;
                }
            }
            index = max_index;
            step++;
        }
        return step;
    }
};

/*
leetcode-452
射击气球
在二维空间中有许多球形的气球。对于每个气球，提供的输入是水平方向上，气球直径的开始和结束坐标。
由于它是水平的，所以y坐标并不重要，因此只要知道开始和结束的x坐标就足够了。
开始坐标总是小于结束坐标。平面内最多存在104个气球。

一支弓箭可以沿着x轴从不同点完全垂直地射出。
在坐标x处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被引爆。
可以射出的弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前进。
我们想找到使得所有气球全部被引爆，所需的弓箭的最小数量。

输入: [[10,16], [2,8], [1,6], [7,12]]
输出: 2

思路：
先将线段按照起点排序，
贪心：从最昨天的线段起点开始，每次取尽可能多的有交点的线段加入，并进行一次射击。
*/

class Solution452 {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() <= 0) {
            return 0;
        }

        std::sort(points.begin(), points.end(), VectComp());
        auto it=points.begin();
        vector<int> intersect = *it;
        int count = 0;

        for(++it;it!=points.end(); it++) {
            vector<int> v = *it;
            if (v[0] > intersect[1]) {
                count++;
                intersect = *it;
            } else if (v[1] <= intersect[1]) {
                intersect = v;
            } else {
                intersect[0] = v[0];
            }
        }
        return count+1;
    }
private:
    struct VectComp {
        bool operator() (const vector<int> & left, const vector<int> & right) {
            return (left.size() == 2 && right.size() == 2 && left[0] < right[0]);
        }
    };
};

int main()
{
    // Solution455 st455;
    // vector<int> g = {1, 2, 3};
    // vector<int> s = {1, 1};
    // cout << st455.findContentChildren(g, s) << endl;

    // Solution376 st376;
    // vector<int> v = {1,17,5,10,13,15,10,5,16,8};
    // // vector<int> v = {1,7,4,9,2,5};
    // // vector<int> v = {0,0};
    // cout << st376.wiggleMaxLength(v) << endl;

    // Solution402 st402;
    // string num = "1234567890";
    // cout << st402.removeKdigits2(num, 9) << endl;

    // Solution55 st55;
    // vector<int> num = {5,9,3,2,1,0,2,3,3,1,0,0};
    // cout << st55.canJump(num) << endl;

    // Solution45 st45;
    // vector<int> v = {2,3,1,1,4};
    // cout << st45.jump(v) << endl;

    Solution452 st452;
    vector<vector<int>> v = {{1,6}, {10,16}, {7,12},{2,8}};
    cout << st452.findMinArrowShots(v) << endl;

    system("pause");
    return 0;
}