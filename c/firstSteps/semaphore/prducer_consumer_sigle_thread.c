#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 5  // Tamanho pequeno para facilitar visualização

// Estrutura do buffer compartilhado
typedef struct {
    int items[BUFFER_SIZE];
    int in;     // Próxima posição de inserção
    int out;    // Próxima posição de remoção
    int count;  // Número de itens no buffer
} Buffer;

Buffer buffer = { .in = 0, .out = 0, .count = 0 };

// Função auxiliar para exibir o estado do buffer
void print_buffer() {
    printf("Buffer [");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i < buffer.count) {
            int pos = (buffer.out + i) % BUFFER_SIZE;
            printf("%d", buffer.items[pos]);
        } else {
            printf(" ");
        }
        if (i < BUFFER_SIZE - 1) printf("|");
    }
    printf("] (count: %d)\n", buffer.count);
}

// Produz um item (simulado)
int produce_item() {
    static int item = 0; //A variável item é declarada como static int. Isso significa que ela mantém seu valor entre chamadas da função, permitindo que o número gerado seja incrementado a cada execução.
    printf("Produzindo item: %d\n", ++item);
    return item;
}


// Consome um item (simulado)
void consume_item(int item) {
    printf("Consumindo item: %d\n", item);
}

// Insere item no buffer
void insert_item(int item) {
    if (buffer.count == BUFFER_SIZE) {
        printf("ERRO: Buffer cheio, não pode inserir\n");
        return;
    }

    buffer.items[buffer.in] = item;
    buffer.in = (buffer.in + 1) % BUFFER_SIZE;
    buffer.count++;
    printf("Inserido item %d - ", item);
    print_buffer();
}

// Remove item do buffer
int remove_item() {
    if (buffer.count == 0) {
        printf("ERRO: Buffer vazio, não pode remover\n");
        return -1;
    }

    int item = buffer.items[buffer.out];
    buffer.out = (buffer.out + 1) % BUFFER_SIZE;
    buffer.count--;
    printf("Removido item %d - ", item);
    print_buffer();
    return item;
}

// Simula o produtor
void producer() {
    for (int i = 0; i < 10; i++) {  // Produz 10 itens
        int item = produce_item();
        insert_item(item);
    }
}

// Simula o consumidor
void consumer() {
    for (int i = 0; i < 10; i++) {  // Consome 10 itens
        int item = remove_item();
        if (item != -1) {
            consume_item(item);
        }
    }
}

int main() {
    printf("=== Início da Simulação Produtor-Consumidor ===\n");

    // Executa produtor e consumidor em sequência
    printf("\nFase de produção:\n");
    producer();

    printf("\nFase de consumo:\n");
    consumer();

    printf("\n=== Fim da Simulação ===\n");
    return 0;
}