#include <iostream>

namespace Sample {
    template<typename T, size_t s>
    class Rows {
        T r[s];
    public:
        Rows() {}
        T& operator[](size_t i) {
            return r[i];
        }
    };
    
    template<typename T, size_t x, size_t y>
    class Matrix {
        Rows<T, y> col[x];
    public:
        Matrix() {}
        Rows<T, y>& operator[](size_t i) {
            return col[i];
        }
    };
}