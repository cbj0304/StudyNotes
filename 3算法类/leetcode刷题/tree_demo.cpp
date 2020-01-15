#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <queue>
#include <stack>

using namespace std;

// 树的节点
struct BiNode {
    int val;
    BiNode* left;
    BiNode* right;

    BiNode(int _val): val(_val), left(nullptr), right(nullptr) {
    }
};

// 创建树
BiNode* createTree() {
    BiNode* root = new BiNode(10);
    BiNode* n8 = new BiNode(8);
    BiNode* n9 = new BiNode(9);
    BiNode* n3 = new BiNode(3);
    BiNode* n5 = new BiNode(5);
    BiNode* n10 = new BiNode(10);
    BiNode* n7 = new BiNode(7);

    root->left = n8;
    root->right = n9;
    n8->left = n3;
    n8->right = n5;
    n5->left = n7;
    n9->right = n10;

    return root;
}

// 树的中序遍历
void inOrderPrint(BiNode* root) {
    if (root == nullptr) {
        return;
    }

    inOrderPrint(root->left);
    cout << root->val << " ";
    inOrderPrint(root->right);
}

// 计算叶子节点数
void countLeaf(BiNode* root, int& count) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        count++;
    } else {
        countLeaf(root->left, count);
        countLeaf(root->right, count);
    }  
}

// 计算树的高度
int treeHeight(BiNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int l = treeHeight(root->left);
    int r = treeHeight(root->right);
    return max<int>(l, r) + 1;
}

// 树的拷贝
BiNode* copyTree(BiNode* root) {
    if (root == nullptr) {
        return nullptr;
    }

    BiNode* newroot = new BiNode(root->val);
    newroot->left = copyTree(root->left);
    newroot->right = copyTree(root->right);
    return newroot;
}

// 树的销毁
void destroyTree(BiNode* root) {
    if (root == nullptr) {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

// 计算树的各种路径
// 通过前序遍历的方式访问到某一结点时，把该结点添加到路径上。遇到叶子节点就打印所有结果，并把当前节点弹出。
void allPath(BiNode* root, vector<int> & v, int& index) {
    cout << index++ << "... ..." << endl;
    if (root == nullptr) {
        return;
    }

    v.push_back(root->val);
    // cout << "root->val= " << root->val << endl;

    if (root->left == nullptr && root->right == nullptr) {
        cout << "output " << root->val  << "-----"<< endl; 
        std::copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    
    allPath(root->left, v, index);
    allPath(root->right, v, index);
    // cout << "pop back= " << v.back() << endl;
    v.pop_back();  // 当一个节点的左右子树都处理完了（其实是叶子节点），需要把这个节点弹出来，返回到其上一层的父节点。
}

// 树的宽度优先搜索（BFS）
// 通过队列实现
// 类似于层次遍历
void BFS(BiNode* root) {
    if (root == nullptr) {
        return;
    }
    queue<BiNode* > q;
    q.push(root);
    while(!q.empty()) {
        BiNode* node = q.front();
        cout << node->val << endl;
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
        q.pop();
    }
}

// 树的深度优先遍历（DFS）
// 通过栈实现
// 类似前序遍历（如栈的时候先push右节点，再push左节点）
void DFS(BiNode* root) {
    if (root == nullptr) {
        return;
    }

    stack<BiNode* > s;
    s.push(root);

    while(!s.empty()) {
        BiNode *node = s.top();
        cout << node->val << endl;
        s.pop();

        if (node->right) {
            s.push(node->right);
        }
        if (node->left) {
            s.push(node->left);
        }
    }
}

/*
二叉搜索树（BST = Binary Search Tree）的操作：

插入节点：
1.如果是空树，直接插入；
2.树不空，按二叉搜索树的性质查找插入位置，插入新节点；如果已有该值则不插入。

查找节点：
1. 如果是空树，直接返回；
2. 如果不是空树，
   val大于当前节点，则找它的右子树；
   val小于当前节点，则找它的左子树；
   依次重述上述过程，直到找到或者为nullptr。

删除节点：
首先查找元素是否在二叉搜索树中，如果不存在，则返回, 否则要删除的结点可能分下面四种情况：
a. 要删除的结点无孩子结点-->直接删除该结点;
b. 要删除的结点只有左孩子结点-->删除该结点且使被删除节点的双亲结点left指向被删除节点的左孩子结点
c. 要删除的结点只有右孩子结点-->删除该结点且使被删除节点的双亲结点left指向被删除节点的右孩子结点
d. 要删除的结点有左、右孩子结点-->在它的右子树中寻找中序下的第一个结点(val最小)，用它的值填补到被删除节点中，在来处理该结点的删除问题
*/
// 向二叉搜索树插入数据
BiNode* BSTInsert(BiNode* root, int val) {
    if (root == nullptr) {
        // 如果根节点为空，直接插入并返回
        BiNode* root = new BiNode(val);
        return root;
    } else {
        BiNode* node = root;  // 当前节点
        while(node) {
            // 如果待插入值小于当前节点的值，则向左走。
            if (val < node->val) {
                if (node->left == nullptr) {
                    node->left = new BiNode(val);
                    break;
                }
                node = node->left;
            } 
            // 如果待插入值大于当前节点的值，则向右走
            else if (val > node->val) {
                if (node->right == nullptr) {
                    node->right = new BiNode(val);
                    break;
                }
                node = node->right;
            } else {
                // 找到，直接返回
                cout << "has set this val " << val << endl;
                break;
            }
        } 
        return root; 
    }
}

// 二叉搜索树的查找
BiNode* BSTSearch(BiNode* root, int val) {
    if (root == nullptr) {
        return nullptr;
    } else {
        BiNode* node = root;
        BiNode* res = nullptr;
        while (node) {
            if (val == node->val) {
                res = node;
                break;
            } else if (val > node->val) {
                if (node->right != nullptr) {
                    node = node->right;
                    continue;
                } else {
                    break;
                }
            } else {
                if (node->left != nullptr) {
                    node = node->left;
                    continue;
                } else {
                    break;
                }
            }
        }
        return res;    
    }
}

int main() 
{
    BiNode *root = nullptr;
    root = BSTInsert(root, 9);
    root = BSTInsert(root, 8);
    root = BSTInsert(root, 50);
    root = BSTInsert(root, 99);
    root = BSTInsert(root, 29);
    root = BSTInsert(root, 3);
    inOrderPrint(root);

    BiNode* node = BSTSearch(root, 9);
    if (node) {
        cout << "find val=" << node->val << endl;
    }
    
    system("pause");
    return 0;
}