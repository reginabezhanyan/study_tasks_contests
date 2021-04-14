#include <iostream>
#include <cctype>

int main()
{
    std::string left, right;   
    bool non_inv = true;   
    bool r_auto = true;
    bool l_auto = true;
    bool r_line = true;
    bool l_line = true;
    bool eps = false;
    bool S = false; 
    bool f = true;
    while(std::cin >> left >> right) {
        size_t l_size = left.size();
        size_t r_size = right.size();
        if(l_size > r_size) {
            non_inv = false; 
        }
        if(right == "_") {
            eps = true;
            if(left != "S") {
                non_inv = false; 
                l_auto = false;
                r_auto = false;
            }
        } else {
            unsigned nt = 0;
            unsigned t = 0;
            for(size_t i = 0; i < r_size; ++i) {
                if(right[i] == 'S') {
                    S = true;
                }
                if(isupper(right[i])) {
                    if(t) {
                        l_line = false;
                        l_auto = false;
                    }
                    ++nt;
                } else {
                    if(nt) {
                        r_line = false;
                        r_auto = false;
                    }
                    ++t;
                }
            }
            if(nt > 1) {
                l_line = false;
                l_auto = false;
                r_line = false;
                r_auto = false;
            } 
            if(t != 1) {
                r_auto = false;
                l_auto = false;
            } 
            if(f && t == 0 && isupper(right[0]) && right[0] != 'S') {
                f = false;
                r_auto = true;
                l_auto = true;
            }
        } 
    }
    if(eps && S) {
        non_inv = false;
        r_auto = false;
        l_auto = false;
    }  
    if(!non_inv && !l_line && !r_line) {
        std::cout << "2" << std::endl;
    } else if(!l_line && !r_line) {
        std::cout << "21" << std::endl;
    } else if(l_line && !l_auto) {
        std::cout << "31" << std::endl;
    } else if(l_auto) {
        std::cout << "311" << std::endl;
    } else if(r_line && !r_auto) {
        std::cout << "32" << std::endl;
    } else if(r_auto) {
        std::cout << "321" << std::endl;
    } 
}