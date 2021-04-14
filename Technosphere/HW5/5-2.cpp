#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

void reverse(char *t, unsigned n) {
    unsigned k = n / 2;
    for(unsigned i = 0; i < k ;i++) {
        char tmp = t[i];
        t[i] = t[n - 1 - i];
        t[n - 1 - i] = tmp;
    }
}

int main() {
    char *tmp = new char[10002]; 
    char *ans = new char[10002];
    char *t = new char[10002];
    scanf("%s", tmp);
       
    unsigned L = strlen(tmp);  
    unsigned i = 1, j = 0, i_ans = 0; 
    while (i < L) { 
        if(tmp[i] == '(') {
            i++;
            while(tmp[i] != ')') {
                t[j] = tmp[i];
                i++; j++;
            }
            t[j] = '\0';
            i++;
            if(tmp[i] == 'R') {
                reverse(t, j);
                i++;
            } 
            strcpy(ans + i_ans, t); 
            i_ans = j;
            j = 0;
            i++;
        } else {
            if(tmp[i] == 'R') {
                reverse(ans, strlen(ans));
            }
            i++;
        }
    }
 
    cout << ans << endl;
}