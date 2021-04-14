#include <iostream>
#include <set> 

using namespace std;

int main() {
    unsigned N;
    cin >> N;
    
    multiset<unsigned long long> t;
    unsigned long long tmp;
    for(unsigned i = 0; i < N; i++) {
        cin >> tmp;
        t.insert(tmp); 
    }
    
    double ans = 0; 
    auto it1 = t.begin(), it2 = t.begin(); 
    it2++;
    while(it2 != t.end()) {
        unsigned long long tmp = *it1 + *it2;
        ans += tmp / 100.0;
        t.erase(it1);
        t.erase(it2);
        t.insert(tmp);  
        it1 = t.begin(); 
        it2 = t.begin();
        it2++;
    }
    
    cout << ans << endl;
}