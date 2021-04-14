#include <iostream>  
#include <vector>
#include <algorithm>

using namespace std;

unsigned check(vector< pair< unsigned, unsigned > > res, unsigned gen) { 
    unsigned cur = 0;
    for (unsigned bitnum = 1; gen != 0; bitnum++) {  
        if((gen & 1)) {
            for(unsigned i = 0; i < bitnum; i++) {
                if(res[bitnum].first > res[i].second) {
                    return 0;
                } else {
                    res[i].second -= res[bitnum].first; 
                }
            }
            cur++;
        } 
        gen >>= 1;
    } 
    return cur;
}

int main() {
    unsigned N;
    cin  >> N;
    vector< pair< unsigned, unsigned > > res;
    for(unsigned i = 0; i < N; i++) {
        unsigned tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        res.push_back(make_pair(tmp1, tmp2));   
    }
    
    sort(res.begin(), res.end(), [](const pair< unsigned, unsigned > &a, 
                                    const pair< unsigned, unsigned > &b) { 
                                    if(a.first != b.first) { return a.first > b.first;
                                    } else { return a.second > b.second; } });
     
 
    unsigned result = 0, tmp; 
    unsigned lim = 1u << (N - 1);
    for (unsigned gen = 1; gen < lim; gen++) {  
        if(result < (tmp = check(res, gen))) {
            result = tmp;
        } 
    }  
    cout << result + 1 << endl;
}