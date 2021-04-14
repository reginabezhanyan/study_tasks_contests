#include <iostream>

bool
add_overflow(int val1, int val2, int *res)  //лучше описать структуру
{
    return !__builtin_add_overflow(val1, val2, res);
}

struct MathResult //улучшить читаемость кода (типизированный pair)
{
    bool ok;
    int value;
};

MathResult
add_overflow(int val1, int val2)
{
    int res;
    bool flag = !__builtin_add_overflow(val1, val2, &res);
    return { flag, res };
}

std::pair<bool, int>
add_overflow_pair(int val1, int val2)
{
    int res;
    bool flag = !__builtin_add_overflow(val1, val2, &res);
    return { flag, res };
}

int main()
{
    int a, b;
    std::cin >> a >> b;
    
    int res;
    bool ovf = add_overflow(a, b, &res);
    
    auto r = add_overflow(a, b);
    
    std::cout << r.ok << " " << r.value << std::endl;
    
    if (auto [ ok, value ] = add_overflow(a, b); ok) {
        std::cout << "ok: " << value;
    }
    
    if (auto [ ok, value ] = add_overflow_pair(a, b); ok) {
        std::cout << "ok: " << value;
    }
}