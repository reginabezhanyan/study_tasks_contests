#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <time.h> 

enum 
{
    N = 3,
    TY = 1900
};

int
main(void)
{
    int fd[2];
    if (pipe(fd) < 0) {
        return 1;
    }
    pid_t pid;
    for (int i = 1;  i <= N; i++) {
        pid = fork();
        if (pid < 0) {
            return 1;
        } else if (pid > 0) {
            wait(NULL);
            time_t tmp;
            close(fd[1]);
            if (read(fd[0], &tmp, sizeof(tmp)) < 0) {
                return 1;
            } 
            struct tm* Tm = localtime(&tmp);
            if (i == 1) {
                printf("Y:%04d\n", Tm->tm_year + TY);
            } else if (i == N - 1) {
                printf("M:%02d\n", Tm->tm_mon + 1);
            } else {
                printf("D:%02d\n", Tm->tm_mday);
            }
            close(fd[0]);
            break;
        }
        if (i == N) {
            close(fd[0]);
            time_t t = time(NULL);  
            for (int j = 0; j < N; j++) {
                if (write(fd[1], &t, sizeof(t)) < 0) {
                    return 1;
                }
            }
            close(fd[1]);
            break;
        }
    }
    return 0;
}