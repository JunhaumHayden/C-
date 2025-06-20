#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// Funcao de ordenacao fornecida. Não pode alterar.
void bubble_sort(int *v, int tam){
    int i, j, temp, trocou;

    for(j = 0; j < tam - 1; j++){
        trocou = 0;
        for(i = 0; i < tam - 1; i++){
            if(v[i + 1] < v[i]){
                temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                trocou = 1;
            }
        }
        if(!trocou) break;
    }
}

// Funcao para imprimir um vetor. Não pode alterar.
void imprime_vet(unsigned int *v, int tam) {
    int i;
    for(i = 0; i < tam; i++)
        printf("%d ", v[i]);
    printf("\n");
}

// Funcao para ler os dados de um arquivo e armazenar em um vetor em memoria. Não pode alterar.
int le_vet(char *nome_arquivo, unsigned int *v, int tam) {
    FILE *arquivo;

    // Abre o arquivo
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    // Lê os números
    for (int i = 0; i < tam; i++)
        fscanf(arquivo, "%u", &v[i]);

    fclose(arquivo);

    return 1;
}

// --- ESTRUTURAS DE DADOS PARA A SOLUÇÃO PARALELA ---

// Struct para representar uma tarefa de ordenação
typedef struct {
    int id;
    int thread_id;
    unsigned int min_val;
    unsigned int max_val;
    unsigned int *valores;
    int qtd;
} Tarefa;

// Struct para argumentos da thread
typedef struct {
    //int thread_id;
    Tarefa *tarefas;
    int ntasks;
    int *proxima_tarefa;
    pthread_mutex_t *mutex;
} ArgsThread;
// ---  ---

// --- IMPLEMENTAÇÃO DA LÓGICA PARALELA ---
// Função executada por cada thread
void *executa_tarefa(void *arg) {
    ArgsThread *args = (ArgsThread *) arg;
    //otimizado
    while (1) {
        pthread_mutex_lock(args->mutex);      // Protege o acesso à variável compartilhada
        int idx = (*args->proxima_tarefa)++;  // Pega o índice da próxima tarefa a ser executada
        pthread_mutex_unlock(args->mutex);    // Libera o mutex
        // fim ----


        if (idx >= args->ntasks)
            break;


        Tarefa *t = &args->tarefas[idx];
        // Otimização: ignora tarefas que ficaram vazias na Etapa 1
        if (t->qtd == 0) {
            continue;
        }
        // Imprime o log de processamento exigido
        //printf("Thread %d processando tarefa %d\n", t->thread_id, t->id);
        //fflush(stdout); // Garante que o log seja impresso imediatamente

        // Ordena os elementos da tarefa usando a função fornecida
        bubble_sort((int *) t->valores, t->qtd);
    }
    pthread_exit(NULL);
}

// Funcao principal de ordenacao.
int sort_paralelo(unsigned int *vetor, unsigned int tam, unsigned int ntasks, unsigned int nthreads) {
    unsigned int min = vetor[0], max = vetor[0];
    for (unsigned int i = 1; i < tam; i++) {
        if (vetor[i] < min) min = vetor[i];
        if (vetor[i] > max) max = vetor[i];
    }

    unsigned int intervalo = (max - min + 1) / ntasks;
    if ((max - min + 1) % ntasks != 0)
        intervalo++;

    // Aloca tarefas
    Tarefa *tarefas = calloc(ntasks, sizeof(Tarefa));
    for (int i = 0; i < ntasks; i++) {
        tarefas[i].id = i;
        tarefas[i].thread_id = i % nthreads; // Distribui as tarefas entre as threads
        tarefas[i].min_val = min + i * intervalo;
        tarefas[i].max_val = tarefas[i].min_val + intervalo - 1;
        tarefas[i].valores = malloc(tam * sizeof(unsigned int)); // espaço máximo
        tarefas[i].qtd = 0;
    }

    // Distribui os valores nas tarefas
    for (unsigned int i = 0; i < tam; i++) {
        for (int j = 0; j < ntasks; j++) {
            if (vetor[i] >= tarefas[j].min_val && vetor[i] <= tarefas[j].max_val) {
                tarefas[j].valores[tarefas[j].qtd++] = vetor[i];
                break;
            }
        }
    }
    // --- ETAPA 2: PROCESSAMENTO PARALELO ---
    // Threads
    pthread_t threads[nthreads];
    int proxima_tarefa = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    ArgsThread args = { tarefas, ntasks, &proxima_tarefa, &mutex };

    for (unsigned int i = 0; i < nthreads; i++)
        pthread_create(&threads[i], NULL, executa_tarefa, &args);

    for (unsigned int i = 0; i < nthreads; i++)
        pthread_join(threads[i], NULL);
    // --- ETAPA 3: CONCATENAÇÃO DOS RESULTADOS ---
    // Concatena os resultados
    int idx = 0;
    for (int i = 0; i < ntasks; i++) {
        for (int j = 0; j < tarefas[i].qtd; j++) {
            vetor[idx++] = tarefas[i].valores[j];
        }
        free(tarefas[i].valores);
    }

    free(tarefas);
    return 1;
}

// Funcao principal do programa. Não pode alterar.
int main(int argc, char **argv) {

    // Verifica argumentos de entrada
    if (argc != 5) {
        fprintf(stderr, "Uso: %s <input> <nnumbers> <ntasks> <nthreads>\n", argv[0]);
        return 1;
    }

    // Argumentos de entrada
    unsigned int nnumbers = atoi(argv[2]);
    unsigned int ntasks = atoi(argv[3]);
    unsigned int nthreads = atoi(argv[4]);

    // Aloca vetor
    unsigned int *vetor = malloc(nnumbers * sizeof(unsigned int));
    if (vetor == NULL) {
        perror("Erro ao alocar memoria para o vetor");
        return 1;
    }

    // Variaveis de controle de tempo de ordenacao
    struct timeval inicio, fim;

    // Le os numeros do arquivo de entrada
    if (le_vet(argv[1], vetor, nnumbers) == 0){
        free(vetor);
        return 1;
    }

    // Imprime vetor desordenado
    imprime_vet(vetor, nnumbers);

    // Ordena os numeros considerando ntasks e nthreads
    gettimeofday(&inicio, NULL);
    sort_paralelo(vetor, nnumbers, ntasks, nthreads);
    gettimeofday(&fim, NULL);

    // Imprime vetor ordenado
    imprime_vet(vetor, nnumbers);

    // Desaloca vetor
    free(vetor);

    // Imprime o tempo de ordenacao
    printf("Tempo: %.6f segundos\n", fim.tv_sec - inicio.tv_sec + (fim.tv_usec - inicio.tv_usec) / 1e6);

    return 0;
}
