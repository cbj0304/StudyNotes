#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

/*
高级数据结构：

trie树（字典树、前缀树）
trie树的优点：
利用字符串的公共前缀来减少存储空间与查询时间。


添加并查找单词
线段树
*/

#define TRIE_MAX_CHAR_NUM 26     // 考虑只存储26个小写英文字母

struct TrieNode {
    TrieNode *child[TRIE_MAX_CHAR_NUM];   // 指向下一个节点
    bool is_end;                          // 用于标识单词结尾
    TrieNode() : is_end(false) {
        for(int i=0; i<TRIE_MAX_CHAR_NUM; i++) {
            child[i] = nullptr;     // 如果其中一个孩子节点是字符'c'，则对应的下标为 'c'-'a' [0~26) 
        }
    }
};

/*
leetcode208
实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。

示例：
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 true
trie.search("app");     // 返回 false
trie.startsWith("app"); // 返回 true
trie.insert("app");   
trie.search("app");     // 返回 true
*/

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delTrie(root);
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *cur = root;
        for(int i=0; i<word.length();i++) {
            if (cur->child[word[i]-'a'] == nullptr) {
                TrieNode *node = new TrieNode;
                cur->child[word[i]-'a'] = node;
            }
            cur = cur->child[word[i]-'a'];
        }
        cur->is_end = true;

        // printTrie(root, 0);
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* cur = root;
        for(int i=0; i<word.length(); i++) {
            if (cur->child[word[i]-'a'] == nullptr) {
                return false;
            }
            cur = cur->child[word[i]-'a'];
        }
        return cur->is_end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* cur = root;
        for(int i=0; i<prefix.length(); i++) {
            if (cur->child[prefix[i]-'a'] == nullptr) {
                return false;
            }
            cur = cur->child[prefix[i]-'a'];
        }
        return true;
    }

    void printTrie(TrieNode* root, int layer) {
        if (root == nullptr) {
            return;
        }

        for(int i=0;i<TRIE_MAX_CHAR_NUM;i++) {
            if (root->child[i]) {
                for(int j=0; j<layer;j++) {
                    cout << "----";
                }
                cout << i + 'a' << "  ";
                if (root->is_end) {
                    cout << "[end]";
                }
                cout << endl;
                printTrie(root->child[i], layer+1);
            } 
        }
    }
    // 递归销毁一棵树
    void delTrie(TrieNode* root) {
        if (root == nullptr) {
            return;
        }

        for(int i=0; i<TRIE_MAX_CHAR_NUM;i++) {
            if (root->child[i]) {
                delTrie(root->child[i]);
            }
        }
        delete root;
    }
private:
    TrieNode *root;
};


/*
leetcode211
添加与搜索单词 - 数据结构设计
设计一个支持以下两种操作的数据结构：

void addWord(word)
bool search(word)

search(word) 可以搜索文字或正则表达式字符串，字符串只包含字母 . 或 a-z 。 . 可以表示任何一个字母。

示例：
addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
*/

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }

    ~WordDictionary() {
        delTrie(root);
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode* cur = root;
        for(int i=0; i<word.length(); i++) {
            if (cur->child[word[i]-'a'] == nullptr) {
                TrieNode* node = new TrieNode();
                cur->child[word[i]-'a'] = node;
            }
            cur = cur->child[word[i]-'a'];
        }
        cur->is_end = true;

        // cout << "print ==================" << endl;
        // PrintWordDictionary(root, 0);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        // 如果当前字符是. 就把所有的非nullchild加入curNodes
        vector<TrieNode*> curNodes; 
        vector<TrieNode*> curNodesTmp;
        curNodes.push_back(root);
        for(int i=0;i<word.length();i++) {
            cout << "***********" << word[i] -'a' << endl;
            curNodesTmp.clear();
            if (word[i] == '.') {
                for(int j=0; j<curNodes.size(); j++) {
                    TrieNode* cur = curNodes[j];
                    for (int k=0; k<TRIE_MAX_CHAR_NUM;k++) {
                        if (cur->child[k] != nullptr) {
                            curNodesTmp.push_back(cur->child[k]);
                        }
                    }
                }
            } else {
                for(int j=0; j<curNodes.size();j++) {
                    TrieNode* cur = curNodes[j];
                    if (cur->child[word[i] -'a'] != nullptr) {
                        curNodesTmp.push_back(cur->child[word[i] -'a']);
                    }
                }
            }
            curNodes.swap(curNodesTmp);
        }
        bool find_flag = false;
        for(int i=0; i<curNodes.size(); i++) {
            TrieNode* cur = curNodes[i];
            if (cur->is_end) {
                find_flag = true;
                break;
            }
        }
        return find_flag;
        
    }
    void delTrie(TrieNode *root) {
        if (root) {
            for(int i=0; i<TRIE_MAX_CHAR_NUM;i++) {
                delTrie(root->child[i]);          
            }
            delete root;
        }
    }
    void PrintWordDictionary(TrieNode *root, int layer) {
        if (root == nullptr) {
            return;
        }

        for(int i=0; i<TRIE_MAX_CHAR_NUM;i++) {
            if (root->child[i] != nullptr) {
                for(int i=0; i<layer;i++) {
                    cout << "---";
                }
                cout << i + 'a' << " ";
            }
        }
        cout << endl;
        if (root->is_end) {
            cout << "[end]" << endl;
        }

        for(int i=0; i<TRIE_MAX_CHAR_NUM;i++) {
            if (root->child[i] != nullptr) {
                PrintWordDictionary(root->child[i], layer+1);
            }
        }
    }
    void PrintNode(TrieNode *node) {
        cout << "&&&&&&& print node=>" << node << endl;
        for(int i=0; i<TRIE_MAX_CHAR_NUM;i++) {
            if (node->child[i] != nullptr) {
                cout << i+'a' << " ";
            }
        }
        cout << endl;
    }
private:
    TrieNode *root;
    
};

int main()
{
    // Trie trie;
    // trie.insert("apple");
    // trie.insert("app");
    // trie.insert("apeee");

    // cout << "search " << trie.search("apple") << endl;   // 返回 true
    // cout << "search " << trie.search("appcbj") << endl;     // 返回 false
    // cout << "startsWith " << trie.startsWith("app") << endl; // 返回 true
    // trie.insert("app");   
    // cout << "search " << trie.search("app") << endl;     // 返回 true

    WordDictionary wd;
    wd.addWord("bad"); 
    wd.addWord("dad");
    wd.addWord("mad");
    wd.addWord("pad");
    cout << wd.search("bad") << endl;
    cout << wd.search(".ad") << endl;
    cout << wd.search("b..") << endl;

    system("pause");
    return 0;
}