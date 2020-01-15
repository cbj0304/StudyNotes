#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <queue>
#include <iterator>
#include <sstream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* createTree() {
    TreeNode* root = new TreeNode(10);
    TreeNode* n8 = new TreeNode(8);
    TreeNode* n9 = new TreeNode(9);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n10 = new TreeNode(10);
    TreeNode* n7 = new TreeNode(7);

    root->left = n8;
    root->right = n9;
    n8->left = n3;
    n8->right = n5;
    n5->left = n7;
    n9->right = n10;

    return root;
}

void inOrderPrint(TreeNode* root) {
    if (root == nullptr) {
        return;
    } else {
        inOrderPrint(root->left);
        cout << root->val << endl;
        inOrderPrint(root->right);    
    }
}

/*
leetcode-113
二叉树路径和
给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。
*/
class Solution113 {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> sumpath;
        vector<int> cpath;
        allPath(root, sumpath, cpath, sum);
        return sumpath;
    }
private:
    //  不要受限于leetcode定义的数据结构，自己实现私有成员函数，统计各路径和
    void allPath(TreeNode* root, vector<vector<int>> &sumpath, vector<int> &cpath, int sum) {
        if (root == nullptr) {
            return;
        }

        cpath.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            int cursum = 0;
            cout << cpath.size() << endl;
            for(size_t i=0; i<cpath.size();i++) {
                // cout << i << "..." << cpath[i] << endl;
                cursum += cpath[i];
            }
            if (cursum == sum) {
                sumpath.push_back(cpath);
            }
        }

        allPath(root->left, sumpath, cpath, sum);
        allPath(root->right, sumpath, cpath, sum);
        cpath.pop_back();
    }
};

/*
leetcode-236
最近的公共祖先
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

最近公共祖先定义：“对于有根树 T 的两个结点 p、q，
最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

解题思路：
包含p的路径上的每一个节点都是p的祖先；
包含q的路径上的每一个节点都是q的祖先；
沿着p、q路径从后往前找，第一个公共的节点即为公共祖先。
*/

class Solution236 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> p_path, q_path, curpath;
        curpath.clear();
        getPath(root, p, curpath, p_path);
        curpath.clear();
        getPath(root, q, curpath, q_path);

        if (p_path.size()==0 || q_path.size()==0) {
            return nullptr;
        }

        for(size_t i = p_path.size()-1; i>=0;i--) {
            if (find(q_path.begin(),q_path.end(), p_path[i]) != q_path.end()) {
                return q_path[i];
            }
        }
    }

private:
    // 计算节点p、q的路径
    void getPath(TreeNode* root, TreeNode* p, 
        vector<TreeNode*> & curpath, vector<TreeNode*> & p_path) {
            if (root == nullptr) {
                return;
            }

            curpath.push_back(root);

            if (root == p) {
                p_path = curpath;
                return;
            }

            // if (root->left == nullptr && root->right == nullptr) {
            //     curpath.clear();
            // }

            getPath(root->left, p, curpath, p_path);
            getPath(root->right, p, curpath, p_path);

            curpath.pop_back();
    }
};

/*
leetcode-114
二叉树转链表
给定一个二叉树，原地将它展开为链表，链表为二叉树前序遍历的结果。
思路：二叉树深度遍历(DFS) 等价于 前序遍历。
*/

class Solution114 {
public:
    void flatten(TreeNode* root) {
        // 根节点为空或者只有一个节点时，直接返回
        if (root == nullptr || 
            (root->left == nullptr && root->right == nullptr)) {
            return;
        }

        stack<TreeNode*> s;
        s.push(root);
        TreeNode* last_node = root;
        while (!s.empty()){
            TreeNode* node = s.top();
            TreeNode* left_node = node->left;
            TreeNode* right_node = node->right;
            last_node->left = nullptr;
            last_node->right = node;
            last_node = node;
            s.pop();
            if (right_node) {
                s.push(right_node);
            }            
            if (left_node) {
                s.push(left_node);
            }
        }          
    }

};

/*
leetcode-199
二叉树的右视图：
给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

思路：二叉树的层次遍历（广度优先遍历BFS），取每一层最后一个。
*/

class Solution199 {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        // 根节点为空或者只有一个节点，需要特殊处理。
        if (root == nullptr) {
            return  res;
        }
        if (root->left == nullptr && root->right == nullptr) {
            res.push_back(root->val);
            return res;
        }

        map<TreeNode*, TreeNode*> parent_map;
        vector<pair<TreeNode*, int>> node_level;
        queue<TreeNode*> q;

        q.push(root);
        parent_map.insert(make_pair(root, nullptr));

