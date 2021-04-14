#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <string.h>
#include <math.h>
#include <limits.h>

int
main (int argc, char *argv[])
{ 
    int *pid = calloc(argc - 1, sizeof(*pid));  
    int *cur = calloc(argc - 1, sizeof(*cur)); 
    for (int i = 1; i < argc; i++) {
        pid_t pidd = fork();
        if (!pidd) {
            unsigned long long int ans;
            sscanf(argv[i], "%llu", &ans);
            int count = 0;
            while (ans) {
                if (1 & ans) { 
                    count++;
                }
                ans >>= 1;
            }
            free(pid);
            free(cur);
            _exit(count);
        }
        pid[i - 1] = pidd;
    } 
    pid_t u;
    int status;
    while ((u = wait(&status)) != -1) {
        for(int i = 0; i < argc - 1; i++) {
            if (pid[i] == u) {
                cur[i] = WEXITSTATUS(status);
                break;
            }
        }
    }
    for(int i = 0; i < argc - 1; i++) {
        printf("%d\n", cur[i]);
    }
   
    return 0;
}