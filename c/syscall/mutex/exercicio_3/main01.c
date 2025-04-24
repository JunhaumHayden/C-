/*
uma solução que mantém a estrutura original do código (com a variável global e o mutex), mas corrige o deadlock. Esta solução funciona, mas tem problemas de design que a tornam questionável.
# Problemas desta Solução

- Serialização efetiva: Embora tecnicamente paralelo, o programa acaba sendo quase serial devido ao uso excessivo do mutex.
Cada thread precisa travar o mutex frequentemente durante a execução recursiva.
- Contenção por lock: Todas as threads competem pelo mesmo mutex, o que pode causar grande overhead e reduzir
significativamente o desempenho.
- Resultados imprevisíveis: Como todas as threads compartilham a mesma variável global gValue, os resultados podem variar dependendo da ordem de execução das threads, já que uma thread pode sobrescrever o valor de gValue antes que outra termine seu cálculo.
Problema de design fundamental: O uso de uma variável global para cálculos independentes é um anti-pattern em programação concorrente.
Quando esta solução poderia ser aceitável?

## Esta abordagem só seria justificável se:
Estivéssemos extremamente limitados em memória e não pudéssemos alocar variáveis locais
O código original fosse tão crítico que não pudéssemos modificar a função compute
O desempenho não fosse uma preocupação

## Conclusão
Esta versão serve principalmente para ilustrar como um uso inadequado de mutexes pode levar a soluções que "funcionam" mas
são profundamente problemáticas.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int gValue = 0;
pthread_mutex_t gMtx;

void imprimir_resultados(int n, int** results);

void compute(int arg) {
    if (arg < 2) {
        pthread_mutex_lock(&gMtx);
        gValue += arg;
        pthread_mutex_unlock(&gMtx);
    } else {
        compute(arg - 1);
        compute(arg - 2);
    }
}

void* compute_thread(void* arg) {
    int* ret = malloc(sizeof(int));

    // Movemos o lock/unlock para proteger apenas o acesso a gValue
    pthread_mutex_lock(&gMtx);
    gValue = 0;
    pthread_mutex_unlock(&gMtx);

    compute(*((int*)arg));

    pthread_mutex_lock(&gMtx);
    *ret = gValue;
    pthread_mutex_unlock(&gMtx);

    return ret;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s n_threads x1 x2 ... xn\n", argv[0]);
        return 1;
    }

    int n_threads = atoi(argv[1]);
    if (!n_threads || argc < 2+n_threads) {
        printf("Uso: %s n_threads x1 x2 ... xn\n", argv[0]);
        return 1;
    }

    pthread_mutex_init(&gMtx, NULL);

    int args[n_threads];
    int* results[n_threads];
    pthread_t threads[n_threads];

    for (int i = 0; i < n_threads; ++i) {
        args[i] = atoi(argv[2+i]);
        pthread_create(&threads[i], NULL, compute_thread, &args[i]);
    }

    for (int i = 0; i < n_threads; ++i)
        pthread_join(threads[i], (void**)&results[i]);

    pthread_mutex_destroy(&gMtx);

    imprimir_resultados(n_threads, results);

    for (int i = 0; i < n_threads; ++i)
        free(results[i]);

    return 0;
}