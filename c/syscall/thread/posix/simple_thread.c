# include <pthread.h> // thread library
# include <stdio.h> // standard I/O library

void* thread_work(void* arg) {
    const pthread_t id = pthread_self();
    printf("Olá da thread com ID: %lu\n", (unsigned long)id);
    printf("\tThread ID       : %lu (como ponteiro): (%p)\n", (unsigned long)id, (void*)pthread_self());
    return NULL;
}

int main() {
    int n_elements = 20; // number of elements in the array
    pthread_t threads[n_elements];
    // create threads
    for (int i = 0; i < sizeof(threads) / sizeof(threads[0]); i++) { // tamanho do array threads = tamanho total do array em bytes dividido pelo tamanho de um único elemento do array
        if (pthread_create(&threads[i], NULL, thread_work, NULL) != 0) {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }
    for (int i = 0; i < sizeof(threads) / sizeof(threads[0]); i++) {
        // wait for threads to finish
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error joining thread %d\n", i);
            return 1;
        }
    }
    return 0;
}