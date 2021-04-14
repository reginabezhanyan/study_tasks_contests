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

int
main(int argc, char *argv[])
{
    DIR *d = opendir(argv[1]);
    if (!d) {
        fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
        return 1;        
    }
    
    struct dirent *dd;
    errno = 0;
    while((dd =readdir(d)) != NULL) {
        if(!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, ".."))
            continue;
        printf("%lu %s\n", dd->d_ino, dd->d_name);
        char *buf = NULL;
        asprintf(&buf, "%s/%s", argv[1], dd->d_name);
        struct stat sb;
        if(lstat(buf, &sb) < 0) {
            fprintf(stderr, "%s: %s\n", buf, strerror(errno));
        } else {
            printf("dev, mode: %lx %08o\n", sb.st_dev, sb.st_mode & 0777);
        }
    }
    return 0;
}