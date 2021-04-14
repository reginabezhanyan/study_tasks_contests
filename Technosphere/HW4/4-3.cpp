#include <iostream>
#include <map> 
#include <vector>
#include <stdio.h>
#include <ctime>
#include <cassert>

using namespace std;

clock_t start; 

void build(vector<unsigned>&tree, unsigned n) {     
    for (unsigned i = n - 1; i >= 1; i--) 
        tree[i] = tree[2 * i] ^ tree[2 * i + 1]; 
}  

void update(vector<unsigned>& tree, unsigned pos, unsigned value, unsigned n) {  
    pos += n;  
    tree[pos] = value; 
  
    while(pos > 1) {  
        pos >>= 1;  
        tree[pos] = tree[2 * pos] ^ tree[2 * pos + 1];  
    } 
}  

unsigned xxor (vector<unsigned>& tree, unsigned l, unsigned r, unsigned n) { 
	l += n;
    r += n;
    unsigned ans = 0;
    
    while(l <= r) {
        if(l % 2 != 0) ans ^= tree[l];
        if(r % 2 == 0) ans ^= tree[r];
        l = (l + 1) / 2;
        r = (r - 1) / 2; 
    }
    return ans;
}

int main() {
    unsigned N, M;
    cin >> N >> M; 
    vector<int> ans; 
    
    vector<unsigned> t; //дерево отрезков
    t.reserve(4*N);
    
    for(unsigned i = 0; i < N; i++) {
        scanf("%u", &(t[N + i]));
    }
    
    start = clock();
    build(t, N);
      
    for(unsigned i = 0; i < M; i++) {
        unsigned code, p1, p2; 
        scanf("%u%u%u", &code, &p1, &p2);
        if(code == 1) { 
            ans.push_back(xxor(t, p1, p2, N));
        } else { 
            update(t, p1, p2, N); 
        }
    } 
    
    unsigned k = ans.size();
    for(unsigned i = 0; i < k; i++) {
        xout << ans[i] << endl;
        //assert(((double) (clock() - start) / ((double) CLOCKS_PER_SEC)) < 0.9);
    } 
    
    ans.clear();
    t.clear(); 
} 