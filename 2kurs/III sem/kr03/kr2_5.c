#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h> 
#include <sys/wait.h>
 
volatile sig_atomic_t usr1_flag = 0; 

void
handler(int s)
{ 
    usr1_flag = 1;
}
 

int
main(void)
{
    sigset_t bs, os;
    sigemptyset(&bs);
    sigemptyset(&os);
    sigaddset(&bs, SIGUSR1); 
    sigprocmask(SIG_BLOCK, &bs, NULL);
    
    sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = handler, .sa_flags = 
            SA_RESTART }, NULL);
    
    int fd[2];
    FILE *in = fdopen(fd[0], "r");
    FILE *out = fdopen(fd[1], "r");
    pipe(fd);
    if(!fork()) { 
        pid_t pid;
        if(!(pid = fork())) {
            sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = handler, .sa_flags = 
                    SA_RESTART }, NULL);
            while (!usr1_flag){
                sigsuspend(&os);
            }
            usr1_flag = 0;
        }
        long long tmp;
        while(fscanf(stdin, "%lld", &tmp) == 1) {
            fprintf(out, "%d\n", tmp);
            fflush(out);
        }
        fclose(in);
        fclose(out);
        kill(pid, SIGUSR1);
        wait(NULL);
        _exit(0);
    }
    while(wait(NULL) != -1);
    return 0;
}