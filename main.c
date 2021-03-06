#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "MatrixMultiplication.h"

int main(int argc, char const *argv[])
{
    float *A, *B, *C;
    int m, n, k, threads;

    /* Ввод размерностей матриц: A(MxK), B(KxN), C(MxN)*/
    printf("M=");
    scanf("%d", &m);
    printf("N=");
    scanf("%d", &n);
    printf("K=");
    scanf("%d", &k);
    
    long int operations=2*(long int)m*n*k;

    /* Выделение памяти под матрицы*/
    A=(float*)malloc(m * k * sizeof(float));
    B=(float*)malloc(k * n * sizeof(float));
    C=(float*)malloc(m * n * sizeof(float));

    /* Заполнение матриц A и B*/
    int i;
    for (i= 0; i<m*k; i++)
    {
        A[i]=i;
    }
    for (i = 0; i<k*n; i++)
    {
        B[i]=i;
    }
    
    /* Ввод количества потоков*/
    printf("Threads=");
    scanf("%d", &threads);

    /* Замер времени для простой реализации перемножения матриц A и B*/
    clock_t clocks,start,stop;
    double time, flops;

    start = clock();
    MatrixMultiplicationSimple(threads, m,n,k,A,B,C);
    stop = clock();
    clocks=stop-start;
    
    time=(double)clocks/CLOCKS_PER_SEC; // время в секундах
    flops = operations/time; // производительность в FLOPS

    printf("Simple. time=%lf s, flops=%lf GFLOPS\n",time, flops/1000000000);

    /* Замер времени для оптимизированной реализации перемножения матриц*/
    start = clock();
    MatrixMultiplicationOptimized(threads, m,n,k,A,B,C);
    stop = clock();
    clocks=stop-start;
    
    time=(double)clocks/CLOCKS_PER_SEC;
    flops = operations/time;

    printf("Optimized. time=%lf s, flops=%lf GFLOPS\n",time, flops/1000000000);

    /* Освобождение памяти*/
    free(A);
    free(B);
    free(C);

    return 0;
}

