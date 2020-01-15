#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
 
using namespace std;
 
int main() {
        std::string data = "1_2_3_4_5_6";
        std::stringstream ss(data);
        std::string item;
        cout << data << endl;
        while (std::getline(ss, item, '_')) 
            cout << item << ' ';  
        system("pause");
}