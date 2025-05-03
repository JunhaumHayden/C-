#include <stdlib.h> // biblioteca para atoi
#include <unistd.h> // biblioteca para sleep
#include <sys/types.h> // biblioteca para pid_t
#include <stdio.h> // biblioteca para printf
#include <pthread.h> // biblioteca para pthread_create, pthread_join

//                 (main)
//                    |
//    +----------+----+------------+
//    |          |                 |
// worker_1   worker_2   ....   worker_n

// ~~~ estrutura do programa ~~~
// main thread (pai) cria n_threds (argv[1]) worker threads
// cada thread deve incrementar contador_global (operador ++) n_loops vezes
// pai deve esperar pelas worker threads  antes de imprimir!


// ~~~ argumentos (argc, argv) ~~~
// ./program n_threads

// ~~~ printfs  ~~~
// main thread (após término das threads filhas): "Contador: %d\n"
// main thread (após término das threads filhas): "Esperado: %d\n"

// Obs:
// - pai deve criar n_threds (argv[1]) worker threads
// - cada thread deve incrementar contador_global (operador ++) n_loops vezes
// - pai deve esperar pelas worker threads  antes de imprimir!


int contador_global = 0;
pthread_mutex_t mutex; // declaraçao do mutex no escopo global

void *incrementor(void *arg) {
    int n_loops = *(int *)arg;
    for (int i = 0; i < n_loops; i++) {
      pthread_mutex_lock(&mutex); // inicio da seção crítica - argumento: endereço do mutex
      contador_global++;
      pthread_mutex_unlock(&mutex); // fim da seção crítica
    }
    pthread_exit(NULL); // ou return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Uso: %s n_threads n_loops\n", argv[0]);
        return 1;
    }

    int n_threads = atoi(argv[1]);  //ASCII to integer
    int n_loops = atoi(argv[2]);
    pthread_t threads[n_threads];
    pthread_mutex_init(&mutex, NULL); // inicializa o mutex - argumento: endereço do mutex, NULL para atributos padrão

    for (int i = 0; i < n_threads; i++)
        pthread_create(&threads[i], NULL, incrementor, (void*)&n_loops);

    for (int i = 0; i < n_threads; i++)
        pthread_join(threads[i], NULL);

    printf("Contador: %d\n", contador_global);
    printf("Esperado: %d\n", n_threads * n_loops);

    pthread_mutex_destroy(&mutex); // destrói o mutex - argumento: endereço do mutex)
    return 0;
}
