#include <iostream>

using namespace std; 

int main() {     
    unsigned long long V;
    cin >> V;
    unsigned N;
    cin >> N;
    unsigned long long w[15]; 
    unsigned long long  sum = 0;
    for (unsigned i = 0; i < N; i++) {
        cin >> w[i];
        sum += w[i] + w[i];
    } 
    if(sum < V) {
        cout << "Impossible" << endl;
        return 0;
    }
    unsigned long long lim = 1;
    for(unsigned i = 0; i < N; i++) {
        lim *= 3;
    }
    unsigned result_num = N + N + 1; 
    for (unsigned gen = 1; gen < lim; gen++) { 
        unsigned long long cur = 0;
        unsigned cur_num = 0;
        unsigned t1 = gen; 
        for (unsigned bitnum = 0; t1 != 0; bitnum++) { 
            unsigned n = t1 % 3;
            cur += w[bitnum] * n;
            cur_num += n;
            t1 = t1 / 3;
        } 
        if(V == cur && cur_num < result_num) { 
            result_num = cur_num; 
        } 
    } 
    if(result_num < N + N + 1) {
        cout << result_num << endl;
    } else {
        cout << "Change" << endl;
    }
} 