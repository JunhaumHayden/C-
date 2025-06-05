#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CONTAS 5            // Número total de contas
#define NUM_THREADS 10          // Número total de threads
#define TRANSFERENCIAS_POR_THREAD 3

typedef struct {
    int id;
    sem_t sem;
} Conta;

Conta contas[NUM_CONTAS];

typedef struct {
    int thread_id;
} thread_arg_t;

void transferir(int origem, int destino, int thread_id) {
    // Simulação sem deadlock: sempre trava primeiro a conta de menor id
    int min = origem < destino ? origem : destino;
    int max = origem < destino ? destino : origem;

    sem_wait(&contas[min].sem);
    sem_wait(&contas[max].sem);

    printf("[Thread %d] Transferindo da conta %d para conta %d.\n", thread_id, origem, destino);
    // Simulação de operação de saldo
    printf("[Thread %d] Operou saldo na conta %d.\n", thread_id, origem);
    printf("[Thread %d] Operou saldo na conta %d.\n", thread_id, destino);
    fflush(stdout);

    // Libera os semáforos
    sem_post(&contas[max].sem);
    sem_post(&contas[min].sem);
}

void *thread_func(void *arg) {
    thread_arg_t *info = (thread_arg_t *) arg;
    int thread_id = info->thread_id;

    for (int i = 0; i < TRANSFERENCIAS_POR_THREAD; i++) {
        int origem, destino;
        do {
            origem = rand() % NUM_CONTAS;
            destino = rand() % NUM_CONTAS;
        } while (origem == destino);

        transferir(origem, destino, thread_id);
        usleep(100000 + rand() % 500000);  // Espera aleatória
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_arg_t args[NUM_THREADS];

    srand(time(NULL));

    // Inicializa contas e semáforos
    for (int i = 0; i < NUM_CONTAS; i++) {
        contas[i].id = i;
        sem_init(&contas[i].sem, 0, 1);
    }

    // Cria as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].thread_id = i;
        pthread_create(&threads[i], NULL, thread_func, &args[i]);
    }

    // Aguarda as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroi semáforos
    for (int i = 0; i < NUM_CONTAS; i++) {
        sem_destroy(&contas[i].sem);
    }

    printf("Fim das transferências.\n");
    return 0;
}
