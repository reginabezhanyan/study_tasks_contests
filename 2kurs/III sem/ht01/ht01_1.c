#include <stdio.h>
#include <stdlib.h>

enum { SIZE = 32 };
 
char *
getline2(FILE *f)
{
    unsigned int lengh = 0;
    size_t buf_size = SIZE;
    char *buf = calloc(buf_size, sizeof(*buf));
    char *signal;
    int tmp;
    while(1){
        tmp = fgetc(f);
        if(tmp == EOF) {
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
                    return signal;
                }
                buf = signal;
            } 
            buf[lengh - 1] = tmp;
            buf[lengh] = '\0';
            if(tmp == '\n') {
                return buf;
            }
        }
    }  
}