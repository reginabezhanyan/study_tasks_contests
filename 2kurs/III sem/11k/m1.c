#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

enum { MAX = 6 };

volatile int count = 0;

void inthnd(int s)
{
    if (count == MAX - 1) {
        exit(0);
    }
    printf("%d\n", count++);
    fflush(stdout);
}

int
main(void)
{
    sigaction(SIGHUP, &(struct sigaction) { .sa_handler = inthnd, .sa_flags = 
            SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) pause();
    return 0;
}
