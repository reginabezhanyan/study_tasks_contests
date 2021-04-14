#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <limits.h>



enum
{
    SIZE = 32,
    SIZE_TMP = 2048,
    MAS_SIZE = 10
};
 
char *
getline2(FILE *f)
{
    unsigned int lengh = 0;
    size_t buf_size = SIZE;
    char *buf = calloc(buf_size, sizeof(*buf));
    if(!buf) {
        return NULL;
    }
    char *signal;
    int tmp;
    while(1){
        tmp = fgetc(f);
        if(tmp == EOF || tmp == '\r' || tmp == '\n') {
            if(lengh == 0) {
                free(buf);
                return NULL;
            }
            return buf;
        } else {
            lengh++;
            if(lengh >= buf_size) {
                buf_size <<= 1;
                signal = realloc(buf, buf_size * sizeof(*signal));
                if(signal == NULL) {
                    free(buf);
                    return NULL;
                }
                buf = signal;
            } 
            buf[lengh - 1] = tmp;
            buf[lengh] = '\0';
        }
    }  
}

int
main(void)
{
    int fd, size_tmp;
    char tmp[SIZE_TMP];
    unsigned long long int mas[MAS_SIZE] = {};
    char *buf = getline2(stdin);
    while (1) {
        if(buf == NULL) {
            break;
        }
        if((fd = open(buf, O_RDONLY)) < 0) {
            free(buf);
            break;
        }
        while((size_tmp = read(fd, tmp, sizeof(tmp))) > 0) {
            for(int i = 0; i < size_tmp; i++) {
                if(tmp[i] >= '0' && tmp[i] <= '9') {
                    mas[tmp[i] - '0']++;
                }
            }
        }
        free(buf);
        close(fd);
        break;
    }
    for(int i = 0; i < MAS_SIZE; i++) {
        printf("%d %llu\n", i, mas[i]);
    }
    return 0;
}