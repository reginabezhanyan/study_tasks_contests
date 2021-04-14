#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
 
int
main(int argc, char *argv[])
{
    int fd;
    unsigned short buf;
    unsigned char tmp[sizeof(buf)];
    fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0600);
    while(scanf("%hu", &buf) == 1) {
        tmp[0] = buf >> CHAR_BIT;
        tmp[1] = buf;
        write(fd, tmp, sizeof(tmp));
    }
    close(fd);
    return 0;
}