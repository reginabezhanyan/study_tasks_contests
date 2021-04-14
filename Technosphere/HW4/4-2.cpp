#include <iostream>  

using namespace std;

int main() {
    unsigned K, N;
    cin >> K >> N; 
    
    double ans = 0;
    unsigned max = 0;
    unsigned tmp;
    for(unsigned i = 0; i < N; i++) {
        cin >> tmp;
        if(tmp > max) max = tmp;
        ans += (double) tmp / (double) K;
    }
    
    unsigned a = ans;
    
    if((double)a < ans) a++;
    
    if(a > max) max = a;
    
    cout << max << endl;
} 