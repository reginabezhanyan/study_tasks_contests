#include <iostream>
#include <iterator>
#include <vector>

void process(std::vector <long long> &mas, long long max)
{
    if(mas.size() == 0)
    {
        return;
    }
    std::vector <long long> :: iterator cnt = mas.end();
    cnt--;
    for(; cnt >= mas.begin(); cnt--)
    {
        if(*cnt >= max)
        {
            auto p = std::distance(mas.begin(), cnt);
            mas.push_back(*cnt);
            cnt = mas.begin();
            std::advance(cnt, p);
        }
    }
}

