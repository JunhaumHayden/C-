#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

int contador_global = 0;
pthread_mutex_t mutex;

void *incrementor(void *arg) {
    int n_loops = *(int *)arg;
    for (int i = 0; i < n_loops; i++) {
        pthread_mutex_lock(&mutex);
        contador_global += 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Uso: %s n_threads n_loops\n", argv[0]);
        return 1;
    }

    int n_threads = atoi(argv[1]);
    int n_loops = atoi(argv[2]);
    pthread_t threads[n_threads];

    pthread_mutex_init(&mutex, NULL);
/*
    declarando duas variáveis do tipo struct timespec, chamadas start e end.
    Essa estrutura (struct timespec) é definida na biblioteca <time.h> e serve para armazenar instantes de tempo com precisão de nanossegundos.
    Ela tem dois campos:

    struct timespec {
        time_t tv_sec;   // segundos (inteiro)
        long   tv_nsec;  // nanossegundos (fração do segundo)
    };
 */
    struct timespec start, end;
    /*
    clock_gettime() é uma função que pega o tempo atual de um relógio específico.
    O primeiro argumento (CLOCK_MONOTONIC) indica qual relógio usar:
    CLOCK_MONOTONIC é um relógio que só anda pra frente, não é ajustado pelo sistema (por exemplo, mudanças de horário ou NTP).
    Isso o torna ideal para medir tempo de execução de código.
    O segundo argumento (&start) é o endereço da struct onde a função vai armazenar o tempo atual.
     */
    clock_gettime(CLOCK_MONOTONIC, &start); // início

    for (int i = 0; i < n_threads; i++)
        pthread_create(&threads[i], NULL, incrementor, &n_loops);

    for (int i = 0; i < n_threads; i++)
        pthread_join(threads[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &end); // fim

    pthread_mutex_destroy(&mutex);

    double tempo_execucao = (end.tv_sec - start.tv_sec) +
                            (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Contador: %d\n", contador_global);
    printf("Esperado: %d\n", n_threads * n_loops);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);

    return 0;
}
