all:

task1: sequential.c
	gcc sequential.c -o sequential

task2: openmp.c
	gcc -fopenmp openmp.c -o openmp

sample: sample.c
	gcc sample.c -o sample -lm -lX11

task3: sequentialx.c
	gcc sequentialx.c -o map -lm -lX11

parallelx: parallelx.c
	gcc -fopenmp parallelx.c -o parallel -lm -lX11

clean:
	rm -f openmp sequential sample map parallel
