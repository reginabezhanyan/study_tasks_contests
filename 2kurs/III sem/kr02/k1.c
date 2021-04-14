#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 

enum { NMAX = 10 };

void tree(long k, long n) {
    if (k > n) {
        printf("%ld\n", k);
        fflush(stdout);
        _exit(0);
    }
    if(!fork()) {
        tree(2*k + 1, n);
    }
    while (wait(NULL) != -1);
    printf("%ld\n", k);
    fflush(stdout);
    if(!fork()) {
        tree(2*k + 2, n);
    }
    while (wait(NULL) != -1);
    _exit(0);
}


int
main (int argc, char *argv[])
{
    long n, max;
    sscanf(argv[1], "%ld", &n);
    /*if (n < 0 || n > NMAX) {
        return 0;
    }*/
    max = (1 << n) - 2;
    tree(0, max);
    return 0;
}