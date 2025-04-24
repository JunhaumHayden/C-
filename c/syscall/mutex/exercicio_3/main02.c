/*
Solução com Mutex Recursivo
Você está absolutamente correto! Usar um mutex recursivo é de fato a solução mais "fácil" para manter a estrutura original do código enquanto resolve o problema de deadlock.
Análise desta Solução

Vantagens:

Mantém a estrutura original: Não precisamos modificar a lógica da função compute
Resolve o deadlock: O mutex recursivo permite que a mesma thread trave o mutex múltiplas vezes
Implementação simples: Requer apenas mudanças na inicialização do mutex
Desvantagens/Problemas:

Serialização implícita: Embora evite o deadlock, ainda força uma serialização das operações
Contenção por lock: Todas as threads competem pelo mesmo mutex global
Problema de design: Continua usando uma variável global compartilhada quando não há necessidade
Overhead: Mutexes recursivos têm um overhead ligeiramente maior que mutexes normais
Quando usar esta abordagem?

Esta solução seria adequada quando:

Você precisa manter exatamente a estrutura do código original
A performance não é crítica
Você está disposto a aceitar a serialização das operações
Modificar a função compute não é uma opção
*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int gValue = 0;
pthread_mutex_t gMtx;

// Função imprime resultados na correção do exercício -- definida em helper.c
void imprimir_resultados(int n, int** results);

// Função original mantida, mas agora com mutex recursivo
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

// Função wrapper com mutex recursivo
void* compute_thread(void* arg) {
    int* ret = malloc(sizeof(int));
    pthread_mutex_lock(&gMtx);
    gValue = 0;
    compute(*((int*)arg));
    /*
    /A expressão: compute(*((int*)arg)) equivale a:
    int* int_ptr = (int*)arg;  // Conversão explícita
    int value = *int_ptr;      // Dereferenciação explícita
    compute(value);            // Chamada da função
     */
    *ret = gValue;
    pthread_mutex_unlock(&gMtx);
    return ret;
}

int main(int argc, char** argv) {
    // Temos n_threads?
    if (argc < 2) {
        printf("Uso: %s n_threads x1 x2 ... xn\n", argv[0]);
        return 1;
    }
    // n_threads > 0 e foi dado um x para cada thread?
    int n_threads = atoi(argv[1]);
    if (!n_threads || argc < 2+n_threads) {
        printf("Uso: %s n_threads x1 x2 ... xn\n", argv[0]);
        return 1;
    }

    // Inicializa o mutex como RECURSIVO
    pthread_mutexattr_t attrs;
    pthread_mutexattr_init(&attrs);
    pthread_mutexattr_settype(&attrs, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&gMtx, &attrs);
    pthread_mutexattr_destroy(&attrs);

    int args[n_threads];
    int* results[n_threads];
    pthread_t threads[n_threads];
    //Cria threads repassando argv[] correspondente
    for (int i = 0; i < n_threads; ++i)  {
        args[i] = atoi(argv[2+i]);
        pthread_create(&threads[i], NULL, compute_thread, &args[i]);
    }
    // Faz join em todas as threads e salva resultados
    for (int i = 0; i < n_threads; ++i)
        pthread_join(threads[i], (void**)&results[i]);

    // Não usaremos mais o mutex
    pthread_mutex_destroy(&gMtx);

    // Imprime resultados na tela
    imprimir_resultados(n_threads, results);

    // Faz o free para os resultados criados nas threads
    for (int i = 0; i < n_threads; ++i)
        free(results[i]);

    return 0;
}