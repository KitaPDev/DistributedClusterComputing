#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello world from thread %d\n", tid);

        if (tid == 0) {
            int nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}