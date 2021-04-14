#include <stdio.h>
#include <limits.h>

int
main(void)
{
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    c = a - a % b; 
    if (a < 0) {
        if (c + INT_MAX >= b && c - b - a > a - c) {
            c -= b;
        }
    } else {
        if (INT_MAX - c >= b && c + b - a <= a - c) {
            c += b;
        }
    }
    printf("%d\n", c);
    return 0;
}