#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <_time.h>
#include <pthread/pthread.h>
#include <sys/_pthread/_pthread_t.h>


#define BUFFER_SIZE 5      // Tamanho pequeno para facilitar visualização
#define PRODUCER_ITEMS 20  // Número de items a serem produzidos
#define CONSUMER_ITEMS 20  // Número de items a serem consumidos

// Estrutura do buffer compartilhado
typedef struct
{
    int items[BUFFER_SIZE];
    int in;
    int out;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond_producer; // Variável de condição para o produtor
    pthread_cond_t cond_consumer; // Variável de condição para o consumidor
} Buffer;

// inicializacao do buffer compartilhado
Buffer buffer = {
    .in = 0,
    .out = 0,
    .count = 0,
    .mutex =PTHREAD_MUTEX_INITIALIZER,
    .cond_producer = PTHREAD_COND_INITIALIZER,
    .cond_consumer = PTHREAD_COND_INITIALIZER
};

int produce_item(int id, int seq)
{
    int item = id *1000 + seq; // Produz um item (simulado)
    printf("Produtor   %d: produzindo item %04d\n", id, item);
    usleep(rand() % 100000); // Simula trabalho
    return item;
}

void consume_item(int id, int item)
{
    printf("Consumidor %d: Consumindo item %04d\n", id, item);
    usleep(rand() % 100000); // Simula trabalho
}

void* producer(void* arg)
{
    int id = *((int*)arg);
    for (int i = 0; i < PRODUCER_ITEMS; i++)
    {
        int item = produce_item(id, i);

        pthread_mutex_lock(&buffer.mutex); // Adiciona o mutex para proteger a seção crítica
        printf("\tProdutor %d: travou Mutex\n", id);
        while (buffer.count == BUFFER_SIZE) // Espera se o buffer estiver cheio - Espera Ativa (Busy Wait) sem mutex
        {
            printf("Produtor %d: Buffer cheio - in: %d, out: %d, count: %d\n", id, buffer.in, buffer.out, buffer.count);
            pthread_cond_wait(&buffer.cond_producer, &buffer.mutex); // Espera até que o buffer tenha espaço
        }

        buffer.items[buffer.in] = item; // Insere o item no buffer a cada iteracao
        buffer.in = (buffer.in + 1) % BUFFER_SIZE; // Atualiza a posição de inserção
        buffer.count++; // Incrementa o contador de items - nao atomico
        printf("Produtor %d: Inseriu item %04d (count: %d)\n", id, item, buffer.count);
        // buffer ao menos com 1 posicao ocupada
        if (buffer.count == 1) // Se o buffer estava vazio, sinaliza o consumidor
        {
            pthread_cond_signal(&buffer.cond_consumer);
        }
        pthread_mutex_unlock(&buffer.mutex);
        printf("\tProdutor %d: Destravou Mutex\n", id);
    }
    printf("Produtor %d: terminou de produzir\n\n", id);
    return NULL;
}

void* consumer(void* arg)
{
    int id = *((int*)arg);;
    for (int i = 0; i < CONSUMER_ITEMS; i++)
    {
        pthread_mutex_lock(&buffer.mutex); // Adiciona o mutex para proteger a seção crítica
        printf("\tConsumidor %d: travou Mutex\n", id);
        while (buffer.count == 0) // se o buffer estiver vazio Espera Ativa (Busy Wait)
        {
            printf("Consumidor %d: Buffer vazio - in: %d, out: %d, count: %d\n", id, buffer.in, buffer.out, buffer.count);
            pthread_cond_wait(&buffer.cond_consumer, &buffer.mutex); // Espera até que o buffer tenha espaço
        }
        int item = buffer.items[buffer.out];
        buffer.out = (buffer.out +1) % BUFFER_SIZE; // Atualiza a posição de remoção
        buffer.count--;
        printf("Consumidor %d: Removeu item %04d (count: %d)\n", id, item, buffer.count);
        // Se o buffer com ao menos 1 posicao livre), sinaliza o produtor
        if (buffer.count == BUFFER_SIZE - 1) // Se o buffer estava cheio, sinaliza o produtor
        {
            pthread_cond_signal(&buffer.cond_producer);
        }
        pthread_mutex_unlock(&buffer.mutex);
        printf("\tConsumidor %d: Destravou Mutex\n", id);

        consume_item(id, item);
    }
    printf("Consumidor %d: terminou de consumir\n\n", id);
    return NULL;
}

int main() {
    pthread_t producers[2], consumers[2];
    int producer_ids[2] = {1, 2};
    int consumer_ids[2] = {1, 2};
    struct timespec start, end;

    srand(time(NULL));
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Cria threads produtoras
    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // Cria threads consumidoras
    for (int i = 0; i < 2; i++) {
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // Aguarda threads
    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("\nTempo total de execução: %.5f segundos\n", time_taken);

    // Destroi mutex e variáveis de condição
    pthread_mutex_destroy(&buffer.mutex);
    pthread_cond_destroy(&buffer.cond_producer);
    pthread_cond_destroy(&buffer.cond_consumer);

    return 0;
}