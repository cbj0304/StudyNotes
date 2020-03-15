# 力扣题型总结

## 数据结构

* 栈、队列、堆
  * 使用队列实现栈；
  * 使用栈实现队列；
  * 包含min函数的栈；
  * 合法的出栈序列；
  * 简单的计算器；
  * 数组中第k大的数；
  * 寻找中位数；

```c++
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <set>

using namespace std;

/*
栈（stack）、队列（queue）、堆（heap）的经典问题。

使用队列实现栈；
使用栈实现队列；
包含min函数的栈；
合法的出栈序列；
简单的计算器；
数组中第k大的数；
寻找中位数；
*/

/*
leetcode-225
使用队列实现栈的下列操作：

    push(x) -- 元素 x 入栈
    pop() -- 移除栈顶元素
    top() -- 获取栈顶元素
    empty() -- 返回栈是否为空
*/

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        _stack.push_back(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int data = _stack.back();
        _stack.pop_back();
        return data;
    }
    
    /** Get the top element. */
    int top() {
        return _stack.back();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return _stack.empty();
    }
private:
    deque<int> _stack;
};

/*
leetcode-232
使用栈实现队列
使用栈实现队列的下列操作：

    push(x) -- 将一个元素放入队列的尾部。
    pop() -- 从队列首部移除元素。
    peek() -- 返回队列首部的元素。
    empty() -- 返回队列是否为空。
*/
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        _queue.push_back(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int data = _queue.front();
        _queue.pop_front();
        return data;
    }
    
    /** Get the front element. */
    int peek() {
        return _queue.front();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return _queue.empty();
    }
private:
    deque<int> _queue;
};

/*
leetcode-155
包含min函数的栈
设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

    push(x) -- 将元素 x 推入栈中。
    pop() -- 删除栈顶的元素。
    top() -- 获取栈顶元素。
    getMin() -- 检索栈中的最小元素。
*/

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {     
    }
    
    void push(int x) {
        _set.insert(x);  
        _stack.push_back(x);        
    }
    
    void pop() {
        int data = _stack.back();
        auto it = _set.find(data);
        if (it != _set.end()) {
            _set.erase(it);
        } 
        _stack.pop_back();
    }
    
    int top() {
        return _stack.back();      
    }
    
    int getMin() {
        auto it = _set.begin();
        if (it != _set.end()) {
            return *it;
        }
        return -1;
    }

private:
    deque<int> _stack;
    multiset<int> _set;   // 有重复元素的红黑树，查找o(logn)，元素默认升序排列。
};


/*
http://poj.org/problem?id=1363
合法的出栈序列：
已知从1至n的数字序列，按顺序入栈，每个数字入栈后既可以出栈，也可以在栈中停留，
等待后面的数字入栈后再出栈，求该数字序列的出栈序列是否合法？
1.按照1-n的顺序，将元素push进入栈S中:
2.每push一个元素，即检查栈顶S.top()是否与队列头部元素order.front()相同。
3.如果相同则同时弹出栈顶元素与队列头部元素，直到栈空或栈顶与队列头部元素不同。 
若最终栈为空，则说明序列合法，否则不合法。
*/

class solutionPoj {
public:
    bool check_is_valid_order(queue<int> &q) {
        stack<int> s;
        int n = q.size();
        for (int i=1; i<=n;i++) {
            s.push(i);
            while (!s.empty() && s.top() == q.front()) {
                s.pop();
                q.pop();
            }  
        }
        return s.empty();
    }
};

/*
leetcode-224
简单的计算器
实现一个基本的计算器来计算一个简单的字符串表达式的值。
字符串表达式可以包含左括号 ( ，右括号 )，加号 + ，减号 -，非负整数和空格  。

思路：
操作数，操作符
遇到+/-  可计算模式
遇到左括号  不可计算模式

*/
class Solution224 {
public:
    int calculate(string s) {
        stack<char> ops;
        vector<int> data;
        int tmpdata = 0;
        char cur_op;
        int cur_d1, cur_d2;
        bool compute_flag = false;
        for(int i=0; i<s.length();) {
            switch (s[i])
            {
            case '+':
            case '-':
                {
                    ops.push(s[i]);
                    cout << "into stack=" << s[i] << endl;
                    i++;
                    compute_flag = true;
                    break;
                }
            case '(':
                {
                    compute_flag = false;
                    i++;
                    // 这里需要处理 1+(5) 1+(-5) 1+(+5) 中(-5) (+5) (5) 这种情况
                    break;
                }  
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                {
                    while(i<s.length() && s[i] >= '0' && s[i] <= '9') {
                        tmpdata = 10 * tmpdata + (s[i] - '0' + 0); 
                        i++;
                    }
                    data.push_back(tmpdata); 
                    cout << "into data vec=" << tmpdata << endl;
                    tmpdata = 0;
                    if (compute_flag) {
                        while(!ops.empty()) {
                            cur_op = ops.top();
                            if (cur_op == '+' || cur_op == '-') {
                                cur_d2 = data.back(); data.pop_back();
                                cur_d1 = data.back(); data.pop_back();
                                data.push_back(my_op(cur_d1, cur_d2, cur_op));
                                ops.pop();
                                cout << "-----" << cur_d1 << cur_op << cur_d2 << endl;
                            }
                        }
                    }
                    break;
                }
            
            default:
                i++;
                break;
            }

        }
        while(!ops.empty()) {
            cur_op = ops.top();
            if (cur_op == '+' || cur_op == '-') {
                cur_d2 = data.back(); data.pop_back();
                cur_d1 = data.back(); data.pop_back();
                data.push_back(my_op(cur_d1, cur_d2, cur_op));
                ops.pop();
                // cout << "-----" << cur_d1 << cur_op << cur_d2 << endl;
            }
        }
        return data.size() > 0 ? data[0] : -1;
    }
private:
    int my_op(int d1, int d2, char op) {
        int res = -1;
        switch (op)
        {
        case '+':
            res = d1 + d2;
            break;
        case '-':
            res = d1 - d2;
            break;
        default:
            break;
        }
        return res;
    }
};
/*
leetcode-215
数组中第k大的数
在未排序的数组中找到第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

思路：创建有k个元素的小根堆，堆顶元素最小，内部元素都比堆顶元素大；
先装入k个元素，堆顶元素就是第k大。
然后依次比较后边的元素，如果大于堆顶则插入（同时弹出堆顶），堆顶就是第k个最大的。

大根堆 --- 比较函数是greater
小根堆 --- 比较函数是less
*/

class Solution215 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> q;
        for(int i=0; i<k;i++) {
            q.push(nums[i]);
        }

        for(int i=k; i<nums.size();i++) {
            if (nums[i] > q.top()) {
                q.pop();
                q.push(nums[i]);
            }
        }
        return q.top();
    }
};

/*
leetcode-295
寻找中位数
中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。
例如，
[2,3,4] 的中位数是 3
[2,3] 的中位数是 (2 + 3) / 2.0 = 2.5

设计一个支持以下两种操作的数据结构：
    void addNum(int num) - 从数据流中添加一个整数到数据结构中。
    double findMedian() - 返回目前所有元素的中位数。
*/

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if (max_q.empty()) {
            max_q.push(num);
        } else if (max_q.size() == min_q.size()) {
            // max_q和min_q长度相等，从max_q.top()和num中选一个较小者插入max_q
            if (num < max_q.top()) {
                max_q.push(num);
            } else {
                min_q.push(num);
            }
        } else if (max_q.size() < min_q.size()) {
            // min_q中比较多，从num和min_q.top()中选一个小的插入max_q中
            int data = min_q.top();
            if (data < num) {
                max_q.push(data);
                min_q.pop();
                min_q.push(num);
            } else {
                max_q.push(num);
            }
        } else {
            // max_q中比较多，从max_q.top()和num中选一个大的插入min_q中
            int data = max_q.top();
            if (data > num) {
                min_q.push(data);
                max_q.pop();
                max_q.push(num);
            } else {
                min_q.push(num);
            }
        }
    }
    
    double findMedian() {
        if (max_q.size() == min_q.size()) {
            return ((double)max_q.top() + (double)min_q.top()) / 2.0;
        } else if (max_q.size() > min_q.size()) {
            return (double)max_q.top();
        } else {
            return (double)min_q.top();
        }
    }
private:
    // 小根堆，堆顶元素最小，里边的元素都大于堆顶元素，用于存储数据的后半部分。  
    priority_queue<int, vector<int>, greater<int>> min_q;
    // 大根堆，堆顶元素最大，里边元素都小于堆顶元素，用于存储数据的前半部分。
    priority_queue<int, vector<int>, less<int>> max_q;

    // 保证大根堆的top <= 小根堆的top
};

int main() {

    // solutionPoj st;
    // queue<int> q;
    // q.push(3);
    // q.push(2);
    // q.push(5);
    // q.push(4);
    // q.push(1);
    // cout << st.check_is_valid_order(q) << endl;

    // Solution224 st224;
    // int res = st224.calculate("1+ 121 -(14+ (5-6))");
    // // int res = st224.calculate("(7)-(0)+(4)");
    // // int res = st224.calculate("7+(-4)");
    // cout << "res=" << res << endl;

    // Solution215 st215;
    // vector<int> v = {3,2,1,5,6,4};
    // cout << st215.findKthLargest(v, 2) << endl;

    MedianFinder mf;
    mf.addNum(10);
    mf.addNum(9);
    mf.addNum(1);
    mf.addNum(7);

    double res = mf.findMedian();
    cout << res << endl;


    system("pause");
    return 0;
}
```

