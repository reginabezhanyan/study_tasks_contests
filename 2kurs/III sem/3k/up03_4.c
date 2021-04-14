#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

enum { SIZE_BUF = 16 };

int
main(void)
{
    int k;
    int sign = 1;
    int signal = 0;
    char buf[SIZE_BUF];
    unsigned long long int sum = 0;
    unsigned long long int tmp = 0;
    while(1){
        k = read(STDIN_FILENO, buf, sizeof(buf));
        for(int i = 0; i < k; i++){
            if(!isspace((unsigned char)buf[i])){
                signal = 1;
                if(buf[i] == '-') {
                    sign = -1;
                } else if(buf[i] >= '0' && buf[i] <= '9') {
                    tmp = tmp * 10 + (unsigned long long int)(buf[i] - '0');
                }
            } else if(signal == 1) {
                if(sign == -1) {
                    tmp = ~tmp + 1;
                }
                sum += tmp;
                tmp = 0;
                sign = 1;
                signal = 0;
            }
        }
        if(k < SIZE_BUF) {
            if(signal == 1){
                sum += tmp;
            }
            break;
        }
    }
    printf("%lld\n", (long long int)sum);
    return 0;
}