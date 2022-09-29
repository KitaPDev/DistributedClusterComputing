#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[]) {
  int nthreads = atoi(argv[1]);
  double x = atoi(argv[2]);
  double terms[4];

  omp_set_num_threads(nthreads);
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      int tid = omp_get_thread_num();
      printf("Thread %d is calculating x4 \n", tid);
      terms[0] = pow(x, 4);
    }
    #pragma omp section
    {
      int tid = omp_get_thread_num();
      printf("Thread %d is calculating 15x3 \n", tid);
      terms[1] = 15 * pow(x, 3);
    }
    #pragma omp section
    {
      int tid = omp_get_thread_num();
      printf("Thread %d is calculating 10x2 \n", tid);
      terms[2] = 10 * pow(x, 2);
    }
    #pragma omp section
    {
      int tid = omp_get_thread_num();
      terms[3] = 2 * x;
    }
  }

  double y = 0;
  for (int i = 0; i < 4; i++) {
    y += terms[i];
  }

  printf("y = %.2f\n", y);
  return 0;
}