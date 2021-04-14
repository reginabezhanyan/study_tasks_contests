#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <string.h>

int
main (int argc, char *argv[])
{
    int fd[2], fd2[2];
    pipe(fd);
    pipe(fd2);
    if (!fork()) {
        double buf;
        FILE *f = fopen(argv[1], "r");
        while(fscanf(f, "%lf", &buf) == 1) {
            if (buf >= 0) {
                write(fd[1], &buf, sizeof(buf));
            }
        }
        if(!fork()) {
            close(fd[1]);
            int i = 0;
            double num;
            double sum  = 0;
            while(read(fd[0], &num, sizeof(num)) > 0) {
                i++;
                sum += num;
            }
            if (i != 0) {
                write(fd2[1], &sum, sizeof(sum));
            }
        }
        close(fd[0]);
        close(fd[1]);
        fclose(f);
        wait(NULL);
        _exit(0);
    }
    close(fd[0]);
    close(fd[1]);
    while (wait(NULL) != -1);
    close(fd2[1]);
    double sum;
    if(read(fd2[0], &sum, sizeof(sum)) > 0) {
        printf("%.10g\n", sum);
    }
    close(fd2[0]);
    return 0;
}