#include <iostream>
#include <iomanip>
#include <cmath>

struct A
{
    A(int a) {}
};

struct B
{
    B(const A& b) {}
};


int main()
{
    B b{1}; //компилируется 1 -> A(int) -> B(const A&)
    //B c = 1; не компилируется 1 -> A(int) -> B(const A&) -> B(const B&) - 2 пользовательских конструктора запрещены
}

/* что можно делать 
   тождественные преобразования (высокий приоритет)
   int[] -> int*
   func() -> (*)()
   T <-> T
   const T & <-> T
   T* -> const T*
   T& -> const T&
   
   стандартные преобразования
   promotions
   char -> int
   short -> int
   float -> double
   
   Приоритет ниже, чем у promotions
   char <-> long
   long <-> double
   float <->
   
   Пользовательские (user-defined)
   A -> B
   stand -> A -> B
   A -> B -> stand
   stand -> A -> B -> stand
   
   ellipsis (...)
   
   void f(int);
   void f(long long);
   unsigned int u;
   f(u); //неоднозначность (равнозначные преобразоваения)
   
   Программа на С++:
   1. анализ
   2. оптимизация
   3. выполнение
   
*/



/* double rand(); для компилятора имеют одного декарирование - нельзя
   int rand();
   При преобразовании с типу bool контекст учитывается
*/