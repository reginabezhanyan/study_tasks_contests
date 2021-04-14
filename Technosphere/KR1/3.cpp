#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

unsigned f(unsigned n, unsigned i) {
  if (i == 0) return 1 + n - 1;
  if(n < 10) {
    unsigned y = 1 << (n-1); // 2^n-1 
    unsigned l = (1 << (n-1)) - 1;
    if (i < y) return f(n-1, i-1);
    else  return f(n-1, l - 1 - (i - y));
  } else {
    unsigned y = (1 << n);   
    unsigned l = (1 << n) - 2;
    if (i < y) return f(n-1, i - 2);
    else  return f(n-1, l - 1 - (i - y)); 
  }
}

int main() {
    unsigned n,m;
    
    cin >> n >> m;
    
    unsigned* ind = new unsigned [m];
    
    for (unsigned i = 0; i < m; i++) {
        cin >> ind[i];
    }
    
    for (unsigned i = 0; i < m; i++) {
        cout << f(n,ind[i] - 1) % 10 << endl;
    }
    cout << endl;
    delete [] ind;
}