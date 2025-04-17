#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t sem; // declaração do semáforo

void* tarefa(void* arg) {
    sem_wait(&sem); // trava
    printf("Executando tarefa: %s\n", (char*) arg);
    sem_post(&sem); // libera
    return NULL;
}

int main() {
    pthread_t t1, t2; // Declaração das threads
    sem_init(&sem, 0, 1); // Inicializa o semáforo com valor 1 (binário)
    // parametros: (endereço do semáforo, 0 para semáforo entre threads do mesmo processo, valor inicial)

    pthread_create(&t1, NULL, tarefa, "Thread_01"); // Criação da thread 1
    pthread_create(&t2, NULL, tarefa, "Thread_02"); // Criação da thread 2

    pthread_join(t1, NULL); // Espera a thread 1 terminar
    pthread_join(t2, NULL); // Espera a thread 2 terminar

    sem_destroy(&sem); // Destroi o semáforo
    return 0;
}
