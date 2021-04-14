#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 

int
main(void)
{
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) { 
        if (i == n) { 
            break;
        }
        printf("%d ", i); 
        fflush(stdout);
        int pid = fork();
        if (pid) {
            wait(NULL); 
            break;
        }  
    }
    if(i == n) {
        printf("%d\n", i);
    }
    return 0;
}