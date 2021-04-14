#include <iostream>
#include <cstdint>
#include <vector>

template<typename T1, class T2>
void func1(T1 a, T2 b)
{
    
}


template<typename T1, uint64_t val = 1024>
void func2(T1 a)
{
    int z[val];
}

enum class E
{
    A, B
};

template<typename T1, E e = E::A>
void func3(T1 a)
{
}

constexpr int *ff() { return nullptr; }

template<typename T1, int *val = ff()> //можно передавать указатель (int *val), если только параметр static
void func4(T1 a)
{
}

template<typename R, typename T>
auto my_cast(T a) -> R
{
    return R(a);
}

template<typename It, typename S = typename It::value_type>
auto sum(It beg, It end)
{
    //Разные варианты установки значения по умолчанию
    //typename It::value_type res = typename It::value_type();
    //auto res = typename It::value_type{};
    //typename It::value_type res{};
    S res{};
    for(; beg != end; ++beg) {
        res += *beg;
    }
    return res;
}

template<typename P>
auto sum2(const P* beg, const P* end)
{
    
    S res{};
    for(; beg != end; ++beg) {
        res += *beg;
    }
    return res;
}

int main()
{
    /*func2(2);
    func4(10);
    auto z = my_cast<double>(10);*/
    
    std::vector v1{1, 2, 3};
    
    std::vector<int>::value_type r = v1.front();
    decltype(v1)::value_type r1 = v1.front();
    
    decltype(v1) v2{v1}; //v2 определяется типом, который у v1
    auto v3{v1};
    
    std::vector<int> &v4{v1};
    const std::vector<int> &v5{v1};
    
    auto v6{v4};
    
    v6[0] = 100;
    std::cout << v1[0] << std::endl;
    
    decltype(v4) v7{v4};
    
    v7[0] = 100;
    std::cout << v1[0] << std::endl;
    
    std::cout << sum(v1.begin(), v1.end()) << std::endl;
    
    std::vector<std::string>v8{"a", "b", "c"};
    
    std::cout << sum(v8.begin(), v8.end()) << std::endl;
    
    std::vector v9{1000000000, 1000000000, 10000000000, 1000000000, 10000000000};
    std::cout << sum(v9.begin(), v9.end()) << std::endl;
    std::cout << sum<decltype(v9)::iterator, int64_t>(v9.begin(), v9.end()) << std::endl;
    
    std::vector v10 = {}
    
    
}