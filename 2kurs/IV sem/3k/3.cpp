#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

void print(std::vector <int> &v)
{
    int size = v.size();
    for(int i = 0; i < size; i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void process(const std::vector <int> &v1, std::vector <int> &v2)
{
    if(v2.size() == 0 || v1.size() == 0) {
        return;
    }
    int size = v2.size();
    std::vector <int> v1_copy(v1);
    std::sort(v1_copy.begin(), v1_copy.end());
    auto last = std::unique(v1_copy.begin(), v1_copy.end());
    auto first = v1_copy.begin();
    while((*first < 0) && (first != last)) {
        first++;
    }
    if(first == last) {
        return;
    }
    last--;
    auto p = v2.begin();
    for(int i = 0; i < size; i++) {
        if(*first != i) {
            *p++ = *(v2.begin() + i); //v2[i]
        } else {
            if(first != last) {
                first++;
            }            
        }  
    }
    v2.erase(p, v2.end());
}

int main()
{
    const std::vector <int> v1 = {0, 1, 2, 3, 3, 3, 3};
    std::vector <int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    process(v1,v2);
    print(v2);
}
