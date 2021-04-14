#include <iostream> 
#include <string>

using namespace std;

unsigned  gcd(unsigned a, unsigned b) {
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return gcd(a % b, b);
    return gcd(a, b % a);
}

unsigned max(unsigned a, unsigned b) {
    if(a > b) return a;
    return b;
}

unsigned l_predper(unsigned M, unsigned *z) {
    unsigned p = 0, q = 0;
    while(M % 2 == 0) {
        p++;
        M /= 2;
    }
    while(M % 5 == 0) {
        q++;
        M /= 5;
    }
    *z = M;
    return max(p, q);
}

void ch(string &ans, unsigned k, unsigned *N, unsigned M){
    for(unsigned i = 0; i < k; i++) {
        *N *= 10;
        string tmp = to_string(*N / M);
        ans += tmp;
        *N %= M;
    }
}

int main() {
    unsigned N, M;
    string ans = "0.";
    cin >> N >> M;
    unsigned k = gcd(N, M);
    N /= k;
    M /= k;
    unsigned z = 0;
    unsigned predper = l_predper(M, &z);
    ch(ans, predper, &N, M); 
    unsigned per = 0;
    if(z != 1) {
        per++;
        unsigned cnt = 9;
        while((cnt = cnt % z)) { 
            per++;
            cnt = cnt * 10 + 9;
        }
        ans += "(";
        ch(ans, per, &N, M); 
        ans += ")";
    }
    
    cout << ans << endl;
}