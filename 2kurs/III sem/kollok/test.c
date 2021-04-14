#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int dd[10];

int main(void)
{
    
    long *k = calloc(11, sizeof(*k));
    int **j = calloc(1, sizeof(*j));
    j[0] = calloc(20, sizeof(*j[0]));
    for (int g = 1; g <= 20; g++) j[0][g - 1] = g;
    k[10] = j;
    for (int h = 0; h < 11; h++) {
        if (h < 10) {
            printf("%d %ld\n", h, k[h]); 
        } else {
            int **pp = k[10];
            int *ll = pp[0];
            for (int g = 0; g < 20; g++) printf("%d ", ll[g]);  
        }
    }
printf("\n");
    int cc[10];
    const int *bb = calloc(10, sizeof(*bb));
    printf("%lu %lu %lu\n", sizeof(bb), sizeof(cc), sizeof(dd));
    printf("%lu\n", sizeof(blksize_t));
    pid_t a[] =
        {
            getpid(),
            getppid()
        };
    printf("%d %d\n", a[0], a[1]);
    
    char b[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
    void *c = b;
    printf("%x %x\n", ((int *) b)[0], b[0]);
    printf("%x\n", ((short *) b)[2]);
    printf("%d %hd %ld\n", ((char *) c)[0], *((short *) c), *((long *) c));
        
    int f[5];
    long g[5];
    c = f;
    printf("size: %lu, %lu, %lu\n", sizeof(g), sizeof(f), sizeof((int *) &c));
        
    return 0;
}
