#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

unsigned long long
hash_function(unsigned long long);

enum
{
    POSIX_H = 16,
    POSIX_C = 10
};
 
int
main(int argc, char *argv[])
{
    int fd;
    char *end;
    int j = 1;
    errno = 0;
    if ((fd = open(argv[j], O_CREAT | O_WRONLY, 0660)) < 0) {
        exit(1);
    }
    j++;
    unsigned long long h = strtoll(argv[j], &end, POSIX_H);
    if(errno || end == argv[j]) {
        exit(1);
    }
    j++;
    unsigned long long count = strtoll(argv[j], &end, POSIX_C);
    if(errno || end == argv[j]) {
        exit(1);
    }
    if(count > 0) {
        if (lseek(fd, (count - 1) * sizeof(h), SEEK_END) < 0){
            exit(1);
        }
        if (write(fd, &h, sizeof(h)) != sizeof(h)) {
            exit(1);
        }
        for(unsigned long long int i = 2; i <= count; i++){
            if (lseek(fd, -i * sizeof(h), SEEK_END) < 0){
                exit(1);
            }
            h = hash_function(h);
            if (write(fd, &h, sizeof(h)) != sizeof(h)) {
                exit(1);
            }
        }
    }
    close(fd);
    return 0;
}