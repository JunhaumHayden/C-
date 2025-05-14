/*
*Certifique-se de linkar com a biblioteca RT (Real Time) quando usar clock_gettime():
bash
gcc -pthread -lrt seu_programa.c -o seu_programa
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread/pthread.h>
#include <time.h> // biblioteca RT clock_gettime() Precisão de nanossegundos

#define BUFFER_SIZE 5
#define PRODUCE_ITEMS 20 // Número de items a serem produzidos
#define CONSUME_ITEMS 20 // Número de items a serem consumidos

typedef struct
{
    int items[BUFFER_SIZE]; // Buffer compartilhado
    int in;    // Próxima posição de inserção
    int out;   // Próxima posição de remoção
    int count;  // Número de items no buffer
} Buffer;

Buffer buffer = { .in = 0, .out = 0, .count = 0 }; // declarando uma struct global iniciada com 0

int produce_item(int id, int seq)
{
    int item = id *1000 + seq; // Produz um item (simulado)
    printf("Produtor   %d: produzindo item %04d\n", id, item);
    return item;
}

void consume_item(int id, int item)
{
    printf("Consumidor %d: Consumindo item %04d\n", id, item);
}

void* producer(void* arg)
{
    int id = *((int*)arg);
    for (int i = 0; i < PRODUCE_ITEMS; i++)
    {
        int item = produce_item(id, i);

        while (buffer.count == BUFFER_SIZE) // Espera se o buffer estiver cheio - Espera Ativa (Busy Wait)
        {
            printf("Produtor %d: Buffer cheio - in: %d, out: %d, count: %d\n", id, buffer.in, buffer.out, buffer.count);
            usleep(1000);
        }

        buffer.items[buffer.in] = item; // Insere o item no buffer a cada iteracao
        buffer.in = (buffer.in + 1) % BUFFER_SIZE; // Atualiza a posição de inserção
        buffer.count++; // Incrementa o contador de items - nao atomico
        usleep(rand() % 1000); // Simula o tempo de produção
    }
    printf("Produtor %d: terminou de produzir\n\n", id);
    return NULL;
}

void* consumer(void* arg)
{
    int id = *((int*)arg);;
    for (int i = 0; i < CONSUME_ITEMS; i++)
    {
        while (buffer.count == 0) // se o buffer estiver vazio Espera Ativa (Busy Wait)
        {
            printf("Consumidor %d: Buffer vazio - in: %d, out: %d, count: %d\n", id, buffer.in, buffer.out, buffer.count);
            usleep(1000); // Espera se o buffer estiver vazio
        }
        int item = buffer.items[buffer.out];
        buffer.out = (buffer.out +1) % BUFFER_SIZE; // Atualiza a posição de remoção
        buffer.count--;

        consume_item(id, item);
        usleep(rand() % 1000); // Simula o tempo de consumo
    }
    printf("Consumidor %d: terminou de consumir\n\n", id);
    return NULL;
}

int main()
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); // Inicia medição

    pthread_t producers[2], consumers[2];
    int producer_ids[2] = {1,2};
    int consumer_ids[2] = {1,2};

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Criar threads produtoras
    for (int i =0; i < 2; i++)
    {
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }
    // Criar threads consumidoras
    for (int i=0; i<2; i++)
    {
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }
    // Esperar as threads produtoras terminarem
    for (int i =0; i < 2; i++)
    {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &end); // Finaliza medição
    double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("\nTempo total de execução: %.5f segundos\n", time_taken);
    return 0;
}

