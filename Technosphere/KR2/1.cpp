#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string buf;
    cin >> buf;
       
    auto it = buf.begin();
    int steck = 0, res = 0;
    while (it != buf.end() && (it + 1) != buf.end() && (it + 2) != buf.end()) {
        if (*it == '(' && *(it + 1) == 'b' && *(it + 2) == ',') {
            it += 3;
            steck = 1;
            while ((it != buf.end()) && (steck != 0)) {
                if (*it == 'w') {
                    res++;
                } else if (*it == '(') {
                    steck++;
                } else if (*it == ')') {
                    steck--;
                }
                it++;
            }
        } else {
            it++;
        }
    }
    
    cout << res << endl;
    
    return 0;
    
}