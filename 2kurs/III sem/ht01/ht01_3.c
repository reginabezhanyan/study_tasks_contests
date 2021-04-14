#include <stdio.h>

enum { FRAC = 24 };

int
check(unsigned int buf) {
    unsigned int mask = (1U << FRAC) - 1; //маска мантиссы
    unsigned int k = buf & -buf; //находжение младшего единичного бита
    return (buf & ~(mask * k)) == 0;    
}

int
main(void)
{
    unsigned int buf;
    while(scanf("%u", &buf) == 1) {
        printf("%d\n", check(buf));
    }
    return 0;
}