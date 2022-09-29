#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int N = atoi(argv[1]);
  int nthreads = atoi(argv[2]);
  int counter = 0;
  omp_set_num_threads(nthreads);
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int i, local_counter;
    local_counter = 0;
    for (i = 0; i < N; i++) {
      counter++;
      local_counter++;
    }
    printf("Thread %d counted %d times \n", tid, local_counter);
  }
  printf("Final count is %d \n", counter);
  return 0;
}