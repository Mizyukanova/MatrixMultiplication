#include <omp.h>

void MatrixMultiplicationSimple(int threads, int M, int N, int K, const float * A, const float * B, float * C);
  
void MatrixMultiplicationOptimized(int threads, int M, int N, int K, const float * A, const float * B, float * C);
