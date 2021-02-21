#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <math.h>
#include "MatrixMultiplication.h"

int ComparisonResults(const float * C, const float * C1, const long int size)
{
    double epsilon=1e-07;

    for (int i = 0; i < size; ++i)
    {
        if ( fabs(C[i]/C1[i] - 1) > epsilon )
        {
            return 1;
        }
    }
    
    return 0;
}

int main(int argc, char const *argv[])
{
    float *A, *B, *C, *C1, *C2;
    int m=1, n=1, k=1, threads=2;

    /* Размерности матриц: A(MxK), B(KxN), C(MxN) и количество потоков*/
    printf("M=N=K=%d\n",m);
    printf("Threads=%d\n", threads);
    
    long int operations=2*(long int)m*n*k;

    /* Выделение памяти под матрицы*/
    A=(float*)malloc(m * k * sizeof(float));
    B=(float*)malloc(k * n * sizeof(float));
    C=(float*)malloc(m * n * sizeof(float));
    C1=(float*)malloc(m * n * sizeof(float));
    C2=(float*)malloc(m * n * sizeof(float));
    
    /* Заполнение матриц*/
    A[0]=1;
    B[0]=5;
    C[0]=5;
    
    MatrixMultiplicationSimple(threads,m,n,k,A,B,C1);
    
    MatrixMultiplicationOptimized(threads,m,n,k,A,B,C2);
    
    /* Вывод матриц*/
    int i,j;
    printf("A\n");
    for (i= 0; i<m; i++)
    {
        for (j= 0; j<k; j++)
        {
            printf("%f\t", A[i*m+j]);
        }
        printf("\n");  
    }
    printf("B\n");
    for (i= 0; i<k; i++)
    {
        for (j= 0; j<n; j++)
        {
            printf("%f\t", B[i*k+j]);
        }
        printf("\n");  
    }
    printf("C(Expected)\n");
    for (i= 0; i<m; i++)
    {
        for (j= 0; j<n; j++)
        {
            printf("%f\t", C[i*m+j]);
        }
        printf("\n");  
    }
    
    /* Сравнение результатов перемножения*/
    printf("C(Simple)\n");
    for (i= 0; i<m; i++)
    {
        for (j= 0; j<n; j++)
        {
            printf("%f\t", C1[i*m+j]);
        }
        printf("\n");  
    }
    if ( ComparisonResults(C, C1, (long int)m*n) == 0)
    {
        printf("Test 1 Simple passed.\n");
    }
    else
    {
        printf("Test 1 Simple failed.\n");
    }
    
    printf("C(Optimized)\n");
    for (i= 0; i<m; i++)
    {
        for (j= 0; j<n; j++)
        {
            printf("%f\t", C2[i*m+j]);
        }
        printf("\n");  
    }
    if ( ComparisonResults(C, C2, (long int)m*n) == 0)
    {
        printf("Test 1 Optimized passed.\n" );
    }
    else
    {
        printf("Test 1 Optimized failed.\n");
    }

    /* Освобождение памяти*/
    free(A);
    free(B);
    free(C);
    free(C1);
    free(C2);

    return 0;
}

