#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

namespace numbers
{
    class complex
    {
        double re_, im_;
    public:
        complex(double _re_ = 0, double _im_ = 0) : re_(_re_), im_(_im_) {}
        explicit complex(const std::string & s)
        {
            std::stringstream ss(s); 
            ss.ignore(s.length(), '(');
            ss >> re_;
            ss.ignore(s.length(), ',');
            ss >> im_;   
        };
        
        double re() const { return re_; }
        double im() const { return im_; }
        
        double abs2() const
        {
            return re_ * re_ + im_ * im_;
        }
        
        double abs() const
        {
            return sqrt(abs2());
        }
        
        std::string to_string() const
        {
            std::stringstream ss;
            ss << "(" << std::setprecision(10) << re_ << "," << im_ << ")";
            return ss.str();
        }
        
        const complex& operator += (const complex &v)
        {
            re_ += v.re_;
            im_ += v.im_;
            return *this;
        }
        
        const complex& operator -= (const complex &v)
        {
            re_ -= v.re_;
            im_ -= v.im_;
            return *this;
        }
        
        const complex& operator *= (const complex &v)
        {
            double re_tmp = re_ * v.re_ - im_ * v.im_;
            double im_tmp = im_ * v.re_ + re_ * v.im_; 
            re_ = re_tmp;
            im_ = im_tmp;
            return *this;
        }
        
        const complex& operator /= (const complex &v)
        {
            double re_tmp = (re_ * v.re_ + im_ * v.im_) / (v.re_ * v.re_ + v.im_ * v.im_);
            double im_tmp = (im_ * v.re_ - re_ * v.im_) / (v.re_ * v.re_ + v.im_ * v.im_);
            re_ = re_tmp;
            im_ = im_tmp;
            return *this;
        }
        
        complex operator ~() const
        {
            complex tmp(re_, -im_);
            return tmp;
        }
        
        complex operator -() const
        {
            complex tmp(-re_, -im_);
            return tmp;
        }
    };
    
    complex operator +(const complex &v1, const complex &v2)
    {  
        complex tmp(v1);
        tmp += v2;
        return tmp;
    }
    
    complex operator -(const complex &v1, const complex &v2)
    {  
        complex tmp(v1);
        tmp -= v2;
        return tmp;
    }
    
    complex operator *(const complex &v1, const complex &v2)
    {  
        complex tmp(v1);
        tmp *= v2;
        return tmp;
    }
    
    complex operator /(const complex &v1, const complex &v2)
    {  
        complex tmp(v1);
        tmp /= v2;
        return tmp;
    }
}