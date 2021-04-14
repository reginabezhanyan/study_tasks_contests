#include <iostream>
#include <iterator>
#include <vector>

void process(const std::vector <unsigned long long> &mas, std::vector <unsigned long long> &l, unsigned int h)
{
    if(l.size() == 0)
    {
        return;
    } 
    auto it = l.end();
    it--;
    for (auto iter = mas.cbegin(); iter < mas.cend(); iter += h, --it)
    {
        *it += *iter; 
        auto dis = std::distance(iter, mas.cend());
        if((it == l.begin()) || (dis <= static_cast<decltype(dis)>(h)))
        { 
            break;
        }
        
    }
} 