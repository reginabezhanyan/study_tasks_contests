#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int
main (int argc, char *argv[])
{
    unsigned int count = 0;
    pid_t pid;
    int n;
    sscanf(argv[1], "%d", &n);
    n += 2;
    for (int i = 2; i < n && i < argc; i++) { 
        pid = fork();
        if(!pid) {
            char buf[PATH_MAX + 1];
            FILE *f = fopen(argv[i], "r");
            fgets(buf, sizeof(buf), f);
            buf[strlen(buf) - 1] = '\0'; 
            fclose(f);
            execlp(buf, buf, NULL); 
            _exit(1);
        }
    }
    int status;
    while ((wait(&status)) != -1) {
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            count++;
        } 
    }
    for(int i = n; i < argc; i++) {
        pid = fork();
        if(!pid) {
            char buf[PATH_MAX + 1] = {};
            FILE *f = fopen(argv[i], "r");
            fgets(buf, sizeof(buf), f);
            buf[strlen(buf) - 1] = '\0';
            fclose(f);
            execlp(buf, buf, NULL); 
            _exit(1);
        } 
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            count++;
        } 
    }
    printf("%d\n", count);
    return 0;
}