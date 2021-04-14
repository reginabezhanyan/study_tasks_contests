#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

enum
{ 
    Y = 1900,
    SW = -1
};

int
normaliz(struct tm *tmp, FILE *f)
{
    memset(tmp, 0, sizeof(*tmp));
    if (fscanf(f, "%d/%d/%d %d:%d:%d", &(tmp->tm_year), &(tmp->tm_mon), &(tmp->tm_mday), 
            &(tmp->tm_hour), &(tmp->tm_min), &(tmp->tm_sec)) == EOF) {
        return 1;    
    }
    tmp->tm_year -= Y;
    tmp->tm_mon -= 1;
    tmp->tm_isdst = SW;
    return 0;
}

int
main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
        return 1;
    }
    time_t first, second;
    struct tm tmp;
    normaliz(&tmp, f);
    first = mktime(&tmp);
    while (!normaliz(&tmp, f)) {
        second = mktime(&tmp);
        printf("%ld\n", second - first);
        first = second;        
    }
    fclose(f);
    return 0;
}