#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void sort_bubble(vector< pair< char, unsigned > > &a, int n) {
   bool sorted = false;
   while (!sorted) {
      sorted = true;
      for (int i = 0; i < n-1; i++) {
        if (a[i].second < a[i+1].second) {
           pair< char, unsigned > tmp = a[i];
           a[i] = a[i+1];
           a[i+1] = tmp;
           sorted = false;
        }
      }
    }
}

int main() {
    string buf;
    cin >> buf;
    vector< pair< char, unsigned > > res;
    res.reserve(26);
    
    for(unsigned i = 0; i < 26; i++) {
        res[i].first = 'A' + i;
        res[i].second = 0;
    }
    unsigned long long N = buf.length();
    for(unsigned long long i = 0; i < N; i++) {
        res[(int)(buf[i] - 'A')].second++;
    }
    
    sort_bubble(res, 26);
    
    for(unsigned i = 0; res[i].second != 0; i++) {
        cout << res[i].first << " " << res[i].second << endl; 
    }
    
}