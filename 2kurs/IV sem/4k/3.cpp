#include <functional>
#include <vector>
#include <iterator>
#include <iostream>

template<typename T, typename S = typename std::iterator_traits<T>::value_type, 
        typename F, typename K = std::vector<std::reference_wrapper<S>>>
K myfilter2(T beg, T end, F f)
{
    K v;
    for(; beg != end; ++beg) {
        if(f(*beg)) {
            v.push_back(*beg);
        }
    } 
    return v;
}

template<typename T, typename F>
void myapply(T beg, T end, F f)
{
    for(; beg != end; ++beg) {
        f(*beg);
    }
}


int main()
{
    /*std::vector<int> v{-1,-2,-3,1,2,3};
    std::function<bool(int)> pred = [] (int x) -> bool { return x > 0;};
    auto k = myfilter2(v.begin(),v.end(),pred);
    for(auto it : k) {
        std::cout << it << std::endl;
    }
    myapply(k.begin(), k.end(), [] (int x) {std::cout << ++x << " ";});
    std::cout << std::endl;
    for(auto it : v) {
        std::cout << it << std::endl;
    }*/
    
    int v []{-1,-2,-3,1,2,3};
    std::function<bool(int)> pred = [] (int x) -> bool { return x > 0;};
    auto k = myfilter2(v, v + sizeof(v)/sizeof(*v),pred);
    for(auto it : k) {
        std::cout << it << std::endl;
    }
    myapply(v, v + sizeof(v)/sizeof(*v), [] (int x) {std::cout << ++x << " ";});
    std::cout << std::endl;
    for(auto it : v) {
        std::cout << it << std::endl;
    }
}

