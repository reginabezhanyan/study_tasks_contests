#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <utility>

template<typename T1, typename S1 = typename std::iterator_traits<T1>::value_type, typename T2>
T2 myremove(T1 beg1, T1 end1, T2 beg2, T2 end2)
{
    if(beg1 == end1) {
        return end2;
    }
    std::vector<S1> v;
    for(auto c = beg1; c != end1; ++c) {
        v.push_back(*c);
    }
    std::sort(v.begin(), v.end());
    auto last = std::unique(v.begin(), v.end());
    auto first = v.begin();
    while((first != last) && (*first < 0)) {
        first++;
    }
    if(first == last) {
        return end2;
    }
    last--;
    auto p1 = beg2;
    for(auto p2 = beg2; p2 != end2; ++p2) {
        if(*first != std::distance(beg2, p2)) {
            *p1 = std::move(*p2);
            ++p1;
        } else {
            if(first != last) {
                first++;
            }            
        }  
    }
    return p1;
}