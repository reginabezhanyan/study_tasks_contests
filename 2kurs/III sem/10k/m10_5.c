#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <signal.h>

void
run (FILE *in, FILE *out, int num, int max, int pr) 
{
    while(fscanf(in, "%d", &num) == 1 && num < max) {
            printf("%d %d\n", pr, num);
            fflush(stdout);
            num++; 
            fprintf(out, "%d\n", num);
            fflush(out);
    }
}

int
main (int argc, char *argv[])
{ 
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    int num = 1;
    int max;
    sscanf(argv[1], "%d", &max);
    FILE *f11 = fdopen(fd1[1], "w");
    fprintf(f11, "%d\n", num);
    fflush(f11);
    FILE *f10 = fdopen(fd1[0], "r");
    FILE *f21 = fdopen(fd2[1], "w");
    FILE *f20 = fdopen(fd2[0], "r");
    pid_t pid = fork();
    if (!pid) {
        close(fd1[1]);
        close(fd2[0]);
        run(f10, f21, num, max, 1);
        return 0;
    }
    pid = fork();
    if (!pid) {
        close(fd1[0]);
        close(fd2[1]);
        run(f20, f11, num, max, 2);
        return 0;
    }
    close(fd1[1]); close(fd1[0]);
    close(fd2[0]); close(fd2[1]);
    fclose(f11); fclose(f10);
    fclose(f21); fclose(f20);
    while (wait(NULL) != -1);
    printf("Done\n");
    fflush(stdout);
    return 0;
}