#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
parse_rwx_permissions(const char *str)
{
    int answ = 0;
    if(str == NULL) {
        return -1;
    }
    int len = strlen(str);
    const char buf[] = "rwxrwxrwx";
    if(len != sizeof(buf) - 1) {
        return -1;
    }
    for(int i = 0; i < len; i++) {
        if (str[i] == buf[i]) {
            answ = (answ << 1) + 1;
        } else if (str[i] == '-') {
            answ <<= 1;
        } else {
            return -1;
        }
    }
    return answ;
}