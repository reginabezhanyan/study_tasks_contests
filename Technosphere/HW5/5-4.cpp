#include <iostream> 
#include <vector>
#include <stdio.h>

using namespace std;

struct node {
    node *next[2];      
    unsigned sc;
    
    node() {
        for (int i = 0; i < 2; i++) {    
            next[i] = nullptr;           
        } 
        sc = 0;
    }
};

node *root = new node();     //корневая вершина бора, соответствующая пустой строке.

void add(unsigned num) {  
    node *cur_v = root;     //текущая вершина

    for (unsigned i = 0; i <= 31; i++) {
        unsigned k = 1 & (num >> (31 - i)); 
        if (cur_v->next[k] == nullptr) {
            cur_v->next[k] = new node();
        }
        
        cur_v = cur_v->next[k]; 
        cur_v->sc++;
    }

}

bool find(unsigned num) { 
    
    node *cur_v = root;     //текущая вершина

    for (unsigned i = 0; i <= 31; i++) {
        unsigned k = 1 & (num >> (31 - i));
        cur_v = cur_v->next[k]; 
        if (cur_v == nullptr || cur_v->sc < 1) {
            return false;
        }  
    } 
    return true;
} 

void del(unsigned num) { 
    node *cur_v = root;     //текущая вершина

    for (unsigned i = 0; i <= 31; i++) {
        unsigned k = 1 & (num >> (31 - i));
        cur_v = cur_v->next[k];
        cur_v->sc--;
    }  
}

unsigned find_max(unsigned ind, unsigned N) { 
    unsigned ans = 0;
    node *cur_v = root;
    max = N;
    for (unsigned i = 0; i <= 31; i++) {
        if(cur_v->next[1] != nullptr) {
            if(cur_v->next[0] == nullptr) {
                cur_v = cur_v->next[1];
                ans = (ans << 1) + 1;
            } else {
                unsigned src;
                src = max - cur_v->next[1]->sc;
                if(ind < src) {
                    cur_v = cur_v->next[0];
                    ans <<= 1;
                    max = src;
                } else {
                    cur_v = cur_v->next[1];
                    ans = (ans << 1) + 1;
                }
            } 
        } else {
            cur_v = cur_v->next[0];
            ans <<= 1;
        }
    }   
    return ans;
}

int main() {
    unsigned N;
    scanf("%u", &N);
    vector<unsigned> ans; 
    for(unsigned i = 0; i < N; i++) {
        unsigned code, zn; 
        scanf("%u%u", &code, &zn);  
        if(code == 1) { 
            if(!find(zn)) {
                add(zn); 
                N++;
            } 
        } else if (code == 2){ 
            if(find(zn)) {
                del(zn);
                N--;
            } 
        } else {
            ans.push_back(find_max((N + 1)/2, N)));
        }
    } 
    
    unsigned k = ans.size();
    for(unsigned i = 0; i < k; i++) {
        printf("%u\n", ans[i]); 
    } 
    
    ans.clear();
}
