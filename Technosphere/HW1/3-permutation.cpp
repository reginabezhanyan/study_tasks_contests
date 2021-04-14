#include <iostream>

using namespace std; 


int main() {
    unsigned N;
    cin >> N;
    unsigned long long M;
    cin >> M;
    unsigned mas[20];
    for(unsigned i = 0; i < N; i++) {
        mas[i] = i + 1;
    }
    unsigned long long tmp = 1;
    for(unsigned i = 2; i < N; i++) { //(N-1)!
        tmp *= i;
    } 
    for(unsigned i = 0; i < N - 1; i++) {  
        unsigned j = i + 1;
        while(M > tmp) {
            M -= tmp;
            mas[i] ^= mas[j];
            mas[j] ^= mas[i];
            mas[i] ^= mas[j];
            j++;
        }
        tmp /= (N - 1 - i); 
    }
    for(unsigned i = 0; i < N; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
}