        while (!q.empty()) {
            TreeNode* node = q.front();
            
            node_level.push_back(
                std::make_pair(node, getLevel(node, parent_map)));
            cout << "node=" << node->val << ", level=" << getLevel(node, parent_map) << endl;
            q.pop();

            if (node->right) {
                q.push(node->right);
                parent_map.insert(make_pair(node->right, node));
            }

            if (node->left) {
                q.push(node->left);
                parent_map.insert(make_pair(node->left, node));
            }   
        }

        int last_level = -1;
        for(size_t i=0; i<node_level.size(); i++) {
            TreeNode* node = node_level[i].first;
            int level = node_level[i].second;
            if (level == last_level + 1) {
                res.push_back(node->val);
                last_level += 1;
            }
        }
        return res;
    }
private:
    int getLevel(TreeNode* node, map<TreeNode*, TreeNode*> &parent_map) {
        int level = 0;
        if (node == nullptr || parent_map.size() == 0) {
            return level;
        }
        while(parent_map.find(node) != parent_map.end()) {  
            node = parent_map[node];
            
            if (node == nullptr) {
                break;
            }
            level++;  
        }
        return level;
    }
    
};

/*
leetcode-35
有序数组中找插入位置，时间复杂度o(logN)

思路：二分查找
*/

class Solution35 {
public:
    int searchInsert(std::vector<int> & nums, int target) {
        int low = 0; 
        int high = nums.size()-1;
        int mid = (low + high) / 2;

        while(low < high) {
            int mid = (low + high) / 2;
            if (target == nums[mid]) {
                // 找到
                return mid;
            } else if (target < nums[mid]) {
                high = mid-1;
            } else {
                low = mid + 1;
            }
            
        }
        // 找到最后mid和low会聚集到一点
        // 如果target比这个位置大，则往后移动一个位置；反之直接返回low
        if ((low + high) / 2 == low && target > nums[low]) {
            low += 1;
        }
        return low;
    }
};

/*
leetcode-34
区间查找
给定一个按照升序排列的整数数组 nums，和一个目标值 target。
找出给定目标值在数组中的开始位置和结束位置。
算法时间复杂度必须是 O(log n) 级别。
如果数组中不存在目标值，返回 [-1, -1]。

思路1:
二分查找找到其中一个符合条件的，然后向左移动确定左端点，向右移动确定右断点。
但是这种做法会超时。！！！

思路2：
修正的二分查找算法
二分查找算法，直接确定左区间和右区间。

*/

class Solution34 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size()-1;
        vector<int> res;
        int left = -1, right = -1;
        
        // 修正的二分查找，找右端点
        while(low <= high) {
            int mid = (low + high) / 2;
            if (target < nums[mid]) {
                high = mid - 1;
            } else if (target > nums[mid] ) {
                low = mid + 1;
            } else {
                if (mid == nums.size()-1 || nums[mid+1] != target) {
                    right = mid;
                    break;
                }
                // 找到了其中一个，还需要继续找最右侧的那个
                low = mid + 1;
            }
        }

        // 修正的二分查找，找左端点
        low = 0;
        high = nums.size()-1;
        while(low <= high) {
            int mid = (low + high) / 2;
            if (target < nums[mid]) {
                high = mid - 1;
            } else if (target > nums[mid] ) {
                low = mid + 1;
            } else {
                if (mid == 0 || nums[mid-1] != target) {
                    left = mid;
                    break;
                }
                // 找到了其中一个，还需要继续找最右侧的那个
                high = mid - 1;
            }
        }
        res.push_back(left);
        res.push_back(right);
        return res;
    }
};

/*
leetcode-33
旋转数组
假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。
你可以假设数组中不存在重复的元素。
你的算法时间复杂度必须是 O(log n) 级别。

思路：修正的二分查找法。
画图验证：
如果mid小于high，说明[mid, high]是有序的，用二分查找法计算target是否在该区间。不在改区间则在[low, mid]区间。
如果mid大于high，说明[low, mid]是有序的，用二分查找法计算target是否在该区间。
不断在有序的一半区间上采用二分查找。直到区间为0。
*/

class Solution33 {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size()-1;
        int res = -1;

        if (nums.size()==1 && nums[0]==target) {
            return 0;
        }

        while (low < high) {
            int mid = (low+high) / 2;

            if (nums[mid + 1] < nums[high]) {
                // 右侧区间查找
                res = Bisearch(nums, mid + 1, high, target);
                if (res != -1) {
                    break;
                }
                // 找不到说明只可能在左侧区间，更新low/high继续
                high = mid;
            } else if (nums[mid + 1] > nums[high]){
                // 左侧区间查找
                res = Bisearch(nums, low, mid, target);
                if (res != -1) {
                    break;
                }
                // 找不到说明只可能在右侧区间，更新low/high继续
                low = mid+1;
            } else {
                // 特殊情况
                // high=mid+1 剩余2个元素  1,3
                // high=mid+1 剩余3个元素  1,3,5
                if (nums[low] == target) res = low;
                if (nums[high] == target) res = high;
                if (nums[mid] == target) res = mid;
                // 查完了
                break;
            }
        }
        return res;   
    }
