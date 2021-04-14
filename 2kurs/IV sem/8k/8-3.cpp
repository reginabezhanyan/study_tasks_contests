#include <iostream>

int main()
{
    std::string left, right; 
    bool n = false;
    bool t_l = true;
    bool n_S = false;
    bool con_free = true;
    bool non_inv = true; 
    bool S_r = false;
    unsigned long long eps = 0;
    while(std::cin >> left >> right) {
        n = true;
        size_t l_size = left.size();
        size_t r_size = right.size();
        if(l_size > r_size) {
            non_inv = false;
        }
        if(l_size == 1) {
            if(!isupper(left.at(0))) {
                con_free = false;
            } else if (left.at(0) == 'S'){
                n_S = true;
            }
        } else {
            con_free = false;
        }
        t_l = false;
        for (size_t i = 0; i < l_size; i++) {
            if(isupper(left.at(i))) {
                t_l = true;
                break;
            } 
        }
        if((right.at(0) == '_')) {
            ++eps;
            if(!(left.at(0) == 'S')) {
                non_inv = false;
            }
        }
        for (size_t i = 0; i < r_size; i++) {
            if(right.at(i) == 'S') {
                S_r = true;
            }
        }
    }
    if((eps > 1) || ((eps == 1) && S_r)) {
        non_inv = false;
    }
    
    if(n && t_l && n_S) {
        if(con_free) {
            if (non_inv) {
                std::cout << "23" << std::endl;
            } else {
                std::cout << "2" << std::endl;
            }
        } else {
            std::cout << "10" << std::endl;
        }
    } else {
        std::cout << "-1" << std::endl;
    }
}