// Usando soluçao 03
//Problemas Identificados
//
//Deadlock na função recursiva: A função compute faz chamadas recursivas enquanto o mutex está travado na thread wrapper (compute_thread). Quando compute tenta travar o mutex novamente para casos base (arg < 2), o programa trava porque o mutex já está travado pela mesma thread.
//Uso desnecessário de variável global: A variável gValue é compartilhada entre todas as threads, o que força o uso de mutex. Porém, cada thread poderia ter sua própria variável local para armazenar o resultado.
//Solução Proposta
//
//A melhor solução é eliminar completamente a necessidade do mutex, tornando cada thread independente. Podemos fazer isso:
//
//Removendo a variável global gValue e usando variáveis locais
//Modificando a função compute para retornar o valor calculado em vez de modificar uma variável global
//Eliminando to_do o uso do mutex, já que cada thread trabalhará com seus próprios dados
//Melhorias Implementadas
//
//Eliminação do mutex: Removemos completamente o mutex e sua inicialização/destruição
//Função compute modificada: Agora retorna o valor calculado em vez de modificar uma variável global
//Thread wrapper simplificada: Apenas chama compute e armazena o resultado
//Paralelismo eficiente: Cada thread opera de forma independente, sem necessidade de sincronização


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Função imprime resultados na correção do exercício -- definida em helper.c
void imprimir_resultados(int n, int** results);

// Função compute que calcula um valor de forma independente (ex: Fibonacci)
int compute(int arg) {
    if (arg < 2)
        return arg;
    return compute(arg - 1) + compute(arg - 2);
}

// Função wrapper que será usada pelas threads
void* compute_thread(void* arg) {
    int* ret = malloc(sizeof(int));
    *ret = compute(*((int*)arg));
    return ret;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s n_threads x1 x2 ... xn\n", argv[0]);
        return 1;
    }

    int n_threads = atoi(argv[1]);
    if (!n_threads || argc < 2 + n_threads) {
        printf("Uso: %s n_threads x1 x2 ... xn\n", argv[0]);
        return 1;
    }

    int args[n_threads];
    int* results[n_threads];
    pthread_t threads[n_threads];

    for (int i = 0; i < n_threads; ++i) {
        args[i] = atoi(argv[2 + i]);
        pthread_create(&threads[i], NULL, compute_thread, &args[i]);
    }

    for (int i = 0; i < n_threads; ++i)
        pthread_join(threads[i], (void**)&results[i]);

    // Imprime resultados
    imprimir_resultados(n_threads, results);

    for (int i = 0; i < n_threads; ++i)
        free(results[i]);

    return 0;
}

/*
Como funciona essa solução?

A ideia é que cada thread calcule seu resultado de forma independente, sem depender de uma variável global (gValue) compartilhada entre threads. Assim:

A função compute() passa a retornar diretamente o valor calculado (por exemplo, de Fibonacci).
A função compute_thread() passa esse resultado direto como retorno da pthread_create().
Benefícios dessa abordagem

Sem uso de mutex → sem overhead de sincronização.
Cada thread calcula de forma independente → melhor uso da CPU.
Código mais simples e limpo.
*/
