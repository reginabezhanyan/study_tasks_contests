#include <iostream>
#include <cmath>

int main()
{
    int m,n, r1, c1, r2, c2;
    std::cin >> m >> n;
    
    while(std::cin >> r1 >> c1 >> r2 >> c2) {
        int row = std::min(std::min(abs(r1 - r2), r1 + m - r2), r2 + m - r1);
        int col = std::min(std::min(abs(c1 - c2), c1 + n - c2), c2 + n - c1);
        std::cout << row + col << std::endl;
    }
}