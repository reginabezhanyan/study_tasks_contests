#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <new>

#include "regina_complex.h"
#include "regina_stack.h"

using namespace numbers;

int main()
{
    complex_stack st;
    //st.print();
    complex a(1.2,2.1), b(4.9, 2.5); 
    st = st << a << b;
    std::cout << st.size() << " " << (+st).to_string() << std::endl;
    st = ~st;
    std::cout << st.size() << " " << (+st).to_string() << std::endl;
    std::cout << st.size() << " " << st[0].to_string() << std::endl;
}