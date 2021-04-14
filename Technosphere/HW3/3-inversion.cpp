#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

long long merge(long long *a, long long low, long long mid, long long high, long long *aux) {
    long long inv_count = 0;
    long long i,j;
    for (i = mid+1; i > low; i--) aux[i-1] = a[i-1];
    for (j = mid; j < high; j++) aux[high+mid-j]=a[j+1]; 
    for (int k = low; k <= high; k++) {
        if (aux[j] < aux[i]) {
            a[k] = aux[j--]; 
            inv_count += (mid - i + 1);
        } else {
            a[k] = aux[i++];  
        }
    }
    return inv_count;
}

long long mergeSort(long long a[], long long low, long long high, long long *aux) {
    long long inv_count = 0; 
    if(low < high) {
        long long mid = (low + high) / 2;
        inv_count = mergeSort(a, low, mid, aux);
        inv_count += mergeSort(a, mid+1, high, aux);
        inv_count += merge(a, low, mid ,high, aux);
    } 
    return inv_count;
}

long long sort_merge(long long *a, unsigned long long N) {
    long long *aux = new long long[N]; 
    long long ans = mergeSort(a, 0, N-1, aux); 
    delete [] aux;
    return ans;
}

int main() {
    unsigned long long N;
    cin >> N;
    long long *a = new long long[N];
    for(unsigned long long i = 0; i < N; ++i) {
        cin >> a[i];
    }
    cout << sort_merge(a, N) << endl; 
}