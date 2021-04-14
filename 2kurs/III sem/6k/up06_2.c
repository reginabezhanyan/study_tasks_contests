#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

enum
{   
    SW = -1,
    BEG = 1900,
    Y = 1925,
    M = 10,
    D = 7,
    H_IN_D = 24,
    S_IN_D = 86400,
    MON = 12,
    DAY = 30
};

void
normaliz(struct tm *tmp)
{
    tmp->tm_year -= BEG;
    tmp->tm_mon -= 1;
    tmp->tm_isdst = SW;
    tmp->tm_hour = H_IN_D >> 1;
}

int
main(void)
{
    long long begin, date;
    struct tm tmp;
    memset(&tmp, 0, sizeof(tmp));
    tmp.tm_year = Y - BEG;
    tmp.tm_mon = M - 1;
    tmp.tm_mday = D;
    begin = mktime(&tmp);
    while (scanf("%d%d%d", &(tmp.tm_year), &(tmp.tm_mon), &(tmp.tm_mday)) > 0) {
        normaliz(&tmp);
        date = mktime(&tmp);
        date -= begin;
        date /= S_IN_D;
        printf("%lld %lld %lld\n", date / (DAY * MON) + 1, (date / DAY) % MON + 1, date % DAY + 1);
    }
    return 0;
}