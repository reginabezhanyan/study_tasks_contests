#include <iostream>
#include <cmath>

template<typename T>
class Coord
{
    public:
        typedef T value_type;
        T row, col;
        Coord(T row_ = T{}, T col_ = T{}) : row(row_), col(col_) {}     
};

template<typename T>
T dist(Coord<T> size, Coord<T> point1, Coord<T> point2)
{
    T m = size.row;
    T n = size.col;
    T r1, r2, c1, c2;
    if(point1.row > point2.row) {
        r1 = point1.row;
        r2 = point2.row;
    } else {
        r2 = point1.row;
        r1 = point2.row;
    }
    
    if(point1.col > point2.col) {
        c1 = point1.col;
        c2 = point2.col;
    } else {
        c2 = point1.col;
        c1 = point2.col;
    }
    T row = std::min(std::min(r1 - r2, r1 + m - r2), r2 + m - r1);
    T col = std::min(std::min(c1 - c2, c1 + n - c2), c2 + n - c1);
    return std::max(row, col);
}


