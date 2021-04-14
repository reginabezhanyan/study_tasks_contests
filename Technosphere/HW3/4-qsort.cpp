#include <iostream>
#include <stdio.h> 
#include <limits.h>

using namespace std; 
 
int main() {
    unsigned long long N, K, M, L;
    cin >> N >> K >> M >> L;
    unsigned *a = new unsigned[N];
    //clock_t start =  clock();
    a[0] = K;
    unsigned backet1[256] = {}; 
    unsigned backet2[256] = {}; 
    unsigned backet3[256] = {}; 
    unsigned backet4[256] = {}; 
    backet1[255 & a[0]]++;
    backet2[255 & (a[0]>>8)]++;
    backet3[255 & (a[0]>>16)]++;
    backet4[255 & (a[0]>>24)]++;
    for (unsigned long long i = 0; i < N-1; i++) {
        a[i+1] = (unsigned int)((a[i]*(unsigned long long)M)&0xFFFFFFFFU)%L;
        backet1[255 & a[i+1]]++;
        backet2[255 & (a[i+1]>>8)]++;
        backet3[255 & (a[i+1]>>16)]++;
        backet4[255 & (a[i+1]>>24)]++;
    }
    
    unsigned *b = new unsigned[N];   
    
    for(unsigned long long j = 1; j < 256; j++) {
        backet1[j] += backet1[j-1];
        backet2[j] += backet2[j-1];
        backet3[j] += backet3[j-1];
        backet4[j] += backet4[j-1];
    } 
    

    for(long long j = N - 1; j >= 0; j--) {
        b[--backet1[255 & a[j]]] = a[j]; 
    } 
    
    for(long long j = N - 1; j >= 0; j--) {
        a[--backet2[255 & (b[j]>>8)]] = b[j]; 
    } 
    
    for(long long j = N - 1; j >= 0; j--) {
        b[--backet3[255 & (a[j]>>16)]] = a[j]; 
    } 
    
    unsigned long long res = 0;
    for(long long j = N - 1; j >= 0; j--) { 
        res += b[j] * (((--backet4[255 & (b[j]>>24)]) + 1) & 1); 
    }  
    
    delete[] b;
     
    res %= L;
    
    delete[] a;
    cout << res << endl;
    
    //clock_t end = clock();
    //cout << ((double) end - start) / ((double) CLOCKS_PER_SEC) << endl;
}