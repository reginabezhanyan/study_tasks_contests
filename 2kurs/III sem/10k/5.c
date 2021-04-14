#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <signal.h>

int
main (int argc, char *argv[])
{ 
    int fd1[2], fd2[2];
    if (pipe(fd1) < 0) {
        return 1;
    }
    if (pipe(fd2) < 0) {
        return 1;
    }
    int num = 1;
    int n;
    sscanf(argv[1], "%d", &n);
    /*fr1 = fdopen(fd1[0], "r");
    fr2 = fdopen(fd1[0], "r");
    fw1 = fdopen(fd1[1], "w");
    fw2 = fdopen(fd2[1], "w");
    fprintf(fw1, "%d\n", num);
    fflush(fw1);*/
    write(fd1[1], &num, sizeof(num));
    pid_t pid = fork();
    if (pid < 0) { 
        return 1;
    } else if (!pid) {
        close(fd1[1]);
        close(fd2[0]);
        while(/*(fscanf(fr1, "%d", &num) == 1)*/ read(fd1[0], &num, sizeof(num)) && num <= n) {
            printf("1 %d\n", num);
            fflush(stdout);
            num++;
            /*fprintf(fw2, "%d\n", num);
            fflush(fw2);*/
            write(fd2[1], &num, sizeof(num));
        }
        return 0;
    }
    pid = fork();
    if (pid < 0) { 
        return 1;
    } else if (!pid) {
        close(fd1[0]);
        close(fd2[1]);
        while(/*(fscanf(fr2, "%d", &num) == 1)*/ read(fd2[0], &num, sizeof(num)) && num <= n) {
            printf("2 %d\n", num);
            fflush(stdout);
            num++;
            /*fprintf(fw1, "%d\n", num);
            fflush(fw1);*/
            write(fd1[1], &num, sizeof(num));
        }
        return 0;
    }
    close(fd1[1]); close(fd1[0]);
    close(fd2[0]); close(fd2[1]);
    while (wait(NULL) != -1);
    printf("Done\n");
    return 0;
}