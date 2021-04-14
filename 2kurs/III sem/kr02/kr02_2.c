#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 

int
main (int argc, char *argv[])
{
    int fd1[2], fd2[2];
    FILE *file1, *file2;
    if (pipe(fd1) < 0 || pipe(fd2) < 0) {
        return 1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        return 1;
    } else if (!pid) {
        file1 = fopen(argv[1], "r");
        int sum1 = 0;
        int buf1;
        while (fscanf(file1, "%d", &buf1) == 1) {
            sum1 += buf1;
        }
        fclose(file1);
        if (write(fd1[1], &sum1, sizeof(sum1)) < 0) {
            return 1;
        }
        return 0;
    }
    
    pid = fork();
    if (pid < 0) {
        return 1;
    } else if (!pid) {
        file2 = fopen(argv[2], "r");
        int sum2 = 0;
        int buf2;
        while (fscanf(file2, "%d", &buf2) == 1) {
            sum2 += buf2;
        }
        fclose(file2);
        if (write(fd2[1], &sum2, sizeof(sum2)) < 0) {
            return 1;
        }
        return 0;
    }
    
    while (wait(NULL) != -1);
    
    int S1, S2;
    if (read(fd1[0], &S1, sizeof(S1)) < 0 || read(fd2[0], &S2, sizeof(S2)) < 0) {
        return 1;
    }
    printf("%d\n%d\n%d\n", S2, S1, S1 + S2);
    
    close(fd1[1]); close(fd1[0]);
    close(fd2[0]); close(fd2[1]);
    
    return 0;
}