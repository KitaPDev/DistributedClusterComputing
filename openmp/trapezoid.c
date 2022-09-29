#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double trap(double a, double b, int N, int nthreads, int tid) {
    double partial_sum = 0;
    double h = ((b-a) / nthreads);
    int partial_n = N/nthreads;
    double delta = (b - a)/N;
    double local_a = a + h * tid;
    double local_b = local_a + delta;
    for (int i = 0; i < partial_n; i++) {
        partial_sum += (local_a * local_a + local_b * local_b) * delta / 2;
        local_a = local_b;
        local_b += delta;
    }

    return partial_sum;
}

int main (int argc, char* argv[]) {
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int N = atoi(argv[3]);
    int nthreads = atoi(argv[4]);
    double partial_sum[nthreads];

    omp_set_num_threads(nthreads);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        partial_sum[tid] = trap(a, b, N, nthreads, tid);
    }    

    double sum = 0;
    for (int i = 0; i < nthreads; i++) {
        sum += partial_sum[i];
    }

    printf("The integral is: %.4f\n", sum);
    return 0;
}