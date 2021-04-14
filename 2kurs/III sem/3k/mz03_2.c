#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int tmp, i;
    long long int sum_pos = 0;
    long long int sum_neg = 0; 
    for(i = 1; i < argc; i++){
        sscanf(argv[i], "%d", &tmp);
        if(tmp > 0){
            sum_pos += tmp;
        } else {
            sum_neg += tmp;
        }
    }
    printf("%lld\n%lld\n", sum_pos, sum_neg);
    return 0;
}