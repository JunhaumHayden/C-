#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

FILE* out;
sem_t semaphore_a, semaphore_b;

// variaveis para solucao flexivel
int count_a = 0, count_b = 0;
pthread_mutex_t mutex;

void *thread_a(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
	//      +---> arquivo (FILE*) destino
	//      |    +---> string a ser impressa
	//      v    v
    //  fprintf(out, "A");
        // Importante para que vocês vejam o progresso do programa
        // mesmo que o programa trave em um sem_wait().
    //    fflush(stdout);
/*
        // solucao com alternância estrita
        sem_wait(&semaphore_a); //Espera se o semáforo estiver bloqueado para imprimir A

        fprintf(out, "A"); // Condicao de corrida
        fflush(stdout);

        sem_post(&semaphore_b); //Libera o semáforo para imprimir B
*/
        // solucao flexivel
        pthread_mutex_lock(&mutex); // Trava o mutex para garantir acesso exclusivo
        while (count_a - count_b > 0)
        {
            pthread_mutex_unlock(&mutex); // Destrava o mutex
            sem_wait(&semaphore_a); // Espera se o semáforo estiver bloqueado para imprimir A
            pthread_mutex_lock(&mutex); // Tenta travar o mutex novamente para a nova iteracao
        }
        // caso não entre no loop chega aqui com a trava
        fprintf(out, "A"); // Condicao de corrida
        fflush(stdout);
        count_a++;

        if (count_b <= count_a)
        {
            sem_post(&semaphore_b); // Libera o semáforo para imprimir B
        } else
        {
            sem_post(&semaphore_a);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *thread_b(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
        pthread_mutex_lock(&mutex);
        while (count_b - count_a > 0)
        {
            pthread_mutex_unlock(&mutex); // Destrava o mutex
            sem_wait(&semaphore_b); // Espera se o semáforo estiver bloqueado para imprimir B
            pthread_mutex_lock(&mutex); // Tenta travar o mutex novamente para a nova iteracao
        }
        // caso não entre no loop chega aqui com a trava
        fprintf(out, "B");
        fflush(stdout);
        count_b++;
        if (count_a <= count_b)
        {
            sem_post(&semaphore_a);
        } else{
            sem_post(&semaphore_b);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s [ITERAÇÕES]\n", argv[0]);
        return 1;
    }

    int iters = atoi(argv[1]);
    srand(time(NULL));
    out = fopen("result.txt", "w");

    // Inicializa semáforos e mutex
    sem_init(&semaphore_a, 0, 1); // Inicializa o semáforo A com valor 1
    sem_init(&semaphore_b, 0, 1); // Inicializa o semáforo B com valor 0 (B precisa esperar
    pthread_mutex_init(&mutex, NULL);

    pthread_t ta, tb;

    // Cria threads
    pthread_create(&ta, NULL, thread_a, &iters);
    pthread_create(&tb, NULL, thread_b, &iters);

    // Espera pelas threads
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    //Imprime quebra de linha e fecha arquivo
    fprintf(out, "\n");
    fclose(out);

    // Destroi semáforos
    sem_destroy(&semaphore_a);
    sem_destroy(&semaphore_b);
    pthread_mutex_destroy(&mutex);
  
    return 0;
}
