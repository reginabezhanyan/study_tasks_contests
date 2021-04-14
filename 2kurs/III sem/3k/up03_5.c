#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

enum 
{
    K = 0x0bad1dea,
    L = 0xbedabeda,
    RADIX = 10
};

char *getline2(FILE *f);

int
main(void)
{
    char *buf;
    char *bend;
    char *bufbuf;
    unsigned int ind_str = 0;
    unsigned int ind_num = 0;
    long int tmp;
    unsigned int sum;
    int signal;
    while((buf = getline2(stdin))) {
        ind_str++;
        sum = 0;
        signal = 0;
        bufbuf = buf;
        while(1) {
            errno = 0;
            tmp = strtol(bufbuf, &bend, RADIX);
            if(bufbuf == bend){
                while(*bend != '\n' && *bend != '\0') {
                    if(!isspace((unsigned char)*bend)) {
                        signal = 1;
                        break;
                    }
                    bend++;
                }
                break;
            }
            bufbuf = bend;
            ind_num++;
            if(errno || (int) tmp != tmp) {
                if(tmp < 0) {
                    tmp = -ind_num;
                } else {
                    tmp = ind_num;
                }
            }
            sum += tmp;
        }
        if(signal) {    
            printf("%d\n", L + ind_str);
        } else if(!sum && !ind_num) {    
            printf("%d\n", K + ind_str);
        } else {
            printf("%d\n", sum);
        }
        ind_num = 0;
        free(buf);
    }
    return 0;
}