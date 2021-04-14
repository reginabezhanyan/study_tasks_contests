#include <iostream>

class A
{
    A() = default;
    A(const A&) = default; //явное включение конструктора по умолчанию для копирования
    
};

class Complex
{ 
    double re_ = 0, im_ = 0;

public: 
    Complex() = default; //явное включение конструктора по умолчанию
    //Complex() = delete; //компилятор откажется компилировать конструктор по умолчанию (явное отключение конструктора по умолчанию)
    
    //**делигирующий конструктор
    explicit Complex(double re_) : re_(re_) //explicit - запрящает неявные преобразования
    {    
    }
    Complex(double re_, double im_) : re_{re_}, im_{im_}
    {  
    }
    
    /*Complex(double re_, double im_)
    { //присваивание, лучше инициализация
        Complex::re_ = re_;
        Complex::im_ = im_;
    }*/
    
    //**списки инициализации
    /*Complex(double re_, double im_) : re_{re_}, im_{im_}
    { //инициализация 
    }*/
    
    double re() const { return re_; }; //const Complex * const
    void set_re(double);
    
    double im() const { return im_; }; //const Complex * const
    void set_im(double im_) { this->im_ = im_; };
};

void Complex::set_re(double re_)
{
    //this->re_ = re_; Скрытый параметр this - в данном случае Complex * const
    Complex::re_ = re_;
} 

void func(Complex arg) 
{
    std::cout << arg.re() << std::endl;
}

int main(int argc, const char * argv[])
{
    const Complex v1;
    Complex v2;
     
    std::cout << v1.re() << std::endl;
    v2.set_re(1.1);
    std::cout << v2.re() << std::endl;
    
    Complex v3{1, 2};
    Complex v4(3, 4);
    [[maybe_unused]]
    Complex v5 = Complex(6, 7.3);
    
    Complex v6 = Complex{1};
    func(Complex{3});
}