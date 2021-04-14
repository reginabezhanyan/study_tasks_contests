#include <stdio.h>
#include <stdlib.h>

enum
{
    MIN = 1,
    MAX = 2000
};

void
gcmd (int a, int b, int *x, int *y)
{
    int x1, y1;
    if (a == 0) {
        *x = 0; 
        *y = 1; 
        return;
    }
    gcmd (b%a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
}

int
prime (int n)
{
    for (int i = 2; i < n; i++){
        if (n % i == 0) {
            return 0;
        }
    }
    return 1; 
}

int
main(void)
{
    int n, y, i, j;
    int x = 0;
    int *x_2;
    scanf("%d", &n);
    if (n <= MIN || n >= MAX || !prime(n)){
        return 0;
    }
    x_2 = calloc(n, sizeof(*x_2));
    if (x_2 == NULL) {
        exit(1);
    }
    for (i = 1; i < n; i++) { //1 строка
        printf("%d ", x);
    }
    printf("\n");
    for (j = 1; j < n; j++) { //2 строка
        gcmd(j,n,&x,&y); //ax + by = 1
        x = (x % n + n) % n;
        x_2[j - 1] = x; //сохранение 2 строки
        printf("%d ", x);
    }
    printf("\n");
    for (i = 2; i < n; i++) { //3 - n строки
        for (j = 1; j < n; j++) {
            x = (i * x_2[j - 1]) % n;
            printf("%d ", x);
        }
        printf("\n");
    }
    free(x_2);
    return 0;
}