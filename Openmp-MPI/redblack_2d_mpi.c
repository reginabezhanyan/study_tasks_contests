#include <math.h>
#include <stdio.h>
#include "mpi.h"
#define Max(a, b) ((a)>(b)?(a):(b))

#define N 64

double max_eps = 0.1e-7;
int itmax = 100;
double w = 0.5;
double eps;
int i, j;
int num_procs, rank;
int min_row = 0, max_row = N - 1;

MPI_Status status;
MPI_Request request;

double A[N][N];

void init();
void relax();
void verify(); 

int main(int argc, char **argv) { 
    MPI_Init(&argc, &argv);
    double time_start, time_end;
    init();
    
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Barrier(MPI_COMM_WORLD);
    
    if (rank == 0) {
        time_start = MPI_Wtime(); 
    } 
    
    min_row = rank == 0 ? 0 : (N / num_procs) * rank - 1;
    max_row = rank == num_procs - 1 ? N - 1 : (N / num_procs) * (rank + 1); 
     
    for (int it = 1; it <= itmax; ++it) {
        eps = 0.;
        relax();
        if (eps < max_eps) {
            break;
        }
    }

    if (rank != 0) {
        MPI_Send(A[min_row + 1], (max_row - min_row - 1) * N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        for (i = 1; i < num_procs; ++i) {
            int tmp_min_row = i == 0 ? 0 : N / num_procs * i - 1;
            int tmp_max_row = i == num_procs - 1 ? N - 1 : (N / num_procs) * (i + 1);
            MPI_Recv(A[tmp_min_row + 1], (tmp_max_row - tmp_min_row - 1) * N, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    
    if (rank == 0) {
        verify();
        time_end = MPI_Wtime();
        printf("time  = %f\n", time_end - time_start);
    }
    
    MPI_Finalize();
    return 0;
}

void init() { //инициализация матрицы
    for(j=0; j<=N-1; j++)
	for(i=0; i<=N-1; i++)
	{
		if(i==0 || i==N-1 || j==0 || j==N-1) A[i][j]= 0.;
		else A[i][j]= ( 1. + i + j) ;
	}
}

void relax() { //релаксация матрицы
    
    int nrank = rank == num_procs - 1 ? MPI_PROC_NULL : rank + 1;
    int prank = rank == 0 ? MPI_PROC_NULL : rank - 1; 
    double local_eps = eps;
    
    for (i = min_row + 1; i <= max_row - 1; i++) {
        for ( j = 1 + (i % 2); j <= N - 2; j += 2) {
            double b = w * ((A[i - 1][j] + A[i + 1][j] + A[i][j - 1] + A[i][j + 1]) / 4. - A[i][j]);
            A[i][j] = A[i][j] + b;
            local_eps = Max(fabs(b), local_eps);
        }
    }

    MPI_Isend(A[max_row - 1], N, MPI_DOUBLE, nrank, 0, MPI_COMM_WORLD, &request);
    MPI_Recv(A[max_row], N, MPI_DOUBLE, nrank, 0, MPI_COMM_WORLD, &status);

    MPI_Isend(A[min_row + 1], N, MPI_DOUBLE, prank, 0, MPI_COMM_WORLD, &request);
    MPI_Recv(A[min_row], N, MPI_DOUBLE, prank, 0, MPI_COMM_WORLD, &status);

    for ( i = min_row + 1; i <= max_row - 1; ++i) {
        for (j = 1 + ((i + 1) % 2); j <= N - 2; j += 2) {
            double b = w * ((A[i - 1][j] + A[i + 1][j] + A[i][j - 1] + A[i][j + 1]) / 4. - A[i][j]);
            A[i][j] = A[i][j] + b;
        }
    }

    MPI_Isend(A[max_row - 1], N, MPI_DOUBLE, nrank, 0, MPI_COMM_WORLD, &request);
    MPI_Recv(A[max_row], N, MPI_DOUBLE, nrank, 0, MPI_COMM_WORLD, &status);

    MPI_Isend(A[min_row + 1], N, MPI_DOUBLE, prank, 0, MPI_COMM_WORLD, &request);
    MPI_Recv(A[min_row], N, MPI_DOUBLE, prank, 0, MPI_COMM_WORLD, &status); 
    
    MPI_Allreduce(&local_eps, &eps, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
}


void verify() { //подсчет ответа
    double s;
    s = 0.; 
    for (i = 0; i <= N - 1; i++) { 
        for (j = 0; j <= N - 1; j++) {
            s = s + A[i][j] * (i + 1) * (j + 1) / (N * N);
        }
    }
    printf("S = %f\n", s);
}
