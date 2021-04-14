#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();

    if (!pid) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("son", "son", NULL);
    } else {
        int status;
        struct user_regs_struct REG;
        while (1) {
            wait(&status);
            ptrace(PTRACE_GETREGS, pid, &REG, &REG);
            printf("signal = %d, status = %#x, EIP = %#lx, ESP = %#lx\n",
                            WSTOPSIG(status), status, REG.eip, REG.esp);
            if (WSTOPSIG(status) != SIGTRAP) {
                if (!WIFEXITED(status)) {
                    ptrace(PTRACE_KILL, pid, NULL, NULL);
                }
                break;
            }
            ptrace(PTRACE_CONT, pid, 0, 0);
        }
    }

    return 0;
}
