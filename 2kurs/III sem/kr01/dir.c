#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    long long sum = 0;
    DIR *d = opendir(argv[1]);
    if (!d) {
        fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
        return 1;        
    }
    
    struct dirent *dd;
    struct stat sb;
    while((dd =readdir(d)) != NULL) {
        if(!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, ".."))
            continue; 
        char *buf = NULL;
        asprintf(&buf, "%s/%s", argv[1], dd->d_name);
        if(stat(buf, &sb) >= 0) {
            if(S_ISREG(sb.st_mode) && getuid() == sb.st_uid) {
                if(dd->d_name[0] >= 'A' && dd->d_name[0] <= 'Z') {
                    sum += (long long) sb.st_size;
                }
            }
        }
    }
    printf("%lld", sum);
    return 0;
}