#include <list>
#include <iostream>
#include <string>
#include <algorithm>

struct Data
{
    std::string x;
};

struct ListItem
{
    ListItem *prev{}, *next{};
    Data *elem;
}

struct List
{
    ListItem *first{}, *last{};
    size_t size; //since C++11
}

int main()
{
    std::list lst{1, 2, 3, 4};

    //std::next, std::prev, std::distance;
    lst.push_fint(3);
    for(auti x : lst) {
        std::cout << x << std::endl;
    }

    lst.front();
    lst.back();

    lst.size();

    //sort(lst.begin(), lst.end());
    lst.sort();


    std::list<Data> lst2;
    
}