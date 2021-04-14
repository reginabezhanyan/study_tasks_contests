#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

enum { K = -1 };

int
main(int argc, char *argv[])
{
    long long buf;
    long long min = LLONG_MAX;
    long long i = 0;
    int fd;
    long long i_min = K;
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        exit(1);
    }
    while (read(fd, &buf, sizeof(buf)) == sizeof(buf)) {
        if (buf < min || (buf == min && i_min == K)) {
            min = buf;
            i_min = i;
        }
        i++;
    }
    close(fd);
    if (i_min >= 0) {
        if ((fd = open(argv[1], O_RDWR)) < 0) {
            exit(1);
        }
        min = -(unsigned long long)min;
        if (lseek(fd, i_min * sizeof(min), SEEK_SET) < 0){
            exit(1);
        }
        if (write(fd, &min, sizeof(min)) != sizeof(min)) {
            exit(1);
        }
        close(fd);
    } 
    return 0;
}