#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    long long sum = 0;
    struct stat sb;
    for(int i = 1; i < argc; i++) {
        if(lstat(argv[i], &sb) >= 0) {
            if(S_ISREG(sb.st_mode) && !S_ISLNK(sb.st_mode) && sb.st_nlink == 1) {
                sum += (long long) sb.st_size;
            }
        }
        
    }
    printf("%lld\n", sum);
    return 0;
}