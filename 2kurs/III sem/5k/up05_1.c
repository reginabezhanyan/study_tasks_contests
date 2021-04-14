#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

enum { SIGN = -1 };

int
main(void)
{
    int n, w;
    scanf("%o", &n);
    scanf("%o", &w);
    uint32_t mask = 1 << (n - 1);
    uint32_t max = (1 << n) - 1;
    uint32_t buf = 0;
    uint32_t sbuf = 0;
    while (buf <= max) {
        if (buf & mask) {
            sbuf = (buf & ~mask) * SIGN;
        } else {
            sbuf = buf;
        }
        printf("|%*" PRIo32 "|%*" PRIu32 "|%*" PRId32 "|\n", w, buf, w, buf, w, sbuf);
        buf++;
    }
    return 0;
}