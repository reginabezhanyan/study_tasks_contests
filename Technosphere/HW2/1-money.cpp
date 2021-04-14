#include <iostream>

using namespace std;

int main() {
    unsigned long long n;
    cin >> n;
    unsigned long long *w = new unsigned long long [n];
    unsigned long long sum = 0; 
    
    for(unsigned long long i = 0; i < n;i++) { 
        cin >> w[i];
    }
    
    for(unsigned long long i = 0; i < n;i++) { 
        if(w[i] > (sum + 1)) {
            cout << sum + 1 << endl;
            delete [] w;
            return 0;
        }
        sum += w[i];
    }
    
    cout << sum + 1 << endl;
    delete [] w;
}