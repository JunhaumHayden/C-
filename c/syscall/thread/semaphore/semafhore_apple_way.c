#include <dispatch/dispatch.h>
#include <stdio.h>
#include <pthread.h>

dispatch_semaphore_t sem; // declaração do semáforo global

void* tarefa(void* arg) {
    dispatch_semaphore_wait(sem, DISPATCH_TIME_FOREVER); // espera o semáforo
    printf("Thread executando: %s\n", (char*)arg);
    dispatch_semaphore_signal(sem); // libera o semáforo
    return NULL;
}

int main() {
    pthread_t t1, t2; // Declaração das threads

    sem = dispatch_semaphore_create(1); // inicializa o semáforo com valor 1 (binário)

    pthread_create(&t1, NULL, tarefa, "T1"); // Criação da thread 1
    pthread_create(&t2, NULL, tarefa, "T2"); // Criação da thread 2

    pthread_join(t1, NULL); // Espera a thread 1 terminar
    pthread_join(t2, NULL); // Espera a thread 2 terminar

    // dispatch_semaphore_t não precisa de destroy manual

    return 0;
}
