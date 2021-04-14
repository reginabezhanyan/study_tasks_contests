#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char str[] = "rwxrwxrwx";

enum { LEN = sizeof(str) - 1 };

int
main(int argc, char *argv[])
{
    long int k = 0, ch;
    int mask;
    char *end;
    char buf[LEN + 1];
    buf[LEN] = '\0';
    for(int i = 1; i < argc; i++){
        k = strtol(argv[i], &end, 8);
        ch = 0;
        for(int j = LEN - 1; j >= 0; j--) {
            mask = 1 << j;
            if((mask & k) != 0){
                buf[ch] = str[ch];
            } else {
                buf[ch] = '-';
            }
            ch++;
        }
        printf("%s\n", buf);
    }
    return 0;
}