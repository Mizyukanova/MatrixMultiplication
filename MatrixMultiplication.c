void MatrixMultiplicationSimple(int threads, int M, int N, int K, const float * A, const float * B, float * C)
{
    omp_set_num_threads(threads);
    #pragma omp parallel for
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

void MatrixMultiplicationOptimized(int threads, int M, int N, int K, const float * A, const float * B, float * C)
{
    omp_set_num_threads(threads);
    #pragma omp parallel for
    for (int i = 0; i < M; ++i)
    {
        //printf("%d", omp_get_thread_num());
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

