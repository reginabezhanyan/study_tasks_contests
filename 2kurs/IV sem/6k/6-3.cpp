#include <iostream>
#include <cmath>

namespace Game
{
    template<typename T>
    class Coord
    {
        public:
            typedef T value_type;
            T row, col;
            Coord(T row_ = T{}, T col_ = T{}) : row(row_), col(col_) {}     
    };
    
    template<typename T>
    T dist(Coord<T> size, Coord<T> p1, Coord<T> p2)
    { 
        T row = abs(p1.row - p2.row);
        T col = abs(p1.col - p2.col);
        T ans = row + col;
        if(p1.col % 2 == 0) {
            if(p1.row < p2.row) {
                ans -= std::min((col + 1) / 2, row);
            } else {
                ans -= std::min(col / 2, row);
            }
        } else {
            if(p1.row < p2.row) {
                ans -= std::min(col / 2, row);
            } else {
                ans -= std::min((col + 1) / 2, row);
            }
        }
        return ans;
    }
}