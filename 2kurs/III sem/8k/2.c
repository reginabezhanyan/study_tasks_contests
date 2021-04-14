#include <stdio.h>
#include <stdlib.h>  

enum { MAX = 100 };

struct TMP{
    int value;
    int p;
};

int
main(void)
{
    int n, m, seed, buf;
    scanf("%d", &n);
    struct TMP *mas = calloc(n, sizeof(*mas));
    if(!mas) {
        return 1;
    } 
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &(mas[i].value), &(mas[i].p));
        if(i != 0) {
            mas[i].p += mas[i-1].p;
        }
    }
    scanf("%d%d", &m, &seed);
    srand(seed);
    for (int i = 0; i < m; i++) {
        buf = (int)((rand() / (RAND_MAX + 1.0)) * MAX);
        for (int j = 0; j < n; j++) {
            if(buf < mas[j].p) {
                printf("%d %d\n", buf, mas[j].value);
                break;
            }
        }
    }
    free(mas);
    return 0;
}