#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

class Figure {
    public:
        Figure() {}
        virtual ~Figure() {}
        virtual double get_square(void) const = 0;
};


class Rectangle: public Figure
{
    double a;
    double b;
    public:
        Rectangle(double a_, double b_) : a{a_}, b{b_}
        { 
        }
        ~Rectangle() {}
        double get_square() const override { return a * b; }
        static Rectangle* make(const std::string &s) {
            std::istringstream ss(s); 
            double tmp1, tmp2;
            ss >> tmp1;
            ss >> tmp2;
            Rectangle *A = new Rectangle(tmp1, tmp2);
            return A;
        }
};

class Square: public Figure
{
    double a;
    public: 
        Square(double a_) : a{a_}
        { 
        }
        ~Square() {}
        double get_square() const override { return a * a;}
        static Square* make(const std::string &s) {
            std::istringstream ss(s); 
            double tmp;
            ss >> tmp;
            Square *A = new Square(tmp);
            return A;
        }
    
};

class Circle: public Figure
{
    double R;
    public: 
        Circle(double R_) : R{R_}
        { 
        }
        ~Circle() {}
        double get_square() const override { return R * R * M_PI;}
        static Circle* make(const std::string &s) {
            std::istringstream ss(s); 
            double tmp;
            ss >> tmp;
            Circle *A = new Circle(tmp);
            return A;
        }
};

