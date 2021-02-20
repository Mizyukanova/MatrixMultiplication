#include <stdio.h>
#include <time.h>
#include <malloc.h>

void MatrixMultiplicationSimple(int M, int N, int K, const float * A, const float * B, float * C)
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            C[i*N + j] = 0;
            for (int k = 0; k < K; ++k)
                C[i*N + j] += A[i*K + k] * B[k*N + j];
        }
    }
    
}

void MatrixMultiplicationOptimized(int M, int N, int K, const float * A, const float * B, float * C)
{
    for (int i = 0; i < M; ++i)
    {
        float * c = C + i * N;
        for (int j = 0; j < N; ++j)
            c[j] = 0;
        for (int k = 0; k < K; ++k)
        {
            const float * b = B + k * N;
            float a = A[i*K + k];
            for (int j = 0; j < N; ++j)
                c[j] += a * b[j];
        }
    }
}

int main(int argc, char const *argv[])
{
    float *A, *B, *C;
    int m, n, k;

    printf("M=");
    scanf("%d", &m);
    printf("N=");
    scanf("%d", &n);
    printf("K=");
    scanf("%d", &k);
    
    long int operations=2*(long int)m*n*k;

    A=(float*)malloc(m * k * sizeof(float));
    B=(float*)malloc(k * n * sizeof(float));
    C=(float*)malloc(m * n * sizeof(float));

    int i;
    for (i= 0; i<m*k; i++)
    {
        A[i]=i;
    }
    for (i = 0; i<k*n; i++)
    {
        B[i]=i;
    }
    for (i = 0; i<m*k; i++)
    {
        C[i]=i;
    }
    
    clock_t clocks,start,stop;
    double time, flops;

    start = clock();
    
    MatrixMultiplicationSimple(m,n,k,A,B,C);

    stop = clock();
    clocks=stop-start;
    
    time=(double)clocks/CLOCKS_PER_SEC;
    flops = operations/time;

    printf("1. time=%lf s, flops=%lf GFLOPS\n",time, flops/1000000000);

    start = clock();
    
    MatrixMultiplicationOptimized(m,n,k,A,B,C);

    stop = clock();
    clocks=stop-start;
    
    time=(double)clocks/CLOCKS_PER_SEC;
    flops = operations/time;

    printf("2. time=%lf s, flops=%lf GFLOPS\n",time, flops/1000000000);

    free(A);
    free(B);
    free(C);

    return 0;
}

