#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    unsigned long N, K;
    cin >> N >> K;
    vector<pair<unsigned long, unsigned long>> a; 
    unsigned long kof1 = 1, kof2 = 1, kof = 0;
    while(N / kof1 != 0) {
        kof1 *= 10; 
    }
    kof1 /= 10; 
    while(K / kof1 == 0) {
        K *= 10; 
    } 
    unsigned long pos = 0; 
    for(unsigned long long i = N; i >= 1; i--) {
        if(i % 10 == K % 10) {
            a.push_back(make_pair(i, i * kof2)); 
        } else if(i % 10 < K % 10) {
            pos++;
        }
        if((i / kof1 == 1) && (i % kof1 == 0)) {
            kof1 /= 10;
            kof2 *= 10;
        } 
    } 
    
    sort(a.begin(), a.end(), [](const pair< unsigned long, unsigned long > &a, 
                                    const pair< unsigned long, unsigned long > &b) { 
                                        return a.second < b.second; });
                                    
                               
    for(unsigned long i = 1; i <= N; i++) {
        if(a[i].first == K) {
            cout << i + pos << endl;
            return 0;
        }
    }
}