/*  Грамматика 1го типа - неукорачивающая
    Язык L = {a^n0^mb^n1^m}, где n > 0, m > 0 
*/

#include <iostream>

int main()
{
    std::string buf;
    unsigned long long m, n, mt, nt;
    bool fl;
    while(std::cin >> buf) {
        n = m = nt = mt = 0; 
        fl = true;
        for(size_t i = 0; i < buf.size(); ++i) {
            std::cout << n << "  " << m << "  " << nt << "  " << mt << std::endl; 
            if(buf.at(i) == 'a') {
                if(!m) {
                    ++n;
                } else {
                    fl = false;
                    break;
                }
            } else if(buf.at(i) == '0') {
                if(n != 0) {
                    ++m;
                } else {
                    fl = false;
                    break;
                }
            } else if(buf.at(i) == 'b') {
                ++nt;
                if(!m || !n || (nt > n) || (mt != 0)) {
                    fl = false;
                    break;
                }  
            } else if(buf.at(i) == '1') {
                ++mt;
                if(!m || !n || (mt > m) || (nt != n)) {
                    fl = false;
                    break;
                }  
            } else {
                fl = false;
                break;
            }
        }
        if((mt != m) || (nt != n) || !m || !n) {
            fl = false;
        }
        std::cout << fl << std::endl; 
    }
}