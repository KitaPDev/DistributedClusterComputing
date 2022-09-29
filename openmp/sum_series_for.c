#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[]) {
  int N = atoi(argv[1]);
  int nthreads = atoi(argv[2]);
  int partial_sum[nthreads];
  clock_t start, end;

  omp_set_num_threads(nthreads);
  start = clock();
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    partial_sum[tid] = 0;
    int p_sum = 0;
    #pragma omp for
    for (int i = 0; i <= N; i++) {
      p_sum += i;
    }
    partial_sum[tid] = p_sum;
  }
  end = clock();

  int sum = 0;
  for (int i = 0; i < nthreads; i++) {
    sum += partial_sum[i];
  }
  printf("The sum of the series is: %d\n", sum);
  printf("The run time is: %.4f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
  return 0;
}