#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int size;
  int my_rank;
  int send_value;
  int rank_sum;
  int i;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  send_value = my_rank + 1;

  MPI_Reduce(&send_value, &rank_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  printf ("The send value of all ranks at process %d is %d \n", my_rank, send_value);
  if (my_rank == 0) {
    printf("The final reduction at %d is %d \n", my_rank, rank_sum);
  }

  /* Finalize the MPI environment. */
  MPI_Finalize();
}