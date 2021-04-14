/*  Грамматика 1го типа - неукорачивающая (КЗ)
    Язык L = {a^n0^mb^n1^m}, где n > 0, m > 0 
    S -> AB
    A -> aAT | aT
    B -> 0B1 | 01
    Tb -> bb
    T1 -> b1
    T0 -> 0T
*/

#include <iostream>

bool ch_gr(std::string buf) {
    unsigned long long m = 0;
    unsigned long long n = 0;
    unsigned long long mt = 0;
    unsigned long long nt = 0;
    unsigned long long size = buf.size();
    unsigned long long i = 0; 
    while((i < size) && (buf[i] == 'a')) {
        ++i;
        ++n;
    }
    if(!n) {
        return false;
    }
    while((i < size) && (buf[i] == '0')) {
        ++i;
        ++m;
    }
    if(!m) {
        return false;
    }
    while((i < size) && (buf[i] == 'b')) {
        ++i;
        ++nt;
    }
    if(n != nt) {
        return false;
    }
    while((i < size) && (buf[i] == '1')) {
        ++i;
        ++mt;
    }
    if((m != mt) || (i < size)) {
        return false;
    }
    return true;
}

int main()
{
    std::string buf;
    while(std::cin >> buf) { 
        std::cout << ch_gr(buf) << std::endl; 
    }
}