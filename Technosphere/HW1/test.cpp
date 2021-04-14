#include <iostream>
#include <ctime>
#include <vector>

using namespace std; 
 
int main() {
    unsigned int start_time =  clock(); // начальное время
     
    unsigned long long N;
    cin >> N;
    unsigned long long M;
    cin >> M; 
    unsigned long long fibo[2];
    fibo[0] = 0;
    fibo[1] = 1;
    for(unsigned long long i = 2; i <= N; i++) {
        fibo[i%2] = (fibo[0] + fibo[1]) % M;
    }
    cout << fibo[N%2] << endl;
     
    unsigned int end_time = clock(); // конечное время
    cout <<  (double) (end_time - start_time) / CLOCKS_PER_SEC << endl;
}