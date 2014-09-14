all: task1 task2

task1: sequential.c
	gcc sequential.c -o sequential

task2: openmp.c
	gcc -fopenmp openmp.c -o openmp

clean:
	rm -f openmp sequential
