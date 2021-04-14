#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

enum { MAX = 4 }; 

volatile int count = 0;
volatile long long num = 0;

void
handler_0(int s)
{
    if (count == MAX - 1) {
        exit(0);
    }
    printf("%lld\n", num);
    fflush(stdout);
    count++;
}

void
handler_1(int s)
{ 
    exit(0);
}

int
simple (int n)
{
    for (int i = 2; i*i <= n; i++ ) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int
main(void)
{
    long long low, high;
    scanf("%lld%lld", &low, &high); 
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler_0, .sa_flags = 
            SA_RESTART }, NULL);
    sigaction(SIGTERM, &(struct sigaction) { .sa_handler = handler_1, .sa_flags = 
            SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    if (high < 0) {
        return 0;
    }
    if (low < 0) {
        low = 1;
    }
    for (int i = low; i < high; i++) {
        if (simple(i)) {
            num = i;
        } 
    }
    printf("%d\n", -1);
    fflush(stdout);
    return 0;
}