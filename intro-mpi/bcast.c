#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
  int my_rank;
  int size;
  int value, value_nonroot;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  value = my_rank;
  value_nonroot = my_rank;
  printf("process %d: Before MPI_Bcast, %d %d\n", my_rank, value, value_nonroot);

  if (my_rank == 0) {
    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
  } else {
    MPI_Bcast(&value_nonroot, 1, MPI_INT, 0, MPI_COMM_WORLD);
  }

  printf("process %d: After MPI_Bcast, %d %d \n", my_rank, value, value_nonroot);

  MPI_Finalize();
  return 0;
}