
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

#define SEED     921
#define NUM_ITER 1000000000

int main(int argc, char* argv[]) {
    int myRank;       
    int size;             
    int tag=0;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int count = 0;
    int partialCount[size-1];
    double x, y, z, pi;
    double startTime = MPI_Wtime();
    
    srand(myRank * SEED); // Important: Multiply SEED by "rank" when you introduce MPI!

    // Calculate PI following a Monte Carlo method
    if (myRank != 0) {
        for (int iter = 0; iter < NUM_ITER/(size - 1); iter++) {
            // Generate random (X,Y) points
            x = (double)random() / (double)RAND_MAX;
            y = (double)random() / (double)RAND_MAX;
            z = sqrt((x*x) + (y*y));
            
            // Check if point is in unit circle
            if (z <= 1.0) {
                count++;
            }
        }
        MPI_Send(&count, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);

    } else {
        for(int i = 1; i <= size - 1; i++) {
            MPI_Recv(&partialCount[i-1], 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
            count += partialCount[i-1];
        }

        pi = ((double)count / (double)NUM_ITER) * 4.0;

        double runTime = MPI_Wtime() - startTime;
        printf("PI computed in %f seconds\n", runTime);

        // Estimate Pi and display the result
        printf("The result is %f\n", pi);
    }
    
    MPI_Finalize();
}

