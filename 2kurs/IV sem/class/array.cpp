#include <array>
#include <iostream>

int main()
{
    constexpr int SIZE = 10;
    std::array<int, SIZE> arr //полностью выделяется в ствоем объекте
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };
    int arr2[SIZE];
    
    //прямые итераторы
    std::array<int, SIZE>::iterator i1 = arr.begin(); //вернет не константный итератор
    std::array<int, SIZE>::const_iterator i2 = arr.cbegin(); //вернет константный итератор
    //обратные итератоты
    std::array<int, SIZE>::reverse_iterator i3 = arr.rbegin(); //вернет не константный итератор
    std::array<int, SIZE>::const_reverse_iterator i4 = arr.crbegin(); //вернет константный итератор
    
    for (auto ii = arr.begin(); ii != arr.end(); ++ii) { //смысл: begin - указатель на начало массива, end - на конец
        std::cout << ++*ii << std::endl;
    }
    
    for (auto ii = arr.cbegin() + 2; ii != arr.cend() - 3; ++ii) { 
        std::cout << *ii << std::endl;
    }
    
    for (auto ii = arr.rbegin(); ii != arr.rend(); ++ii) { //смысл reverse: end - указатель куда-то за начало массива, begin - на конец
        std::cout << *ii << std::endl;
    }
    
    std::cout << "===" << std::endl;
    
    for (auto v : arr) {
        std::cout << v << std::endl;
    }
    
    for (const auto &v : arr) {
        std::cout << v << std::endl;
    }
    
    
}