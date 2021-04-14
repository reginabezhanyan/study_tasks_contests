#include <functional>
#include <iostream> 
#include <iterator>
#include <vector>

bool pred(int x)

{
    return x > 0;
}

template<typename T> 
T myfilter(const T &v, std::function<bool(const typename T::value_type &)> pred)
{
    T v2;
    auto itr = v.begin();
    while(itr != v.end()) {
        if(pred(*itr)) {
            v2.insert(v2.end(),*itr);
        }
        itr++;
    }
    return v2;
}

int main()
{
    const std::vector<int> v{0};
    const std::vector<int> v2 = myfilter(v, pred);
    for(auto i = v2.begin(); i != v2.end(); ++i) {
        std::cout << *i << std::endl;
    }
}