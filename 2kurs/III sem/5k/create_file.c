#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

union U
{
    unsigned short k;
    unsigned char a[2];
};

int
main(int argc, char *argv[])
{
    union U x;
	FILE *f = fopen("test.bin", "wb");
    for(int i = 1; i <= 8 ; i++){
        x.k = (unsigned short)i;
        fwrite(&(x.a[1]), 1, 1, f);
        fwrite(&(x.a[0]), 1, 1, f);
    }
    fclose(f);
	return 0;
}