#include <iostream>

class Complex
{
    //constexpr static double PI = 4; //constexpr (только конст компиляции) только со static, лучше const (он связан с памятью, кот. нельзя изменять; конс компиляции в С++)
    
    //inline int wun = 10;
    
    double re_ = 0, im_ = 0;

public:    
    double re() const { return re_; }; //const Complex * const
    void set_re(double);
    
    //static int count_;
    
    //static int count() { return count_ + Complex::re_; }
};

void Complex::set_re(double re_)
{
    //this->re_ = re_; Скрытый параметр this - в данном случае Complex * const
    Complex::re_ = re_;
}

int Complex::count_ = 100500;

int main(int argc, const char * argv[])
{
    const Complex v1;
    Complex v2;
    
    Complex::count_ = 0;
    
    std::cout << v1.re() << std::endl;
    v2.set_re(1.1);
    std::cout << v2.re() << std::endl;
     
}