private:
    int Bisearch(vector<int>& nums, int low, int high, int target) {
        int res = -1;

        while(low <= high) {
            int mid = (low+high) / 2;
            if (target < nums[mid]) {
                high = mid - 1;
            } else if (target > nums[mid]) {
                low = mid + 1;
            } else {
                res = mid;
                break;
            }
        }
        return res;
        
    }
};

/*
leetcode-449
二叉查找树编码与解码
序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，
或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建。

设计一个算法来序列化和反序列化二叉搜索树。 对序列化/反序列化算法的工作方式没有限制。 
您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。

思路：
序列化先根遍历。
反序列化按序构建二叉搜索树。（只要确定了根节点，构建的二叉搜索树是唯一的）
*/

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        vector<int> seq;
        preOrder(root, seq);
        string str;
        vector2string(seq, str);
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        // 二叉搜索树的插入
        vector<int> v;
        string2vector(data, v);
        if (v.size() == 0) {
            return nullptr;
        }
        TreeNode *root = nullptr;
        for(auto it=v.begin();it!=v.end();it++) {
            root = BSTinsert(root, *it);
        }
        return root;
    }
private:
    void preOrder(TreeNode* root, vector<int> & seq) {
        if (root == nullptr) {
            return;
        }
        seq.push_back(root->val);
        preOrder(root->left, seq);
        preOrder(root->right, seq);
    }

    void vector2string(vector<int> &data, string& str) {
        stringstream ss;
        for(auto it=data.begin(); it!=data.end();it++) {
            ss << *it;
            if (it != data.end() - 1) {
                ss << "#";
            }
        }
        str = ss.str();
    }

    int toInt1(string &s) {
        int data;
        stringstream ss;
        ss << s;
        ss >> data;
        return data;
    }

    void string2vector(string &str, vector<int> &v) {
        string item("");
        stringstream ss(str);
        while(std::getline(ss, item, '#')) {
            v.push_back(toInt1(item));
        }
    }
    TreeNode* BSTinsert(TreeNode* root, int val) {
        if (root == nullptr) {
            // 如果根节点为空，直接插入并返回
            TreeNode* root = new TreeNode(val);
            return root;
        } else {
            TreeNode* node = root;  // 当前节点
            while(node) {
                // 如果待插入值小于当前节点的值，则向左走。
                if (val < node->val) {
                    if (node->left == nullptr) {
                        node->left = new TreeNode(val);
                        break;
                    }
                    node = node->left;
                } 
                // 如果待插入值大于当前节点的值，则向右走
                else if (val > node->val) {
                    if (node->right == nullptr) {
                        node->right = new TreeNode(val);
                        break;
                    }
                    node = node->right;
                } else {
                    // 找到，直接返回
                    // cout << "has set this val " << val << endl;
                    break;
                }
            } 
            return root; 
        }
    }
};

/*
leetcode-315
逆序数
给定一个整数数组 nums，按要求返回一个新数组 counts。数组 counts 有该性质： counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量。

示例:
输入: [5,2,6,1] 
输出: [2,1,1,0] 
解释:
5 的右侧有 2 个更小的元素 (2 和 1).
2 的右侧仅有 1 个更小的元素 (1).
6 的右侧有 1 个更小的元素 (1).
1 的右侧有 0 个更小的元素.
*/

class Solution315 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        TreeNode* root = nullptr;
        vector<int> res;
        if (nums.size()==0) {
            return res;
        }
        for (int i=nums.size()-1; i>=0; i--) {
            int val = nums[i];
            int count = 0;
            if (root == nullptr) {
                root = new TreeNode(val);
                res.push_back(0);
            } else {
                TreeNode* node = root;
                while (node) {
                    if (val > node->val) {  
                        count += (node->count + 1);             
                        if (node->right == nullptr) {     
                            node->right = new TreeNode(val);
                            res.push_back(count);
                            break;
                        }
                        node = node->right;
                    } else if (val <= node->val) {
                        node->count++;
                        if (node->left == nullptr) {
                            node->left = new TreeNode(val);
                            res.push_back(count);
                            break;
                        }
                        node = node->left;
                    }
                } 
            }
        }

        reverse(res.begin(), res.end());
        return res;
    }
private:
    struct TreeNode {
        int val;
        int count;           // 逆序数
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), count(0), left(NULL), right(NULL) {}
    };
};

int main() 
{
    // TreeNode* root = createTree();

    // Codec cc;
    // string str = cc.serialize(root);
    // TreeNode* newroot = cc.deserialize(str);
    // inOrderPrint(newroot);

    Solution315 st315;
    vector<int> nums = {-1,-1};
    vector<int> nixu = st315.countSmaller(nums);
    std::copy(nixu.begin(), nixu.end(), ostream_iterator<int>(cout, " "));

    system("pause");
    return 0;
}