#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int sum(int N, int nthreads, int tid) {
	int count = N / nthreads;
	int start = count * tid;
	int end = start + count;
	int p_sum = 0;
	int remainder = N % nthreads;

	for (int i = start; i <= end; i++) {
		p_sum += i;
	}
	if (tid < remainder) {
		p_sum += count * nthreads + tid;
	}

  printf("N: %d | nthreads: %d | tid: %d --> count: %d | start: %d | end: %d | remainder: %d | p_sum: %d\n", N, nthreads, tid, count, start, end, remainder, p_sum);

	return p_sum;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Expected 3 arguments. Exiting...\n");
		exit(0);
	}

	int N = atoi(argv[1]);
	int nthreads = atoi(argv[2]);
	int partial_sum[nthreads];

  omp_set_num_threads(nthreads);
	#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		partial_sum[tid] = sum(N, nthreads, tid);
	}

	int sum = 0;
	for (int i = 0; i < nthreads; i++) {
		sum += partial_sum[i];
	}

	printf("The sum of the series is: %d\n", sum);
	return(0);
}