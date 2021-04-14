#include <iostream>
#include <vector>

void process (std::vector<uint64_t>  &v, uint32_t s)
{
    if (v.size() == 0 || v.size() < s){
        return;
    }
    uint32_t i = 1;
    uint64_t sum = 0;
    auto ptr = v.begin();
    for (;ptr != v.end(); ++i, ++ptr) {
        sum += *ptr; 
        if (i == s) {
            ptr++;
            ptr = v.insert(ptr, sum);
            i = 0;        
        } 
        
    }
    return;
} 