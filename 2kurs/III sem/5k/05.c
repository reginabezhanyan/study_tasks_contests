#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(int argc, char *argv[])
{
    int year, mon, day, hour, min, sec;
    time_t y;
    int p = 0;
    FILE *f;
    f = fopen(argv[1], "r");
    while(fscanf(f, "%d/%d/%d %d:%d:%d", &year, &mon, &day, &hour, &min, &sec) > 0) {
        struct tm t;
        t.tm_year = year - 1900;
        t.tm_mon = mon - 1;
        t.tm_mday = day;
        t.tm_hour = hour;
        t.tm_min = min;
        t.tm_sec = sec;
        t.tm_isdst = -1;
        time_t x = mktime(&t);
        if(p != 0) {
            printf("%ld\n", x - y);
        }
        y = x;
        p = 1;;
    }
    fclose(f);
}
