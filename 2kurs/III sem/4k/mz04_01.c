#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

enum 
{
    NAME = 16,
    PECK = 100,
    PECK_2 = 10,
    SIGN = -1
};

struct Read
{
    char name[NAME];
    int count;
};

int
main(int argc, char *argv[])
{
    int fd;
    long long int signal = 0;
    struct Read buf;
    int max = INT_MIN;
    int max_2 = INT_MIN;
    for(int i = 1; i < argc; i++) {
        if((fd = open(argv[i], O_RDONLY)) < 0) {
            exit(1);
        }
        while(1) {
            if(read(fd, &buf, sizeof(buf)) != sizeof(buf)) {
                break;
            }
            if(signal == 0) {
                max = buf.count;
                signal++;
            } else if(buf.count > max) {
                max_2 = max;
                max = buf.count;
                signal++;
            } else if(buf.count != max && buf.count >= max_2) {
                max_2 = buf.count;
                signal++;
            }
        }
        close(fd);
    } 
    if(signal > 1) {
        if(max_2 < 0) {
            printf("-");
        } else {
            max_2 *= SIGN;
        } 
        if(-(max_2 % PECK) < PECK_2) {
            printf("%d.0%d\n", -(max_2 / PECK), -(max_2 % PECK));
        } else {
            printf("%d.%d\n", -(max_2 / PECK), -(max_2 % PECK));
        }
    }
    return 0;
}