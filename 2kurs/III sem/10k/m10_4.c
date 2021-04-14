#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <signal.h>

pid_t *pid;
int count;

void kll_process (void) {
    for(int i = 1; i <= count; i++) {
        kill(pid[i], SIGKILL);
    }
    free(pid);  
    while (wait(NULL) != -1); 
    _exit(1);
}

void handler(int s) {
    kll_process();
}

int
main (int argc, char *argv[])
{
    if(argc == 1) {
        return 0;
    }
    int fd[2];
    int n = argc - 1;  
    pid = malloc((n + 1) * sizeof(*pid)); 
    count = 0;
    if (sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = handler }, NULL) < 0) {
        _exit(1);
    } 
    for (int i = 1; i < n; i++) {
        if(pipe(fd) < 0) {
            kll_process();
        } 
        pid[i]= fork(); 
        if (pid[i] < 0) {
            kll_process();
        } else if (!pid[i]) {  
            free(pid);
            if (dup2(fd[1], 1) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0) {
                kill(getppid(), SIGUSR1);
                _exit(1);
            }
            execlp(argv[i], argv[i], NULL);  
            kill(getppid(), SIGUSR1);
            _exit(1);
        } 
        count++; 
        if (dup2(fd[0], 0) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0) {
            kll_process();
        }
    } 
    pid[n] = fork();
    if (pid[n] < 0) {
        kll_process();
    } else if (!pid[n]) {
        execlp(argv[n], argv[n], NULL);
        kill(getppid(), SIGUSR1);
        _exit(1);
    } 
    close(0);
    while (wait(NULL) != -1); 
    free(pid);
    return 0;
} 