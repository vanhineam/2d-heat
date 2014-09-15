all:

task1: sequential.c
	gcc sequential.c -o sequential

task2: openmp.c
	gcc -fopenmp openmp.c -o openmp

task3: sequentialx.c
	gcc sequentialx.c -o sample -lm -lX11

clean:
	rm -f openmp sequential sample
