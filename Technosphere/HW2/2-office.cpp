#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std; 

enum { 
    M = 60
};

 unsigned N;
    if(!scanf("%u", &N)) {
        return -1;
    }
    vector< pair< unsigned, unsigned > > res;
    for(unsigned i = 0; i < N; i++) {
        unsigned tmp1[3], tmp2[3];
        if(!scanf("%u:%u:%u", &tmp1[0], &tmp1[1], &tmp1[2])) return -1;
        if(!scanf("%u:%u:%u", &tmp2[0], &tmp2[1], &tmp2[2])) return -1;
        unsigned enter = tmp1[0] * M * M + tmp1[1] * M + tmp1[2];
        unsigned exit = tmp2[0] * M * M + tmp2[1] * M + tmp2[2] + 1;
        res.push_back(make_pair(enter, 0));
        res.push_back(make_pair(exit, 1));  
    }
    
    sort(res.begin(), res.end(), [](const pair< unsigned, unsigned > &a, 
                                    const pair< unsigned, unsigned > &b) { 
                                    if(a.first != b.first) { return a.first < b.first;
                                    } else { return a.second > b.second; } });
    unsigned ans = 0;
    unsigned cur = 0; 
    for(unsigned i = 0; i < N + N; i++) {
        if(res[i].second == 0) { 
            cur++;
            if(cur > ans) {
                ans = cur;
            } 
        } else {
            cur--;
        }  
    } 
    printf("%u\n", ans);
}