#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<long long> a, b;
    a.reserve(N);
    b.reserve(N);
    vector< pair< int, long long> > res;
    res.reserve(N);
    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < N; i++) {
        cin >> b[i];
    } 
    res[N - 1].first = N - 1;
    res[N - 1].second = b[N - 1]; 
    for(int i = N - 2; i >= 0; i--) {
        if(b[i] > res[i + 1].second) {
            res[i].first = i;
            res[i].second = b[i];
        } else {
            res[i].first = res[i + 1].first;
            res[i].second = res[i + 1].second;
        } 
    }  
    
    long long max = -9223372036854775807; 
    int i_a = 0, i_b = 0;
    for(int i = 0; i < N; i++) {
        long long sum = a[i] + res[i].second;
        if(sum > max) {
            max = sum;
            i_a = i;
            i_b = res[i].first;
        }
    }
    cout << i_a << " " << i_b << endl; 
}