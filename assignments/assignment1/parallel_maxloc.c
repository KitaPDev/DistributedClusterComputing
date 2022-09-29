#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

int x[1000000];

int main(int argc, char* argv[]) {
    int nthreads = atoi(argv[1]);

    srand(time(0));
    for(int i=0; i < 1000000;i++) {
        x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
    }

    double maxval = 0.0; int maxloc = 0;

    time_t start = clock();
    omp_set_num_threads(nthreads);
    #pragma omp parallel for
    for (int i=0; i < 1000000; i++) {
        if (x[i] > maxval) {
            #pragma omp critical
            maxval = x[i]; maxloc = i;
        }
    }
    time_t end = clock();

    printf("Maximum Value is %f at %d.\nRun time is %.5f seconds.\n", maxval, maxloc, ((double) (end - start)) / CLOCKS_PER_SEC);
}