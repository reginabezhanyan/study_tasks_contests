#include <iostream>

/*
    S -> aAd
    A -> aAd | bB
    B -> bBc | c
*/

void B(int k, int m)
{
    if(k == m) {
        for(int i = 0; i < m; ++i) {
            std::cout << "b";
        }
        for(int i = 0; i < m; ++i) {
            std::cout << "c";
        }
        return;
    }
    m += 1;
    B(k, m);
}

void A(int k, int n)
{
    if(k - n > 1) {
        A(k, n + 1);
    }
    for(int i = 0; i < n; ++i) {
        std::cout << 'a';
    }
    B(k - n, 1);
    for(int i = 0; i < n; ++i) {
        std::cout << 'd';
    }
    std::cout << std::endl;
}

void S(int k, int n)
{
    A(k, 1);
}

int main() 
{
    int k;
    std::cin >> k;
    if(k % 2 == 0 && k > 3) {
        S(k/2, 0);
    }
}