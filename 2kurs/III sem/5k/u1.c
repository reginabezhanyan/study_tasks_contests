#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

enum
{
    POSIX_8 = 8,
    POSIX_10 = 10
};

int32_t
len_num (uint32_t num, uint32_t posix) {
    int32_t len = 0;
    if(num == 0) {
        len = 1;
        return len;
    } else {
        while(num) {
            len++;
            num = num / posix;
        }
        return len;
    }
}

void
pr_tab (int32_t tabl) {
    for (int32_t j = 0; j < tabl; j++) {
        printf(" ");
    }
}

int
main(void)
{
    int32_t n, w;
    scanf("%" SCNo32 "%" SCNo32, &n, &w);
    uint32_t mask = 1 << (n - 1);
    uint32_t max = (1 << n) - 1;
    uint32_t buf = 0;
    uint32_t sbuf = 0;   
    while (buf <= max) {
        printf("|");
        pr_tab(w - len_num(buf, POSIX_8));
        printf("%" PRIo32 "|", buf);
        pr_tab(w - len_num(buf, POSIX_10));
        printf("%" PRIu32 "|", buf);
        if (mask & sbuf) {
            sbuf &= ~mask;
        }
        if(sbuf) {
            pr_tab(w - 1 - len_num(sbuf, POSIX_10));
            printf("-");
        } else {
            pr_tab(w - len_num(sbuf, POSIX_10));
        }
        printf("%" PRIu32 "|\n", sbuf);
        buf++;
        sbuf++;
    }
    return 0;
}

