#include <pthread.h>
#include <stdio.h>

void* minhaThread(void* arg) {
    printf("Executando thread!\n");
    return NULL;
}

int main() {
    pthread_t thread; // Declaração da thread
    pthread_create(&thread, NULL, minhaThread, NULL); // Criação da thread parametros:
                                                      // (endereço da thread, atributos, função a ser executada, argumento da função)
    pthread_join(thread, NULL); // Espera a thread terminar
    printf("Thread terminou.\n");
    return 0;
}
