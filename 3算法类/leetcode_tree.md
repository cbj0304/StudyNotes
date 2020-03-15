[toc]

# ���������ܽ�

## ��������������

* �����������

* ����Ҷ�ӽڵ���

* �������ĸ߶�

* ���Ŀ���

* ��������

* �������ĸ���·��

* ���Ŀ������������BFS��

* �����������������DFS��

* ���������������룬���ң�ɾ����

* ������ԭ��ת����

  ``` c++
  #include <iostream>
  #include <cstdlib>
  #include <vector>
  #include <iterator>
  #include <queue>
  #include <stack>
  
  using namespace std;
  
  /*
  // �����������
  // ����Ҷ�ӽڵ���
  // �������ĸ߶�
  // ���Ŀ���
  // ��������
  // �������ĸ���·��
  // ���Ŀ������������BFS��
  // �����������������DFS��
  // ���������������룬���ң�ɾ����
  // ������ԭ��ת����
  */
  
  
  // ���Ľڵ�
  struct BiNode {
      int val;
      BiNode* left;
      BiNode* right;
      int layer;           // �������Ĳ��
  
      BiNode(int _val): val(_val), left(nullptr), right(nullptr), layer(0) {
      }
  };
  
  // ������
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
  
  // �����������
  void inOrderPrint(BiNode* root) {
      if (root == nullptr) {
          return;
      }
  
      inOrderPrint(root->left);
      cout << root->val << " ";
      inOrderPrint(root->right);
  }
  
  // ����Ҷ�ӽڵ���
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
  
  // �������ĸ߶�
  int treeHeight(BiNode* root) {
      if (root == nullptr) {
          return 0;
      }
  
      int l = treeHeight(root->left);
      int r = treeHeight(root->right);
      return max<int>(l, r) + 1;
  }
  
  // ���Ŀ���
  BiNode* copyTree(BiNode* root) {
      if (root == nullptr) {
          return nullptr;
      }
  
      BiNode* newroot = new BiNode(root->val);
      newroot->left = copyTree(root->left);
      newroot->right = copyTree(root->right);
      return newroot;
  }
  
  // ��������
  void destroyTree(BiNode* root) {
      if (root == nullptr) {
          return;
      }
  
      destroyTree(root->left);
      destroyTree(root->right);
      delete root;
  }
  
  // �������ĸ���·��
  // ͨ��ǰ������ķ�ʽ���ʵ�ĳһ���ʱ���Ѹý����ӵ�·���ϡ�����Ҷ�ӽڵ�ʹ�ӡ���н�������ѵ�ǰ�ڵ㵯����
  void allPath(BiNode* root, vector<int> & v, int& index) {
      cout << index++ << "... ..." << endl;
      if (root == nullptr) {
          return;
      }
  
      v.push_back(root->val);
      cout << "root->val= " << root->val << endl;
  
      if (root->left == nullptr && root->right == nullptr) {
          cout << "output " << root->val  << "-----"<< endl; 
          std::copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
          cout << endl;
      }
      
      allPath(root->left, v, index);
      allPath(root->right, v, index);
      cout << "pop back= " << v.back() << endl;
      v.pop_back();  // ��һ���ڵ�������������������ˣ���ʵ��Ҷ�ӽڵ㣩����Ҫ������ڵ㵯���������ص�����һ��ĸ��ڵ㡣
  }
  
  bool findPath(BiNode* root, vector<int>& v, int data) {
      if (root == nullptr) {
          v.push_back(-1);
          return false;
      }
  
      v.push_back(root->val);
  
      if (root->val == data) {
          cout << "output-----"<< endl;
          std::copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
          return true;
      }
  
      if (!findPath(root->left, v, data)) {
          v.pop_back(); 
          if (!findPath(root->right, v, data)) {
              v.pop_back();
              return false;
          }
      }
      return true;
  }
  
  void findPath1(BiNode* root, int data, bool &finish) {
      // �κ�һ��·����finishΪtrue�ˣ�˵�����ҵ���֮�������·��ȫ��ֱ��return
      if (root == nullptr || finish == true) {
          return;
      }
  
      if (root->val == data) {
          finish = true;
          return;
      }
  
      findPath1(root->left, data, finish);
      findPath1(root->right, data, finish);
  }
  
  bool findPath2(BiNode* root, int data) {
      if (root == nullptr) {
          return false;
      }
      queue<BiNode*> _queue;
      _queue.push(root);
  
      while (!_queue.empty()) {
          BiNode* node = _queue.front();
          if (node->val == data) {
              cout << "find..." << node->val << endl;
              return true;
          }
          cout << node->val <<  " ";
          _queue.pop();
          if (node->left) {
              _queue.push(node->left);
          }
          if (node->right) {
              _queue.push(node->right);
          }
      }
      return false;
  }
  
  bool findPath3(BiNode* root, int data) {
      if (root == nullptr) {
          return false;
      }
      stack<BiNode*> _stack;
      _stack.push(root);
  
      while (!_stack.empty()) {
          BiNode* node = _stack.top();
          if (node->val == data) {
              cout << "find val..." << node->val << endl;
              return true;
          }
          cout << node->val << " ";
          _stack.pop();
          if (node->left) {
              _stack.push(node->left);
          }
          if (node->right) {
              _stack.push(node->right);
          }
      }
      return false; 
  }
  
  // ���Ŀ������������BFS��
  // ͨ������ʵ��
  // �����ڲ�α���
  void BFS(BiNode* root) {
      if (root == nullptr) {
          return;
      }
      queue<BiNode* > q;
      q.push(root);
      while(!q.empty()) {
          BiNode* node = q.front();
          for(int i=0;i<node->layer;i++) {
              cout << "==";
          }
          cout << node->val << endl;
          if (node->left) {
              node->left->layer = node->layer+1;
              q.push(node->left);
          }
          if (node->right) {
              node->right->layer = node->layer+1;
              q.push(node->right);
          }
          q.pop();
      }
  }
  
  // ����������ȱ�����DFS��
  // ͨ��ջʵ��
  // ����ǰ���������ջ��ʱ����push�ҽڵ㣬��push��ڵ㣩
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
  ������������BST = Binary Search Tree���Ĳ�����
  
  ����ڵ㣺
  1.����ǿ�����ֱ�Ӳ��룻
  2.�����գ������������������ʲ��Ҳ���λ�ã������½ڵ㣻������и�ֵ�򲻲��롣
  
  ���ҽڵ㣺
  1. ����ǿ�����ֱ�ӷ��أ�
  2. ������ǿ�����
     val���ڵ�ǰ�ڵ㣬����������������
     valС�ڵ�ǰ�ڵ㣬����������������
     ���������������̣�ֱ���ҵ�����Ϊnullptr��
  
  ɾ���ڵ㣺
  ���Ȳ���Ԫ���Ƿ��ڶ����������У���������ڣ��򷵻�, ����Ҫɾ���Ľ����ܷ��������������
  a. Ҫɾ���Ľ���޺��ӽ��-->ֱ��ɾ���ý��;
  b. Ҫɾ���Ľ��ֻ�����ӽ��-->ɾ���ý����ʹ��ɾ���ڵ��˫�׽��leftָ��ɾ���ڵ�����ӽ��
  c. Ҫɾ���Ľ��ֻ���Һ��ӽ��-->ɾ���ý����ʹ��ɾ���ڵ��˫�׽��leftָ��ɾ���ڵ���Һ��ӽ��
  d. Ҫɾ���Ľ�������Һ��ӽ��-->��������������Ѱ�������µĵ�һ�����(val��С)��������ֵ�����ɾ���ڵ��У���������ý���ɾ������
  */
  // �������������������
  BiNode* BSTInsert(BiNode* root, int val) {
      if (root == nullptr) {
          // ������ڵ�Ϊ�գ�ֱ�Ӳ��벢����
          BiNode* root = new BiNode(val);
          return root;
      } else {
          BiNode* node = root;  // ��ǰ�ڵ�
          while(node) {
              // ���������ֵС�ڵ�ǰ�ڵ��ֵ���������ߡ�
              if (val < node->val) {
                  if (node->left == nullptr) {
                      node->left = new BiNode(val);
                      break;
                  }
                  node = node->left;
              } 
              // ���������ֵ���ڵ�ǰ�ڵ��ֵ����������
              else if (val > node->val) {
                  if (node->right == nullptr) {
                      node->right = new BiNode(val);
                      break;
                  }
                  node = node->right;
              } else {
                  // �ҵ���ֱ�ӷ���
                  cout << "has set this val " << val << endl;
                  break;
              }
          } 
          return root; 
      }
  }
  
  // �����������Ĳ���
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
  
  // ������ԭ��ת���� leetcode-114
  // ����ı��ʾ��ǽ����нڵ��������Ϊ��
  void Tree2List(BiNode* root) {
      if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
          return;
      }
      if (root->left == nullptr && root->right != nullptr) {
          // ���û�����ӣ�ֱ�ӵݹ鴦����һ���ڵ�
          Tree2List(root->right);
      } else if (root->left != nullptr && root->right == nullptr) {
          // ��������ӣ�û���Һ��ӣ�����ڵ��ÿգ�Ȼ��ݹ鴦����һ���ڵ�
          root->right = root->left;
          root->left = nullptr;
          Tree2List(root->right);
      } else {
          // ���������ӣ������Һ��ӣ�����������ڵ�����ұ��Ǹ��ڵ�node
          // �����������ÿգ��������ҽڵ�ҵ�node�����ݹ鴦����һ���ڵ�
          BiNode* node = root->left;
          while (node->right) {
              node = node->right;
          }
          node->right = root->right;
          root->right = root->left;
          root->left = nullptr;
          Tree2List(root->right);
      }
  }
  
  /*
  ����������ת
  */
  class SolutionMirror {
  public:
      BiNode* mirrorTree(BiNode* root) {
          if (root == nullptr) {
              return nullptr;
          }
  
          BiNode* left = mirrorTree(root->left);
          BiNode* right = mirrorTree(root->right);
  
          root->right = left;
          root->left = right;
  
          return root;
      }
  };
  
  /*
  ���Ĳ�����⣺
  ������������������õݹ�ķ�ʽʵ�֣� Ҳ������BFS��α���
  1. ��������ĳһ��Ľڵ�
  2. �����������в�Ľڵ�
  3. ��������ĳһ���ж��ٽڵ�
  4. ��ӡÿ���һ���ڵ�����һ���ڵ�
  */
  
  // 1. ��������ĳһ��Ľڵ�
  void travelKlayerTree(BiNode* root, int level) {
      if (root == nullptr) {
          return;
      }
      if (level == 0) {
          cout << root->val << endl;
      }
      travelKlayerTree(root->left, level-1);
      travelKlayerTree(root->right, level-1);
  }
  
  // 2. �����������в�Ľڵ�
  void travelAllLayerTree(BiNode* root) {
      // �������ĸ߶ȣ��õ����еĲ�� treeHeight()
      for(int i=0; i<treeHeight(root);i++) {
          travelKlayerTree(root, i);
          cout << endl;
      }
  }
  
  // 3. ��������ĳһ���ж��ٽڵ�
  void travelKthCntTree(BiNode* root, int level, int & sum) {
      if (root == nullptr) {
          return;
      }
      if (level == 0) {
          sum += 1;
      }
      travelKthCntTree(root->left, level-1, sum);
      travelKthCntTree(root->right, level-1, sum);
  }
  
  // 4. ��ӡÿ���һ���ڵ�����һ���ڵ�
  /*
  ���Ĳ�α���BFS��ÿ�ΰ����Ľڵ�Ĳ����Ϣ��Ϊһ��pair push��queue�С�
  first����ֻ�ḳֵһ�Σ��±��ǲ�Σ�
  last�������¸�ֵȥ���һ�Σ��±�Ҳ�ǲ�Σ�
  
  ע�⣺������ʵ�ַ���
  ��һ��ʵ��˼·�� node��layer��Ϊһ��pair��push�������У�
  �ڶ���ʵ��˼·�� �ڵ�������һ�������ֶα�ʾ������Ϣlayer��
  */
  void firstAndLastTree(BiNode* root, vector<int> & first, vector<int> & last) {
      if (root == nullptr) {
          return;
      }
      queue<pair<BiNode*, int>> _q;
      _q.push(make_pair(root, 0));
      while (!_q.empty()) {
          pair<BiNode*, int> item = _q.front();
          BiNode* node = item.first;
          int level = item.second;
  
          if (level == first.size()) {
              first.push_back(node->val);      // ��ÿ���һ���ڵ㣬ֻ��ֵһ��
          } 
          if (level == last.size()) {
              last.push_back(node->val);       // ��ÿ�����һ���ڵ㣬���ϵĸ���ʽ��ֵ
          } else {
              last[level] = node->val;
          }
  
          _q.pop();
          if (node->left) {
              _q.push(make_pair(node->left, level+1));
          }
          if (node->right) {
              _q.push(make_pair(node->right, level+1));
          }
      }
  }
  
  
  
  int main() 
  {
      BiNode* root = createTree();
      // BFS(root);
      // Tree2List(root);
      // inOrderPrint(root);
  
      // SolutionMirror st;
      // BiNode* new_root = st.mirrorTree(root);
      // BFS(new_root);
  
      // travelKlayerTree(root, 1);
      // int sum = 0;
      // travelKthCntTree(root, 1, sum);
      // cout << "cnt" << sum << endl;
  
      vector<int> first, last;
      firstAndLastTree(root, first, last);
      copy(first.begin(), first.end(), ostream_iterator<int>(cout, " "));
      cout << endl;
      copy(last.begin(), last.end(), ostream_iterator<int>(cout, " "));
  
      system("pause");
      return 0;
  }
  ```

  

