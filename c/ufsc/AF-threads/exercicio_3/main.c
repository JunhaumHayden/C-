#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
/*
Em outro caso de programador desaparecido, você deve paralelizar um programa que calcula o produto escalar de dois vetores:

./program 1 a b
Produto escalar: -9
O primeiro argumento ("1" é o número de threads a serem usadas para computação. Assim como no exercício 2, a sintaxe gen:N pode ser usada para testar sua implementação com vetores aleatórios grandes. Lembre que:

O produto escalar é o somatório dos produtos entre os elementos pareados dos vetores, ou seja, sum += a[i] * b[i], para to_do elemento i dos vetores a e b.
Os arquivos a e b, com vetores pequenos, estão incluídos no esqueleto fornecido.
Evite usar variáveis globais sempre que possível.
 */
// Lê o conteúdo do arquivo filename e retorna um vetor E o tamanho dele
// Se filename for da forma "gen:%d", gera um vetor aleatório com %d elementos
//
// +-------> retorno da função, ponteiro para vetor malloc()ado e preenchido
// | 
// |         tamanho do vetor (usado <-----+
// |         como 2o retorno)              |
// v                                       v
double* load_vector(const char* filename, int* out_size);


// Avalia se o prod_escalar é o produto escalar dos vetores a e b. Assume-se
// que ambos a e b sejam vetores de tamanho size.
void avaliar(double* a, double* b, int size, double prod_escalar);

typedef struct {
    double* a;
    double* b;
    int start;
    int end;
    long double partial_sum;
} ThreadData;

void* thread_work(void* arg) {
  ThreadData* data = (ThreadData*)arg;
  (*data).partial_sum = 0;
    for (int i = (*data).start; i < (*data).end; ++i) {
        (*data).partial_sum += (*data).a[i] * (*data).b[i];
    }
    return NULL;
}
int main(int argc, char* argv[]) {
    srand(time(NULL));

    //Temos argumentos suficientes?
    if(argc < 4) {
        printf("Uso: %s n_threads a_file b_file\n"
               "    n_threads    número de threads a serem usadas na computação\n"
               "    *_file       caminho de arquivo ou uma expressão com a forma gen:N,\n"
               "                 representando um vetor aleatório de tamanho N\n", 
               argv[0]);
        return 1;
    }
  
    //Quantas threads?
    int n_threads = atoi(argv[1]);
    if (!n_threads) {
        printf("Número de threads deve ser > 0\n");
        return 1;
    }
    //Lê números de arquivos para vetores alocados com malloc
    int a_size = 0, b_size = 0;
    double* a = load_vector(argv[2], &a_size);
    if (!a) {
        //load_vector não conseguiu abrir o arquivo
        printf("Erro ao ler arquivo %s\n", argv[2]);
        return 1;
    }
    double* b = load_vector(argv[3], &b_size);
    if (!b) {
        printf("Erro ao ler arquivo %s\n", argv[3]);
        return 1;
    }
    
    //Garante que entradas são compatíveis
    if (a_size != b_size) {
        printf("Vetores a e b tem tamanhos diferentes! (%d != %d)\n", a_size, b_size);
        return 1;
    }

    //Calcula produto escalar. Paralelize essa parte
    double result = 0;
    // for (int i = 0; i < a_size; ++i)
    //    result += a[i] * b[i];

    if (n_threads > a_size) { // se o número de threads for maior que o tamanho do vetor, reduz o número de threads
        n_threads = a_size;
    }
    pthread_t threads[n_threads]; // declando um vetor de threads
    ThreadData thread_data[n_threads]; // declando um vetor de dados para cada thread

    int chunk_size = a_size / n_threads; // tamanho do chunk para cada thread
    int remainder = a_size % n_threads; // elementos restantes
    int start = 0; // inicializando o índice de início

    for (int i = 0; i < n_threads; i++) {
        thread_data[i].a = a; // ponteiro para o vetor a
        thread_data[i].b = b; // ponteiro para o vetor b
        thread_data[i].start = start; // índice de início
        thread_data[i].end = start + chunk_size + (i < remainder ? 1 : 0); // índice de fim
        thread_data[i].partial_sum = 0; // inicializando a soma parcial

        pthread_create(&threads[i], NULL, thread_work, &thread_data[i]); // criando a thread
        start = thread_data[i].end; // atualizando o índice de início
    }
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL); // aguardando a thread terminar
        result += thread_data[i].partial_sum; // somando o resultado parcial
    }

    //    +---------------------------------+
    // ** | IMPORTANTE: avalia o resultado! | **
    //    +---------------------------------+
    avaliar(a, b, a_size, result);

    //Libera memória
    free(a);
    free(b);

    return 0;
}
