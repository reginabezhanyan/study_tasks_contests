#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    if (!fork()) {
        if (!fork()) {
            sleep(1);
            printf("%d %d\n", getpid(), getppid());
        }
        _exit(0);
    }
    while (wait(NULL) != -1);
    return 0;
}
