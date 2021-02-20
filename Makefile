all: 	
	gcc MatrixMultiplication.c -fPIC -O3 -march=native -w -o MatrixMultiplication -fopenmp
	