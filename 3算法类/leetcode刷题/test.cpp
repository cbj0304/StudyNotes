#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <iterator>
#include <map>
#include <algorithm>
#include <set>
#include <regex>
#include <queue>
#include <cmath>

using namespace std;

struct mygreater {
    bool operator () (const pair<int, int> & left, const pair<int, int> & right) {
        if (left.first == right.first) {
            return left.second >= right.second;
        } else {
            return left.first >= right.first;
        }
    }
};

void string2vect(string & num, vector<int> & vec) {
    for(int i=0; i<num.length();i++) {
        int data = num[i] - '0' + 0;
        vec.push_back(data);
    }
}

void vect2string(string & num, vector<int> & vec) {
    for(auto it=vec.begin(); it!=vec.end();it++) {
        num += *it - 0 + '0'; 
    }
}

int main() 
{
    string s = "123";
    s = s + "#";
    cout << s << endl;
    s.pop_back();
    cout << s << endl;
    system("pause");
    return 0;
}

