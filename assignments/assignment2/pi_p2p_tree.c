
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

    if (size % 2 != 0) {
        printf("Number of processes must be a multiple of 2!");
        MPI_Finalize();
        return 0;
    }

    int numSteps = log2(size);
    int bufCount;

    int count = 0;
    int partialCount[numSteps+1]; // For process 0 only
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

        // Eliminate odd processes
        if (myRank % 2 != 0) {
            MPI_Send(&count, 1, MPI_INT, myRank-1, tag, MPI_COMM_WORLD);

        } else {
            // Receive count from odd process
            MPI_Recv(&bufCount, 1, MPI_INT, myRank+1, tag, MPI_COMM_WORLD, &status);
            count += bufCount;

            if (myRank % 64 == 0) {
                for (int i = 1; i < 6; i++) {
                    MPI_Recv(&bufCount, 1, MPI_INT, myRank+pow(2, i), tag, MPI_COMM_WORLD, &status);
                    count += bufCount;
                }
                MPI_Send(&count, 1, MPI_INT, myRank-64, tag, MPI_COMM_WORLD);
            
            } else if (myRank % 32 == 0) {
                for (int i = 1; i < 5; i++) {
                    MPI_Recv(&bufCount, 1, MPI_INT, myRank+pow(2, i), tag, MPI_COMM_WORLD, &status);
                    count += bufCount;
                }
                MPI_Send(&count, 1, MPI_INT, myRank-32, tag, MPI_COMM_WORLD);

            } else if (myRank % 16 == 0) {
                for (int i = 1; i < 4; i++) {
                    MPI_Recv(&bufCount, 1, MPI_INT, myRank+pow(2, i), tag, MPI_COMM_WORLD, &status);
                    count += bufCount;
                }
                MPI_Send(&count, 1, MPI_INT, myRank-16, tag, MPI_COMM_WORLD);

            } else if (myRank % 8 == 0) {
                for (int i = 1; i < 3; i++) {
                    MPI_Recv(&bufCount, 1, MPI_INT, myRank+pow(2, i), tag, MPI_COMM_WORLD, &status);
                    count += bufCount;
                }
                MPI_Send(&count, 1, MPI_INT, myRank-8, tag, MPI_COMM_WORLD);
            
            } else if (myRank % 4 == 0) {
                MPI_Recv(&bufCount, 1, MPI_INT, myRank+2, tag, MPI_COMM_WORLD, &status);
                count += bufCount;
                MPI_Send(&count, 1, MPI_INT, myRank-4, tag, MPI_COMM_WORLD);

            } else if (myRank % 2 == 0) {
                MPI_Send(&count, 1, MPI_INT, myRank-2, tag, MPI_COMM_WORLD);
            }
        }

    } else { // Process 0
        for(int i = 0; i < numSteps; i++) {
            MPI_Recv(&partialCount[i-1], 1, MPI_INT, (int)pow(2, i), tag, MPI_COMM_WORLD, &status);
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