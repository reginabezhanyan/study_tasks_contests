#include <iostream>  
#include <vector>
#include <algorithm>

using namespace std;

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
     
    unsigned cnt = 0;
    unsigned sum_w = 0; 
    for(unsigned i = N - 1; i > 0; i--) {
        if(res[i].second >= sum_w) {
            sum_w += res[i].first;
            cnt++; 
        }
        if(res[0].second < sum_w){
            cnt--;
            break;
        }
    }
    cout << cnt + 1 << endl;
}