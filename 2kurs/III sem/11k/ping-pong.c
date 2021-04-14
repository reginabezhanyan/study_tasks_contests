#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h> 
#include <sys/wait.h>

volatile sig_atomic_t usr1_flag;

void handler (int s)
{
    usr1_flag = 1;
}

enum { K = 2 };

void 
run(FILE *in, FILE *out, sigset_t *os, long long max) 
{
    long long x; 
    int send, to;
    while (1) {
        while (!usr1_flag){
            sigsuspend(os);
        }
        usr1_flag = 0;
        fscanf(in, "%lld", &x); 
        if (x < max) {
            send = getpid();
            fscanf(in, "%d", &to);
            if (x % K == 1) {
                printf("%d %lld\n", 1, x);
                fflush(stdout);
            } else {
                printf("%d %lld\n", K, x);
                fflush(stdout);
            }
            x++;
            fprintf(out, "%lld %d\n", x, send); 
            fflush(out);
            kill(to, SIGUSR1);
        } else { 
            return;
        }  
    }
}

int 
main(int argc, char *argv[])
{
    int pid1, pid2, status;
    long long max = strtoll(argv[1], NULL, 10);
    int fd[2];
    pipe(fd);

    sigset_t bs, os;
    sigemptyset(&bs);
    sigemptyset(&os);
    sigaddset(&bs, SIGUSR1); 
    sigprocmask(SIG_BLOCK, &bs, NULL);
    
    FILE *in = fdopen(fd[0], "r");
    FILE *out = fdopen(fd[1], "w");
    
    if (!(pid1 = fork())) {
        sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = handler }, NULL); 
        run(in, out, &os, max);
        _exit(1);
    }
    
    if (!(pid2 = fork())) {
        sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = handler }, NULL);
        long long x = 1; 
        int pid = getpid();
        fprintf(out, "%lld %d\n", x, pid); 
        fflush(out);
        kill(pid1, SIGUSR1);
        run(in, out, &os, max);
        _exit(0);
    }
    wait(&status);  
    fprintf(out, "%lld\n", max); 
    fflush(out);
    if (WEXITSTATUS(status) == 1) { 
        kill(pid2, SIGUSR1);
    } else {
        kill(pid1, SIGUSR1);
    } 
    printf("Done\n"); 
    fclose(in);
    fclose(out);
    return 0;
}