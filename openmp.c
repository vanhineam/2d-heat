#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void getInput(int*, int*);

void main(int arc, char* argv) {
    clock_t begin,end;
    double time_spent;
    int iteration, i, j, current, next, N, T;

    getInput(&N, &T);

    //initaialize the array
    double h[2][N][N];
    double g[2][N][N];

    // Set all the walls to 20C degrees
    for(i = 0; i < N; i++) {
        h[0][0][i] = 20.0;
        h[0][i][0] = 20.0;
        h[0][N-1][i] = 20.0;
        h[0][i][N-1] = 20.0;
        g[0][0][i] = 20.0;
        g[0][i][0] = 20.0;
        g[0][N-1][i] = 20.0;
        g[0][i][N-1] = 20.0;
    }

    // Set the starting point and the ending point of the fireplace
    double fp_start, fp_end;
    fp_start = 0.3 * N;
    fp_end = (0.7 * N);

    // Initialize the values of the location of the fireplacee to 100C
    for(i = fp_start; i < fp_end; i++) {
        h[0][0][i] = 100.0;
        g[0][0][i] = 100.0;
    }

    // Get the start time of the program
    begin = clock();

    // The actual calculation of the temperature of the room.
    current = 0;
    next = 1;
    for (iteration = 0; iteration < T; iteration++) {
        for( i = 1; i < N-1; i++) {
            for( j = 1; j < N-1; j++) {
                h[next][i][j] = 0.25 * (h[current][i-1][j] + h[current][i+1][j]+ h[current][i][j-1] + h[current][i][j+1]);
            }
        }
        current = next;
        next = (current + 1) % 2;
    }

    // Get the end time
    end = clock();
    // Calculate the time spent
    time_spent = (double)(end-begin) /CLOCKS_PER_SEC;

    // Print an 8x8 array the N/8 x N/8 positions of the room.
    for(i = 0; i < N; i+= N/8) {
        for(j = 0; j < N; j+= N/8) {
            printf("%.2f ", h[0][i][j]);
        }
        printf("\n");
    }
    printf("\n");




    for (iteration = 0; iteration < T; iteration++) {
        #pragma omp parallel for private(i, j)
        for( i = 1; i < N-1; i++) {
            for( j = 1; j < N-1; j++) {
                g[next][i][j] = 0.25 * (g[current][i-1][j] + g[current][i+1][j]+ g[current][i][j-1] + g[current][i][j+1]);
            }
        }
        current = next;
        next = (current + 1) % 2;
    }

    // Print an 8x8 array the N/8 x N/8 positions of the room.
    for(i = 0; i < N; i+= N/8) {
        for(j = 0; j < N; j+= N/8) {
            printf("%.2f ", g[0][i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(g[0][i][j] != h[0][i][j]) {
                printf("2 arrays do not match\n");
                exit(1);
            }
        }
    }
    // Print the time in seconds that the program took to run
    printf("The program took %f seconds to run.\n", time_spent);

}

void getInput(int* N, int* T) {
    // Get the size of the matrix
    int valid = 0;
    while(!valid) {
        printf("Please enter matrix size(NxN): ");
        scanf("%d", N);
        if(N) {
            valid = 1;
        }
    }

    // Get the number of iterations
    valid = 0;
    while(!valid) {
        printf("Please enter the number of iterations: ");
        scanf("%d", T);
        if(N) {
            valid = 1;
        }
    }
}

