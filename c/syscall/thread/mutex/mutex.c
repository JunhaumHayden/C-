#include <pthread.h> // Biblioteca para threads POSIX
#include <stdio.h>

int contador = 0;
pthread_mutex_t lock; // declaração do Mutex para proteger o acesso ao contador

void* incrementar(void* arg) {
    for(int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock); // funcao lock - bloqueia o mutex
        contador++;
        pthread_mutex_unlock(&lock); // funcao unlock - libera o mutex
    }
    return NULL;
}

int main() {
    pthread_t t1, t2; // Declaração das threads
    pthread_mutex_init(&lock, NULL); // Inicializa o mutex

    pthread_create(&t1, NULL, incrementar, NULL); // Criação da thread 1
   // parametros: (endereço da thread, atributos, função a ser executada, argumento da função)
    pthread_create(&t2, NULL, incrementar, NULL); // Criação da thread 2
   // parametros: (endereço da thread, atributos, função a ser executada, argumento da função)

    pthread_join(t1, NULL); // Espera a thread 1 terminar
    pthread_join(t2, NULL); // Espera a thread 2 terminar

    pthread_mutex_destroy(&lock); // Destroi o mutex

    printf("Contador final: %d\n", contador);
    return 0;
}
