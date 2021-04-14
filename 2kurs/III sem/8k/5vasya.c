#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int
main(void)
{
    int value, status, tmp;
    int ismain = 1;
    while(1) {
        pid_t pid = fork();
        if (!pid) {
            ismain = 0;
            if (fscanf(stdin, "%d", &value) == EOF) {
                break;
            }
        } else if (pid > 0) {
            wait(&status);
            if (ismain == 0) {
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    printf("%d\n", value);
                    break;
                } else {
                    _exit(1);
                }
            }
            if (WIFEXITED(status) == 0 || WEXITSTATUS(status)) {
                printf("-1\n");
            }
            break;
        } else if (fscanf(stdin, "%d", &tmp) > 0) {
            if (ismain) {
                printf("-1\n");
                break;
            } else {
                _exit(1);
            }
        } else {
            if (ismain == 0) {
                printf("%d\n", value);
            }
            break;
        }
    }
    return 0;
}