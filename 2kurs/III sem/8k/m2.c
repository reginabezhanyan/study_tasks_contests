#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { N = 3 };

int
main(void)
{
    for (int i = 1; i <= N; i++) {
        if (i == N) {
            printf("%d", i);
            break;
        }
        int pid = fork();
        if (pid) {
            wait(NULL);
            printf (" %d", i);
            if (i == 1) {
                printf("\n");
            }
            break;
        }  
    }
    return 0;
}