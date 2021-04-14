#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    double a;
    double sum = 0;
    int n = 0;
    double qr = 0; 
    double x = 0;
    while(std::cin >> a) {
        sum += a;
        n++;
        qr += a * a;
    }
    if (n > 0) {
        x = sum / n;
        qr = (qr - 2 * sum * x + n * x * x ) / n;
        qr = sqrt(qr);
        std::cout << std::setprecision(10) << x << std::endl;
        std::cout << std::setprecision(10) << qr << std::endl;
    }
    return 0;
}