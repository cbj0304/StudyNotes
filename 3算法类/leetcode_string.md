# ���������ܽ�

## ���ݽṹ

* ��ϣ�����ַ���

  * ����Ĵ�
  * ����ģʽ
  * ͬ�ַ��������
  * ���ظ��ַ�����Ӵ�
  * �ظ���DNA����
  * ��С�����Ӵ�

  ```c++
  #include <iostream>
  #include <string>
  #include <cstdlib>
  #include <map>
  #include <sstream>
  #include <vector>
  #include <set>
  #include <algorithm>
  #include <iterator>
  #include <cstring>
  
  using namespace std;
  
  /*
  leetcode-409  ����Ĵ�
  leetcode-5    ������Ӵ�
  leetcode-290  �ַ����Ƿ����ĳһģʽ
  leetcode-49   ͬ�ַ��������
  leetcode-3    ���ظ���Ӵ�
  leetcode-187  �ظ���DNA����
  leetcode-76   ���� T ������ĸ����С�Ӵ�
  leetcode-131  �ָ���Ĵ�
  �����ַ�����������Ӵ�
  */
  
  /*
  leetcode-409
  ����Ĵ�
  ����һ��������д��ĸ��Сд��ĸ���ַ������ҵ�ͨ����Щ��ĸ����ɵ���Ļ��Ĵ���
  �ڹ�������У���ע�����ִ�Сд������ "Aa" ���ܵ���һ�������ַ�����
  
  ˼·��
  ��Ҫ��ѡ�ַ�������ԵĶ�ѡ��������aa bb cc
  Ȼ���������ʣ����ַ�����ѡһ������Ϊ�м�λ�õ�һ�����Բ��Գơ�
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
  �ַ����Ƿ����ĳһģʽ
  ����һ�ֹ��� pattern ��һ���ַ��� str ���ж� str �Ƿ���ѭ��ͬ�Ĺ��ɡ�
  ����� ��ѭ ָ��ȫƥ�䣬���磬 pattern ���ÿ����ĸ���ַ��� str �е�ÿ���ǿյ���֮�������˫�����ӵĶ�Ӧ���ɡ�
  
  ����: pattern = "abba", str = "dog cat cat dog"  ���: true
  ����:pattern = "abba", str = "dog cat cat fish" ���: false
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
                  // keyû�г��ֹ�������val���ֹ���
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
  ͬ�ַ��������
  ����һ���ַ������飬����ĸ��λ�������һ����ĸ��λ��ָ��ĸ��ͬ�������в�ͬ���ַ�����
  ����: ["eat", "tea", "tan", "ate", "nat", "bat"],
  ���:
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
  ���ظ���Ӵ�
  ����һ���ַ����������ҳ����в������ظ��ַ��� ��Ӵ� �ĳ��ȡ�
  
  ˼·��˫ָ�루�������ڣ�
  �̶�һ��ָ���λ�ã�����ƶ���һ��ָ�룬��ָ��2ָ����ַ��ڴ����д���ʱ���ƶ�ָ��1���ı䴰�ڴ�С��ͬʱ��¼�Ӵ��ĳ��ȡ�
  */
  class Solution3 {
  public:
      int lengthOfLongestSubstring(string s) {
          if (s.empty()) {
              return 0;
          }
          int start = 0, end=0;
          int max_len = 0;
          for(end=1; end<s.length();end++) {
              // ���i�ڴ�����û�г��ֹ���i++
              // i�ڴ����г��ֹ�������startΪ�ظ�Ԫ�ص���һ��Ԫ�أ�ͬʱ����max_len
              for(int j=start;j<end;j++) {
                  if (s[j] == s[end]) {
                      max_len = max<int>(max_len, end-start);
                      start = j+1;
                      break;
                  }
              }
          }
          return  max<int>(max_len, end-start);
      }
  };
  
  /*
  leetcode-187
  �ظ���DNA����
  ���� DNA ����һϵ����дΪ A��C��G �� T �ĺ�������ɣ�
  ���磺��ACGAATTCCG�������о� DNA ʱ��ʶ�� DNA �е��ظ�������ʱ����о��ǳ��а�����
  ��дһ������������ DNA ���������г��ֳ���һ�ε� 10 ����ĸ�������У��Ӵ�����
  
  ���룺s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
  �����["AAAAACCCCC", "CCCCCAAAAA"]
  */
  
  class Solution187 {
  public:
      vector<string> findRepeatedDnaSequences(string s) {
          vector<string> res;
          if (s.length() < 10) {
              return res;
          }
          map<string, int> mymap;
  
          // �������г���Ϊ10���Ӵ�
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
  ������Ӵ�
  ����һ���ַ��� s���ҵ� s ����Ļ����Ӵ�������Լ��� s ����󳤶�Ϊ 1000��
  
  ˼·�����Ĵ��ǹ������ĶԳƵģ���aba aa����������Ҫ��������ɢ����
  
  s = "babad"
  b # a # b # a # d
  ÿ�����ַ�֮����������ַ� #
  ��ÿ���ַ���������չ�������Ļ��Ĵ���
  */
  
  class Solution5 {
  public:
      string longestPalindrome(string s) {
          
      }
  };
  
  /*
  leetcode-76
  ��С�����Ӵ�
  ����һ���ַ��� S��һ���ַ��� T�������ַ��� S �����ҳ������� T ������ĸ����С�Ӵ���
  ����: S = "ADOBECODEBANC", T = "ABC"
  ���: "BANC"
  
  ˼·��˫ָ�루�������ڣ�-O(n)  ע�⣺�ַ����򣬿�����map��
  
  index1=0, index2=0
  1. t�ŵ�һ��map�У�map<char, int> t_map;
  2. ��ʱ�ƶ�index2��  ��ǰ���ڲ�ȫ������tʱ
      ÿ���ƶ�index2���ж��Ƿ���Ҫ����index1�� ÿ���ƶ�index2������Ҫ�ж��Ƿ���Ҫ�ƶ�index1
      index1��ָ�ַ���������t�У�
      index1��ָ�ַ���t�У���ǰ�����и��ַ������㹻�ˡ�
  3.��ǰ������������ʱ��������С�ַ���������������ǰ����������ʱ�临�Ӷ�O(n)
  
  */
  
  class Solution76 {
  public:
      string minWindow(string s, string t) {
  
         
      }
  };
  
  /*
  leetcode-131
  �ָ���Ĵ�
  ����һ���ַ��� s���� s �ָ��һЩ�Ӵ���ʹÿ���Ӵ����ǻ��Ĵ���
  ���� s ���п��ܵķָ����
  */
  
  class Solution131 {
  public:
      vector<vector<string>> partition(string s) {
          
      }
  };
  
  /*
  �������ַ�����������Ӵ��ĳ���
  https://www.cnblogs.com/chenleideblog/p/10457320.html
  */
  const int N=1024;
  int c[N][N];
  int maxLen=0,flag=0;
  char s1[N],s2[N];
  int len1,len2;
  void LCSs()
  {
      for(int i = 1; i <= len1; i++){
          for(int j = 1; j <= len2; j++){
              if(s1[i-1] == s2[j-1]){ //ע���˴���s1��s2�����Ǵ�s1[0]��s2[0]��ʼ��
                  c[i][j] = c[i-1][j-1] + 1;
                  if(c[i][j] > maxLen){
                      maxLen = c[i][j];
                      flag = j;   //ע���˴���flag��s2��Ѱ��Ӧ�ô�s2[flag-maxLen]-s2[flag-1]Ѱ��
                  }
              }
              else{
                  c[i][j] = 0;
              }
  
          }
      }
  }
  
  void LCSs_PRINT(int flag,int maxLen,int len2 )
  {
      if(flag==0 || maxLen==0){
          return;
      }
      for(int i = flag-maxLen; i < flag; i++){
          cout << s2[i];
      }
  }
  
  int main()
  {
      cout << "������X�ַ���" << endl;
      cin >> s1;
      cout << "������Y�ַ���" << endl;
      cin >> s2;
      len1 = strlen(s1);
      len2 = strlen(s2);
      for(int i = 0; i <= len1; i++){
          c[i][0] = 0;
      }
      for(int j = 0; j <= len2; j++){
          c[0][j] = 0;
      }
      LCSs();
      cout << "s1��s2������������еĳ����ǣ�" << maxLen <<endl;
      cout << "s1��s2��������������ǣ�";
      LCSs_PRINT(flag,maxLen,len2);
      return 0;
  }
  
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
  ```