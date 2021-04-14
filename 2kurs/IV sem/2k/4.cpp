#include <iostream> 
#include <vector>
#include <cmath>

#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

int
main(int argc, char *argv[])
{ 
    numbers::complex C(argv[1]);
    double R;
    sscanf(argv[2], "%lf", &R);
    int N;
    sscanf(argv[3], "%d", &N);
    std::vector<std::string> args(argv + 4, argv + argc);
    numbers::complex I(0.0, 0.0);
    numbers::complex z1(C.re() + R, C.im());
    for(int i = 0; i < N; i++) {
        numbers::complex z2(C.re() + R * cos(M_PI * 2 * (i + 1) / N), C.im() + R * sin(M_PI * 2 * (i + 1) / N));
        I += (z1 - z2) * eval(args, z1);
        z1 = z2;
    }
    std::cout << I.to_string() << std::endl;
    return 0;
}