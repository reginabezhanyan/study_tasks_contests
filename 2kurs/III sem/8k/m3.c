#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum
{
    N = 3,
    BUF_SIZE = 8
};

int
main(void)
{
    char buf[BUF_SIZE] = {0};
    int num;
    for (int i = 1; i <= N; i++) {
        if (!fork()) {
            if (read(STDIN_FILENO, buf, BUF_SIZE) < 0) {
                exit(1);
            }
            sscanf(buf, "%d", &num);
            printf("%d %d\n", i, num * num); 
            return 0;
        }
    }
    while (wait(NULL) != EOF); 
    return 0;
}