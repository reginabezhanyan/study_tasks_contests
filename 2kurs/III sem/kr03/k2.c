#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <math.h> 

int
main(int argc, char *argv[])
{ 
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    double x0, dx;
    int n;
    sscanf(argv[1], "%lf", &x0);
    sscanf(argv[2], "%d", &n);
    sscanf(argv[3], "%lf", &dx);
    if (!fork()) { 
        close(fd1[1]);
        close(fd2[0]);
        if (!fork()) { 
            double ans;
            for (int i = 0; i <= n; i++) {
                ans = sin(x0 + i * dx); 
                write(fd2[1], &ans, sizeof(ans));
            }
            close(fd2[1]);
            double cs;
            ans = 0;
            while(read(fd1[0], &cs, sizeof(cs)) == sizeof(cs)) { 
                ans += cs * cs;
            }
            close(fd1[0]);
            printf("1 %.10lf\n", ans);
            fflush(stdout);
            _exit(0);
        }
        close(fd1[0]);
        close(fd2[1]);
        wait(NULL); 
        _exit(0);
    }
    if (!fork()) {
        close(fd1[0]);
        close(fd2[1]); 
        if (!fork()) {
            double ans;
            for (int i = 0; i <= n; i++) {
                ans = cos(x0 + i * dx); 
                write(fd1[1], &ans, sizeof(ans));
            }
            close(fd1[1]);
            double sn;
            ans = 0;
            while(read(fd2[0], &sn, sizeof(sn)) == sizeof(sn)) { 
                ans += fabs(sn); 
            }
            close(fd2[0]);
            printf("2 %.10lf\n", ans);
            fflush(stdout);
            _exit(0);
        }
        close(fd1[1]);
        close(fd2[0]);
        wait(NULL); 
        _exit(0);
    }
    close(fd1[1]); close(fd1[0]);
    close(fd2[0]); close(fd2[1]);
    while (wait(NULL) != -1); 
    printf("%d %d\n", 0, 0);
    return 0;
}