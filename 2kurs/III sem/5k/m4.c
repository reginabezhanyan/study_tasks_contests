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
    unsigned short tmp;
    unsigned char buf[sizeof(tmp)];
    unsigned short maxch = K;
    int fd; 
    if((fd = open(argv[1], O_RDONLY)) < 0) {
        exit(1);
    }
    while(read(fd, &buf, sizeof(buf)) > 0) {
        tmp = buf[0] << CHAR_BIT;
        tmp += buf[1];
        if(tmp % 2 == 0 && tmp < maxch) {
            maxch = tmp;
        }
    }
    if(maxch % 2 == 0){
        printf("%hu\n", maxch);
    }
    close(fd);
    return 0;
}