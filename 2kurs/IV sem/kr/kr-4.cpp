#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <algorithm>

class Figure {
public:
    virtual bool equals(Figure *fig) const = 0;
    virtual ~Figure(){}
};


class Rectangle: public Figure {
public:
    int a = 0;
    int b = 0;
    virtual bool equals(Rectangle *fig) const  {
        return (fig->a == a && fig->b == b);
    }
    Rectangle (int a_, int b_): a(a_), b(b_) {}
};

class Triangle: public Figure {
public:
    int a = 0;
    int b = 0; 
    int h = 0;
    virtual bool equals(Triangle *fig) const {
        return (fig->a == a && fig->b == b && fig->h == h);
    }
    Triangle (int a_, int b_, int h_): a(a_), b(b_), h(h_) {} 
}; 