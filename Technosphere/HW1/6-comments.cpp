#include <iostream> 
#include <string>

using namespace std;

unsigned min(unsigned a, unsigned b) { 
    if(a < b) return a;
    return b;
}
 
int main() {
    string s; 
    unsigned type1 = 0, type2 = 0, type3 = 0, type4 = 0; 
    bool pos1 = false, pos2 = false, pos4 = false;
    while(getline(cin, s)) {
        int length = s.size();
        for(auto i = 0; i < length; i++) {
            if(!pos1 && !pos2 && !pos4) {
                if(s[i] == '(' && i + 1 != length && s[i + 1] == '*') {
                    pos1 = true;
                } else if(s[i] == '{') {
                    pos2 = true;
                } else if(s[i] == '/' && i + 1 != length && s[i + 1] == '/') {
                    type3++;
                    break;
                } else if(s[i] == 39) {
                    pos4 = true;
                }
            } else if(pos1 && s[i] == '*' && i + 1 != length && s[i + 1] == ')') {
                type1++;
                pos1 = false;
            } else if(pos2 && s[i] == '}') {
                type2++;
                pos2 = false;
            }  else if(pos4 && s[i] == 39) {
                type4++;
                pos4 = false;
            }
            
        }
    }
    cout << type1 << " " << type2 << " " << type3 << " " << type4 << endl;
}