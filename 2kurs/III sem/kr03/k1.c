#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    int tmp;
    unsigned int n, count;
    while(scanf("%d", &tmp) == 1) {
        n = tmp;
        count = 0;
        while(n > 0) {
            count += n & 1;
            n >>= 1;
        }
        printf("%d\n", count % 2);
    }
    return 0;
}