#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv) 
{
  int my_rank;       
  int size;             
  int tag=0;
  int buf, fromOne, sumFromOne;

  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int arrayZero[16];
  srand(time(NULL));
  if (my_rank == 0) {
    for (int i = 0; i < 16; i++) {
        arrayZero[i] = rand();
    }

    MPI_Send(&arrayZero[1], 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
    printf("Process %2d has sent value %2d \n", my_rank, arrayZero[1]);
  }
  
  if (my_rank == 1) {
    MPI_Recv(&buf, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    printf("Process %2d received value %2d \n", my_rank, buf);

    printf("Process %2d broadcasting value %2d \n\n", my_rank, buf);  
    MPI_Bcast(&buf, 1, MPI_INT, my_rank, MPI_COMM_WORLD);
  }

  if (my_rank != 1) {
    MPI_Bcast(&fromOne, 1, MPI_INT, 1, MPI_COMM_WORLD);
    printf("process %d: After MPI_Bcast, %d %d \n", my_rank, buf, fromOne);
  }

  // MPI_Reduce(&fromOne, &sumFromOne, 1, MPI_INT, MPI_SUM, 2, MPI_COMM_WORLD);
  // if (my_rank == 2) {
  //   printf("Reduction at %d is %d\n", my_rank, sumFromOne);
  // }

  MPI_Finalize();
}