## ����������ֲ���

```c++
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

/*
���������������
·���ܺ͵��ڸ���Ŀ��͵�·��
�ҵ�����������ָ���ڵ������������ȣ�������� DFS��
������ԭ��ת����������� DFS��
����������ͼ��BFS��
leetcode-35  �����������Ҳ���λ�ã����ֲ��ң�
leetcode-34  ������ң������Ķ��ֲ��ң�
leetcode-33  ��ת���� �������Ķ��ֲ��ң�
leetcode-449 ������������������
leetcode-315 ������
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    int layer;           // �������Ĳ����Ϣ
    TreeNode(int x) : val(x), left(NULL), right(NULL), layer(0) {}
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

// ���������������
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
��ӡ�������������д������Ҵ�ӡ��ż���д��������ӡ
����˼·���������ڵ�������һ��������ԣ�
������BFS��α�����ͬʱ���²�����ԣ�ÿ��ڵ�׷�ӵ���Ӧ��vector�У�
ż����ԭ������������㷴�������
*/

vector<vector<int>> tree_BFS(TreeNode* root) {
    vector<vector<int>> res(10, vector<int>());

    queue<TreeNode* > q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        res[node->layer].push_back(node->val);
        q.pop();

        if (node->left) {
            node->left->layer = node->layer+1;
            q.push(node->left);
        }
        if (node->right) {
            node->right->layer = node->layer+1;
            q.push(node->right);
        }
    }
    return res;
}

/*
leetcode-113
������·����
����һ����������һ��Ŀ��ͣ��ҵ����дӸ��ڵ㵽Ҷ�ӽڵ�·���ܺ͵��ڸ���Ŀ��͵�·����
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
    //  ��Ҫ������leetcode��������ݽṹ���Լ�ʵ��˽�г�Ա������ͳ�Ƹ�·����
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
����Ĺ�������
����һ��������, �ҵ�����������ָ���ڵ������������ȡ�

����������ȶ��壺�������и��� T ��������� p��q��
����������ȱ�ʾΪһ����� x������ x �� p��q �������� x ����Ⱦ����ܴ�һ���ڵ�Ҳ���������Լ������ȣ�����

����˼·��
����p��·���ϵ�ÿһ���ڵ㶼��p�����ȣ�
����q��·���ϵ�ÿһ���ڵ㶼��q�����ȣ�
����p��q·���Ӻ���ǰ�ң���һ�������Ľڵ㼴Ϊ�������ȡ�
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
    // ����ڵ�p��q��·��
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
������ת����
����һ����������ԭ�ؽ���չ��Ϊ��������Ϊ������ǰ������Ľ����
˼·����������ȱ���(DFS) �ȼ��� ǰ�������
*/

class Solution114 {
public:
    void flatten(TreeNode* root) {
        // ���ڵ�Ϊ�ջ���ֻ��һ���ڵ�ʱ��ֱ�ӷ���
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
������������ͼ��
����һ�ö������������Լ�վ�������Ҳ࣬���մӶ������ײ���˳�򣬷��ش��Ҳ����ܿ����Ľڵ�ֵ��

˼·���������Ĳ�α�����������ȱ���BFS����ȡÿһ�����һ����
*/

class Solution199 {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        // ���ڵ�Ϊ�ջ���ֻ��һ���ڵ㣬��Ҫ���⴦��
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
�����������Ҳ���λ�ã�ʱ�临�Ӷ�o(logN)

˼·�����ֲ���
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
                // �ҵ�
                return mid;
            } else if (target < nums[mid]) {
                high = mid-1;
            } else {
                low = mid + 1;
            }
            
        }
        // �ҵ����mid��low��ۼ���һ��
        // ���target�����λ�ô��������ƶ�һ��λ�ã���ֱ֮�ӷ���low
        if ((low + high) / 2 == low && target > nums[low]) {
            low += 1;
        }
        return low;
    }
};

/*
leetcode-34
�������
����һ�������������е��������� nums����һ��Ŀ��ֵ target��
�ҳ�����Ŀ��ֵ�������еĿ�ʼλ�úͽ���λ�á�
�㷨ʱ�临�Ӷȱ����� O(log n) ����
��������в�����Ŀ��ֵ������ [-1, -1]��

˼·1:
���ֲ����ҵ�����һ�����������ģ�Ȼ�������ƶ�ȷ����˵㣬�����ƶ�ȷ���Ҷϵ㡣
�������������ᳬʱ��������

˼·2��
�����Ķ��ֲ����㷨
���ֲ����㷨��ֱ��ȷ��������������䡣

*/

class Solution34 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size()-1;
        vector<int> res;
        int left = -1, right = -1;
        
        // �����Ķ��ֲ��ң����Ҷ˵�
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
                // �ҵ�������һ��������Ҫ���������Ҳ���Ǹ�
                low = mid + 1;
            }
        }

        // �����Ķ��ֲ��ң�����˵�
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
                // �ҵ�������һ��������Ҫ���������Ҳ���Ǹ�
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
��ת����
���谴�����������������Ԥ��δ֪��ĳ�����Ͻ�������ת��
( ���磬���� [0,1,2,4,5,6,7] ���ܱ�Ϊ [4,5,6,7,0,1,2] )��
����һ��������Ŀ��ֵ����������д������Ŀ��ֵ���򷵻��������������򷵻� -1 ��
����Լ��������в������ظ���Ԫ�ء�
����㷨ʱ�临�Ӷȱ����� O(log n) ����

˼·�������Ķ��ֲ��ҷ���
��ͼ��֤��
���midС��high��˵��[mid, high]������ģ��ö��ֲ��ҷ�����target�Ƿ��ڸ����䡣���ڸ���������[low, mid]���䡣
���mid����high��˵��[low, mid]������ģ��ö��ֲ��ҷ�����target�Ƿ��ڸ����䡣
�����������һ�������ϲ��ö��ֲ��ҡ�ֱ������Ϊ0��
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
                // �Ҳ��������
                res = Bisearch(nums, mid + 1, high, target);
                if (res != -1) {
                    break;
                }
                // �Ҳ���˵��ֻ������������䣬����low/high����
                high = mid;
            } else if (nums[mid + 1] > nums[high]){
                // ����������
                res = Bisearch(nums, low, mid, target);
                if (res != -1) {
                    break;
                }
                // �Ҳ���˵��ֻ�������Ҳ����䣬����low/high����
                low = mid+1;
            } else {
                // �������
                // high=mid+1 ʣ��2��Ԫ��  1,3
                // high=mid+1 ʣ��3��Ԫ��  1,3,5
                if (nums[low] == target) res = low;
                if (nums[high] == target) res = high;
                if (nums[mid] == target) res = mid;
                // ������
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
������������������
���л��ǽ����ݽṹ�����ת��Ϊһϵ��λ�Ĺ��̣��Ա������Դ洢���ļ����ڴ滺�����У�
��ͨ������������·���䣬�Ա��Ժ���ͬһ������һ��������������ؽ���

���һ���㷨�����л��ͷ����л������������� �����л�/�����л��㷨�Ĺ�����ʽû�����ơ� 
��ֻ��ȷ�������������������л�Ϊ�ַ��������ҿ��Խ����ַ��������л�Ϊ����Ķ�����������

˼·��
���л��ȸ�������
�����л����򹹽���������������ֻҪȷ���˸��ڵ㣬�����Ķ�����������Ψһ�ģ�
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
        // �����������Ĳ���
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
            // ������ڵ�Ϊ�գ�ֱ�Ӳ��벢����
            TreeNode* root = new TreeNode(val);
            return root;
        } else {
            TreeNode* node = root;  // ��ǰ�ڵ�
            while(node) {
                // ���������ֵС�ڵ�ǰ�ڵ��ֵ���������ߡ�
                if (val < node->val) {
                    if (node->left == nullptr) {
                        node->left = new TreeNode(val);
                        break;
                    }
                    node = node->left;
                } 
                // ���������ֵ���ڵ�ǰ�ڵ��ֵ����������
                else if (val > node->val) {
                    if (node->right == nullptr) {
                        node->right = new TreeNode(val);
                        break;
                    }
                    node = node->right;
                } else {
                    // �ҵ���ֱ�ӷ���
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
������
����һ���������� nums����Ҫ�󷵻�һ�������� counts������ counts �и����ʣ� counts[i] ��ֵ��  nums[i] �Ҳ�С�� nums[i] ��Ԫ�ص�������

ʾ��:
����: [5,2,6,1] 
���: [2,1,1,0] 
����:
5 ���Ҳ��� 2 ����С��Ԫ�� (2 �� 1).
2 ���Ҳ���� 1 ����С��Ԫ�� (1).
6 ���Ҳ��� 1 ����С��Ԫ�� (1).
1 ���Ҳ��� 0 ����С��Ԫ��.
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
        int count;           // ������
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), count(0), left(NULL), right(NULL) {}
    };
};

int main() 
{
    TreeNode* root = createTree();
    // inOrderPrint(root);
    vector<vector<int>> res = tree_BFS(root);
    int index = 1;
    for(auto it = res.begin(); it != res.end(); it++,index++) {
        if (index % 2 == 0) {
            reverse(it->begin(), it->end());    
        }
        copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
        
        cout << endl;
    }

    // Codec cc;
    // string str = cc.serialize(root);
    // TreeNode* newroot = cc.deserialize(str);
    // inOrderPrint(newroot);

    // Solution315 st315;
    // vector<int> nums = {-1,-1};
    // vector<int> nixu = st315.countSmaller(nums);
    // std::copy(nixu.begin(), nixu.end(), ostream_iterator<int>(cout, " "));

    system("pause");
    return 0;
}
```