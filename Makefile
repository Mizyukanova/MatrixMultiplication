all: MatrixMultiplication test1 test2 test3 test4

MatrixMultiplication: main.o MatrixMultiplication.o
	gcc main.o MatrixMultiplication.o -w -o MatrixMultiplication -fopenmp

test1: test1.o MatrixMultiplication.o
	gcc MatrixMultiplication.o test1.o -w -o test1 -fopenmp

test2: test2.o MatrixMultiplication.o
	gcc MatrixMultiplication.o test2.o -w -o test2 -fopenmp

test3: test3.o MatrixMultiplication.o
	gcc MatrixMultiplication.o test3.o -w -o test3 -fopenmp

test4: test4.o MatrixMultiplication.o
	gcc MatrixMultiplication.o test4.o -w -o test4 -fopenmp


main.o: main.c
	gcc -c main.c -fPIC -O3 -march=native -w -fopenmp

MatrixMultiplication.o: MatrixMultiplication.c
	gcc -c MatrixMultiplication.c -fPIC -O3 -march=native -w -fopenmp

test1.o: test1.c
	gcc -c test1.c -fPIC -O3 -march=native -w -fopenmp

test2.o: test2.c
	gcc -c test2.c -fPIC -O3 -march=native -w -fopenmp

test3.o: test3.c
	gcc -c test3.c -fPIC -O3 -march=native -w -fopenmp

test4.o: test4.c
	gcc -c test4.c -fPIC -O3 -march=native -w -fopenmp

clean:
	rm -rf *.o MatrixMultiplication test1 test2 test3 test4