#include <stdio.h>
#include <math.h>

int
main(int argc, char *argv[])
{
    int i;
    double x, per;
    double k = 100.0;
    sscanf(argv[1], "%lf", &x);
    for(i = 2; i < argc; i++){
        sscanf(argv[i], "%lf", &per);
        x += per / k * x ;
        x = round(x * 10000) / 10000;
    }
    printf("%.4lf\n", x);
    return 0;
}