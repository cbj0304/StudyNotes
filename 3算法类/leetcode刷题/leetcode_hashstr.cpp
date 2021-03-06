#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

/*
leetcode-409
最长回文串
给定一个包含大写字母和小写字母的字符串，找到通过这些字母构造成的最长的回文串。
在构造过程中，请注意区分大小写。比如 "Aa" 不能当做一个回文字符串。

思路：
主要是选字符，能配对的都选出来，如aa bb cc
然后如果还有剩余的字符，再选一个，因为中间位置的一个可以不对称。
*/

class Solution409 {
public:
    int longestPalindrome(string s) {
        map<char, int> mymap;
        for(size_t i=0; i<s.length(); i++) {
            mymap[s[i]]++;
        }
        int count = 0;
        bool left = false;
        for (size_t i=0; i<mymap.size(); i++) {
            if (mymap[i] % 2 == 0) {
                count += mymap[i];
            } else {
                count += mymap[i] - 1;
                left = true;
            }
        }
        count = left ? count+1 : count;
        return count;
    }
};

/*
leetcode-290
词语模式
给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。
这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 str 中的每个非空单词之间存在着双向连接的对应规律。

输入: pattern = "abba", str = "dog cat cat dog"  输出: true
输入:pattern = "abba", str = "dog cat cat fish" 输出: false
*/

class Solution290 {
public:
    bool wordPattern(string pattern, string str) {
        vector<string> v;
        string2vector(str, v);
        map<char, string> mymap;
        set<string> filt;

        if (pattern.size() != v.size()) {
            return false;
        }
        for(size_t i=0; i<pattern.size();i++) {
            
            if (mymap.find(pattern[i]) != mymap.end()) {
                if (mymap[pattern[i]] != v[i]) {
                    return false;
                }
            } else {
                // key没有出现过，但是val出现过了
                if (filt.find(v[i]) != filt.end()) {
                    return false;
                }
                mymap.insert(make_pair(pattern[i], v[i]));
            }
            filt.insert(v[i]);
        }
        return true;
    }
private:
    void string2vector(string& str, vector<string> & v) {
        stringstream ss(str);
        string item;
        while(std::getline(ss, item, ' ')) {
            v.push_back(item);
        }
    }
};

/*
leetcode-49
同字符词语分组
给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。
输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
*/
class Solution49 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> pmap;
        vector<vector<string>> result;
        for (auto it=strs.begin(); it != strs.end(); it++) {
            string tmp = *it;
            sort(tmp.begin(), tmp.end());
            pmap[tmp].push_back(*it);
        }
        for (auto it = pmap.begin(); it != pmap.end(); it++) {
            result.push_back(it->second);
        }
        return result;
    }
};

/*
leetcode-3
无重复最长子串
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

思路：双指针（滑动窗口）
固定一个指针的位置，向后移动另一个指针，当指针2指向的字符在窗口中存在时，移动指针1，改变窗口大小，同时记录子串的长度。
*/
class Solution3 {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() == 0) {
            return 0;
        }
        int maxLen = 0;
        int index1 = 0, index2 = 0;
        while(index2 <= s.length() - 1) {
            while(index2 < s.length() && !index2InWindow(s, index1, index2)) {
                index2++;
            }
            
            int tmpLen = index2 - index1;
            if (maxLen < tmpLen) {
                maxLen = tmpLen;
            }
            // 更改窗口边界
            index1 = newIndex1(s, index1, index2);        
        }
        return maxLen;
    }
private:
    // 判断index2指向的字符是否在窗口[index1, index2)上
    bool index2InWindow(string & s, int index1, int index2) {
        for (size_t i=index1; i<index2; i++) {
            if (s[i] == s[index2]) {
                return true;
            }
        }
        return false;
    }
    // 当index2再次出现在窗口内时，需要把窗口内index1指向第一个出现的index2字符之后
    int newIndex1(string & s, int index1, int index2) {
        for(size_t i=index1; i<index2; i++) {
            if (s[i] == s[index2]) {
                return i+1;
            }
        }
        return index1;
    }
};

/*
leetcode-187
重复的DNA序列
所有 DNA 都由一系列缩写为 A，C，G 和 T 的核苷酸组成，
例如：“ACGAATTCCG”。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。
编写一个函数来查找 DNA 分子中所有出现超过一次的 10 个字母长的序列（子串）。

输入：s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
输出：["AAAAACCCCC", "CCCCCAAAAA"]
*/

class Solution187 {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> res;
        if (s.length() < 10) {
            return res;
        }
        map<string, int> mymap;

        // 计算所有长度为10的子串
        for (size_t i=0; i<=s.length()-10;i++) {
            string sub = s.substr(i, 10);
            mymap[sub]++;
        }
        for (auto it = mymap.begin(); it !=mymap.end();it++) {
            if (it->second > 1) {
                res.push_back(it->first);
            }
        }
        return res;
    }
};

/*
leetcode-5
最长回文子串
给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

思路：回文串是关于中心对称的（如aba aa），所以需要用中心扩散法。

s = "babad"
b # a # b # a # d
每两个字符之间添加特殊字符 #
从每个字符从两边扩展，找最大的回文串。
*/

class Solution5 {
public:
    string longestPalindrome(string s) {
        
    }
};

/*
leetcode-76
最小窗口子串
给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。
输入: S = "ADOBECODEBANC", T = "ABC"
输出: "BANC"

思路：双指针（滑动窗口）-O(n)  注意：字符无序，可以用map。

index1=0, index2=0
1. t放到一个map中，map<char, int> t_map;
2. 何时移动index2？  当前窗口不全部包含t时
    每次移动index2，判断是否需要更新index1？ 每次移动index2，都需要判断是否需要移动index1
    index1所指字符不包含在t中；
    index1所指字符在t中，当前窗口中该字符数量足够了。
3.当前窗口满足条件时，更新最小字符串，窗口线性向前滑动，整体时间复杂度O(n)

*/

class Solution76 {
public:
    string minWindow(string s, string t) {

       
    }
};

/*
leetcode-131
分割回文串
给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
返回 s 所有可能的分割方案。
*/

class Solution131 {
public:
    vector<vector<string>> partition(string s) {
        
    }
};

int main()
{
    // Solution409 st409;
    // string str = "abccccdd";
    // cout << st409.longestPalindrome(str) << endl;

    // Solution290 st290;
    // string pattern = "abba";
    // string str = "dog cat cat dog";
    // cout << st290.wordPattern(pattern, str) << endl;

    // Solution49 st49;
    // vector<string> v = {"eat", "tea", "tan", "ate", "nat", "bat"};
    // vector<vector<string>> res = st49.groupAnagrams(v);

    // for (auto it=res.begin(); it!=res.end();it++) {
    //     vector<string> tmp = *it;
    //     for (auto itt = tmp.begin(); itt != tmp.end(); itt++) {
    //         cout << *itt << " ";
    //     }
    //     cout << endl;
    // }

    // Solution3 st3;
    // string s = "bbbbb";
    // cout << st3.lengthOfLongestSubstring(s) << endl;

    // Solution187 st187;
    // string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    // vector<string> res = st187.findRepeatedDnaSequences(s);
    // std::copy(res.begin(), res.end(), ostream_iterator<string>(cout, " "));

    Solution76 st76;
    string S = "ADOBECODEBANC", T = "ABC";
    cout << st76.minWindow(S, T) << endl;

    system("pause");
    return 0;
}