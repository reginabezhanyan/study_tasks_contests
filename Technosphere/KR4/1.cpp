#include <iostream> 
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

int n_th(vector<int>& v, int k, int start, int end) {
    if (start == end) return v[k];   // Только один элемент
 
    int i = start, j = end, pivot = v[rand() % (j - i + 1) + i];

    for (; i < j;) {
        while (i < j && v[i] < pivot) ++i;

        while (i < j && v[j] >= pivot) --j;

        if (i < j) {
            int t = v[i];
            v[i] = v[j];
            v[j] = t;
            }
        } 
        
    if (k >= j) return n_th(v, k, j, end);
    else return n_th(v, k, start, j - 1);
 }

int main() {
    unsigned N;
    scanf("%u", &N); 
    vector<int> v;
    for(unsigned i = 0; i < N; i++) {
        int code, zn; 
        scanf("%d", &code);  
        if(code == 0) {
            scanf("%d", &zn); 
            v.push_back(zn); 
        } else if (code == 1){ 
            scanf("%d", &zn);  
            auto it = find(v.begin(),v.end(),zn);
            if(it != v.end()) {
                 v.erase(it); 
            }
        } else {
            int K = v.size();
            printf("%d\n", n_th(v, (K + 1)/2 - 1, 0, K - 1));  
        }
    }  
}