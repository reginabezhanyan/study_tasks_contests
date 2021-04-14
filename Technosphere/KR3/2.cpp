#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

bool prime(unsigned long long n) {
    for (unsigned long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main () {
    bool prosto[1000] = {};
	unsigned long long mas[100]= {};
	unsigned long long res = 0;
	unsigned long long N;
	vector<vector<unsigned long long>> solution; 
    
	for (unsigned i = 101; i < 1000; i++) {
		if (prime(i)){
			mas[i % 100]++;
			prosto[i]= true;
		}
	}
    
	scanf ("%llu",&N);
    
	solution.resize(N + 1);
	for (unsigned long long i = 0; i < N+1; i++) {
		solution[i].resize(100); 
	}
    
	for (unsigned j = 0; j < 100; j++) solution[3][j] = mas[j];
	for (unsigned long long i = 4; i <= N; i++) {
		for (unsigned long long j = 10; j < 100; j++) { 
			for (unsigned long long k = 1; k < 10; k++) {
				if (prosto[k*100+j]) solution[i][j] = (solution[i][j] + solution[i-1][k*10+j/10])%1000000009;
			}
		}
	} 
	for (unsigned i = 0; i < 100; i++){ 
        res = (res + solution[N][i])%1000000009;
    }
    
	printf ("%llu\n",res); 
}