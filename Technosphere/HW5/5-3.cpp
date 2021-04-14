#include <iostream>
#include <map> 
#include <vector>
#include <string.h>
#include <algorithm>  
using namespace std;

int main() {
    unsigned N, L;
    cin >> N;
    map<vector<unsigned>, int> data;
    char *tmp = new char[10002];
    vector<unsigned> t;
    t.resize(26);
    
    for (unsigned i = 0; i < N; i++) {
        scanf("%s", tmp);
        if(i == 0){
            L = strlen(tmp); 
        }
        for(unsigned j = 0; j < L; j++) {
            t[tmp[j] - 'A']++;
        }
        if(data.find(t) != data.end()) {
            data[t]++;
        } else {
            data[t] = 0;
        }
        for(unsigned j = 0; j < 26; j++) {
            t[j] = 0;
        }
    }
    
    cout << data.size() << endl;
} 