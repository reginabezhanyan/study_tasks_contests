#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 

int
main(int argc, char *argv[])
{
    char a[16] = {};
    printf("%d", sizeof(a));
	FILE *f = fopen("test.bin", "wb");
    for(int i = 100; i <= 800 ; i++){ 
        fwrite(a, sizeof(a), 1, f);
        fwrite(&i, sizeof(i), 1, f);
    }
    fclose(f);
	return 0;
}