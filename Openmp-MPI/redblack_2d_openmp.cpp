#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#define  Max(a,b) ((a)>(b)?(a):(b))

#define  N   2048
double   maxeps = 0.1e-7;
int itmax = 100;
int i,j,k;
double w = 0.5;
double eps;
int num_thr = 0;

double A [N][N];

void relax();
void init();
void verify(); 


int main(int argc, char **argv){
    
	if (argc < 2) {
		printf("Too few arguments\n");
		return -1;
	}
    
	num_thr = atoi(argv[1]);
	int it;
	init();
	double start_time = omp_get_wtime();
	for(it = 1; it <= itmax; it++){
		eps = 0.;
		relax(); 
		if (eps < maxeps) 
			break;
	}
	double end_time = omp_get_wtime();
	verify();
	printf("number of threads: %d\n time: %f\n", num_thr, end_time - start_time);
	return 0;
}

void init(){ //инициализация матрицы
    #pragma omp parallel shared(A) num_threads(num_thr) 
    {
        #pragma omp for private(i,j)
        for(i = 0; i <= N-1; i++){
            for(j = 0; j <= N-1; j++){
                if(i == 0 || i == N-1 || j == 0 || j == N-1) A[i][j]= 0.;
                else A[i][j]= ( 1. + i + j) ;
            }
        }
    }
} 


void relax(){ //релаксация матрицы
	#pragma omp parallel shared(A) num_threads(num_thr) reduction(max: eps)
	{ 
		#pragma omp for private(i,j)
		for(int i = 1; i <= N-2; i++){
			for(int j = 1 + i % 2; j <= N-2; j+=2){
				double b;
				b = w * ((A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]) / 4. - A[i][j]);
				eps = Max(fabs(b),eps);
				A[i][j] = A[i][j] + b;
			}
		}
		#pragma omp for private(i,j)
		for(int i=1; i <= N-2; i++){
			for(int j = 1 + (i + 1) % 2; j<=N-2; j+=2){
				double b;
				b = w * ((A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]) / 4. - A[i][j]);
				A[i][j] = A[i][j] + b;
			}
		}
		#pragma omp critical
		{
			eps = Max(eps, eps);
		}

	}
}


void verify(){ //вычисление ответа
	double s;
	s = 0.;
    #pragma omp parallel shared(A) num_threads(num_thr) reduction(+: s)
    { 
        #pragma omp for private(i,j)
        for(i = 0; i <= N-1; i++){
            for(j = 0; j <= N-1; j++){
                s = s + A[i][j] * (i+1) * (j+1) / (N*N);
            }
        }
    }
	printf("S = %f\n",s);
}