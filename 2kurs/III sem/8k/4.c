#include <stdio.h>
#include <stdlib.h>  
#include <limits.h>

enum
{
    A = 1103515245,
    C = 12345,
    M = INT_MAX
};

typedef struct RandomOperations
{
    int (* next) (int);
    int (* destroy) (int);
} RandomOperations;

typedef struct RandomGenerator
{
    RandomOperations ops;
} RandomGenerator;

RandomGenerator *
random_create(int seed)
{
    static int k = seed;
    
    
}

int 
main(void)
{
    printf("%d", M);
    return 0;
}