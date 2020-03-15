# ���������ܽ�

## ���ݽṹ

* ջ�����С���
  * ʹ�ö���ʵ��ջ��
  * ʹ��ջʵ�ֶ��У�
  * ����min������ջ��
  * �Ϸ��ĳ�ջ���У�
  * �򵥵ļ�������
  * �����е�k�������
  * Ѱ����λ����

```c++
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <set>

using namespace std;

/*
ջ��stack�������У�queue�����ѣ�heap���ľ������⡣

ʹ�ö���ʵ��ջ��
ʹ��ջʵ�ֶ��У�
����min������ջ��
�Ϸ��ĳ�ջ���У�
�򵥵ļ�������
�����е�k�������
Ѱ����λ����
*/

/*
leetcode-225
ʹ�ö���ʵ��ջ�����в�����

    push(x) -- Ԫ�� x ��ջ
    pop() -- �Ƴ�ջ��Ԫ��
    top() -- ��ȡջ��Ԫ��
    empty() -- ����ջ�Ƿ�Ϊ��
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
ʹ��ջʵ�ֶ���
ʹ��ջʵ�ֶ��е����в�����

    push(x) -- ��һ��Ԫ�ط�����е�β����
    pop() -- �Ӷ����ײ��Ƴ�Ԫ�ء�
    peek() -- ���ض����ײ���Ԫ�ء�
    empty() -- ���ض����Ƿ�Ϊ�ա�
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
����min������ջ
���һ��֧�� push��pop��top �����������ڳ���ʱ���ڼ�������СԪ�ص�ջ��

    push(x) -- ��Ԫ�� x ����ջ�С�
    pop() -- ɾ��ջ����Ԫ�ء�
    top() -- ��ȡջ��Ԫ�ء�
    getMin() -- ����ջ�е���СԪ�ء�
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
    multiset<int> _set;   // ���ظ�Ԫ�صĺ����������o(logn)��Ԫ��Ĭ���������С�
};


/*
http://poj.org/problem?id=1363
�Ϸ��ĳ�ջ���У�
��֪��1��n���������У���˳����ջ��ÿ��������ջ��ȿ��Գ�ջ��Ҳ������ջ��ͣ����
�ȴ������������ջ���ٳ�ջ������������еĳ�ջ�����Ƿ�Ϸ���
1.����1-n��˳�򣬽�Ԫ��push����ջS��:
2.ÿpushһ��Ԫ�أ������ջ��S.top()�Ƿ������ͷ��Ԫ��order.front()��ͬ��
3.�����ͬ��ͬʱ����ջ��Ԫ�������ͷ��Ԫ�أ�ֱ��ջ�ջ�ջ�������ͷ��Ԫ�ز�ͬ�� 
������ջΪ�գ���˵�����кϷ������򲻺Ϸ���
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
�򵥵ļ�����
ʵ��һ�������ļ�����������һ���򵥵��ַ������ʽ��ֵ��
�ַ������ʽ���԰��������� ( �������� )���Ӻ� + ������ -���Ǹ������Ϳո�  ��

˼·��
��������������
����+/-  �ɼ���ģʽ
����������  ���ɼ���ģʽ

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
                    // ������Ҫ���� 1+(5) 1+(-5) 1+(+5) ��(-5) (+5) (5) �������
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
�����е�k�����
��δ������������ҵ��� k ������Ԫ�ء�
��ע�⣬����Ҫ�ҵ������������ĵ� k ������Ԫ�أ������ǵ� k ����ͬ��Ԫ�ء�

˼·��������k��Ԫ�ص�С���ѣ��Ѷ�Ԫ����С���ڲ�Ԫ�ض��ȶѶ�Ԫ�ش�
��װ��k��Ԫ�أ��Ѷ�Ԫ�ؾ��ǵ�k��
Ȼ�����αȽϺ�ߵ�Ԫ�أ�������ڶѶ�����루ͬʱ�����Ѷ������Ѷ����ǵ�k�����ġ�

����� --- �ȽϺ�����greater
С���� --- �ȽϺ�����less
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
Ѱ����λ��
��λ���������б��м����������б�����ż������λ�������м���������ƽ��ֵ��
���磬
[2,3,4] ����λ���� 3
[2,3] ����λ���� (2 + 3) / 2.0 = 2.5

���һ��֧���������ֲ��������ݽṹ��
    void addNum(int num) - �������������һ�����������ݽṹ�С�
    double findMedian() - ����Ŀǰ����Ԫ�ص���λ����
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
            // max_q��min_q������ȣ���max_q.top()��num��ѡһ����С�߲���max_q
            if (num < max_q.top()) {
                max_q.push(num);
            } else {
                min_q.push(num);
            }
        } else if (max_q.size() < min_q.size()) {
            // min_q�бȽ϶࣬��num��min_q.top()��ѡһ��С�Ĳ���max_q��
            int data = min_q.top();
            if (data < num) {
                max_q.push(data);
                min_q.pop();
                min_q.push(num);
            } else {
                max_q.push(num);
            }
        } else {
            // max_q�бȽ϶࣬��max_q.top()��num��ѡһ����Ĳ���min_q��
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
    // С���ѣ��Ѷ�Ԫ����С����ߵ�Ԫ�ض����ڶѶ�Ԫ�أ����ڴ洢���ݵĺ�벿�֡�  
    priority_queue<int, vector<int>, greater<int>> min_q;
    // ����ѣ��Ѷ�Ԫ��������Ԫ�ض�С�ڶѶ�Ԫ�أ����ڴ洢���ݵ�ǰ�벿�֡�
    priority_queue<int, vector<int>, less<int>> max_q;

    // ��֤����ѵ�top <= С���ѵ�top
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

