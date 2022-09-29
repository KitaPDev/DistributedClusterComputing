#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *myThreadFunc(void *vargp) {
    int t = *((int *) vargp);
    printf("Hello world from thread %d.\n", t);
    return NULL;
}

int main(int argc, char* argv[]) {
    int i;
    int *k;
    int num_threads = atoi(argv[1]);
    pthread_t *threads;

    threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));
    for (i = 0; i < num_threads; i++) {
        k = malloc(sizeof(int));
        *k = i;
        pthread_create(&threads[i], NULL, myThreadFunc, k);
    }
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");
    return 0;
}