#include <stdio.h> 

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

int main() {
    unsigned N; 
    unsigned a, b; 
    char buf[30];
    char *t = NULL;
    t = fgets(buf, 30, stdin); 
    sscanf(t, "%u", &N);
    t = fgets(buf, 30, stdin); 
    sscanf(t, "%u", &a);
    unsigned res = 0;
    for(unsigned i = 1; i < N; ++i) {
        t = fgets(buf, 30, stdin); 
        sscanf(t, "%u", &b);
        if(a % 2 == 0 && b % 2 == 0) {
            ++res;
        } else if (gcd(a, b) > 1) {
            ++res;
        }
        a = b;
    }
    printf("%u\n", res);
}