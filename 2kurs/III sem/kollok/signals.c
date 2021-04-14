#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int count;
void handler(int s)
{
    printf("\nSIGINT: %d time(s)\n", ++count);
    if (count == 4) {
        signal(SIGINT, SIG_DFL);
    } else {
        signal(SIGINT, handler);
    }
}

int main(void)
{
    signal(SIGINT, handler);
    while (1) {
        pause();
    }
    return 0;
}
