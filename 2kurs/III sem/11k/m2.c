#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t flag = 0;

void handler_0(int s)
{ 
    flag = 0;
}

void handler_1(int s)
{ 
    flag = 1;
}

int
main(void)
{
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler_0, .sa_flags = 
            SA_RESTART }, NULL);
    sigaction(SIGQUIT, &(struct sigaction) { .sa_handler = handler_1, .sa_flags = 
            SA_RESTART }, NULL);
    int buf;
    unsigned int ans = 0;
    fprintf(stdout, "%d\n", getpid());
    fflush(stdout);
    while (fscanf(stdin,"%d", &buf) > 0) { 
        if (flag == 1) {
            ans *= buf;
        } else {
            ans += buf;
        }
        fprintf(stdout, "%d\n", ans);
        fflush(stdout);
    }
    return 0;
}