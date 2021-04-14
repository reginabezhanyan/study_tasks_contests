#include <iostream>

struct Range
{
    int min_{}, max_{};
    
    Range(int min, int max) : min_{min}, max_{max} {}
    
    int begin()
    {
        return min;
    }
    int end()
    {
        return nax;
    }
};