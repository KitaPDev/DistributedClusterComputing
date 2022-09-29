#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int nthreads = atoi(argv[1]);

  omp_set_num_threads(nthreads);
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      int tid = omp_get_thread_num();
      printf("Thread %d is doing work in section A \n", tid);
    }
    #pragma omp section
    {
      int tid = omp_get_thread_num();
      printf("Thread %d is doing work in section B \n", tid);
    }
    #pragma omp section
    {
      int tid = omp_get_thread_num();
      printf("Thread %d is doing work in section C \n", tid);
    }
  }
  return 0;
}