#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void alrm(int s)
{
    printf("\nFASTER!\n");
    fflush(stdout);
    alarm(5);
}

int main(int argc, char *argv[])
{
    char s[10];
    signal(SIGALRM, alrm);
    alarm(5);
    printf("Enter the name!\n");
    while (1) {
        printf("name: ");
        fflush(stdout);
        if (fgets(s, sizeof(s), stdin) != NULL) {
            break;
        }
        printf("\n");
    }
    printf("OK!\n");
    return 0;
}
