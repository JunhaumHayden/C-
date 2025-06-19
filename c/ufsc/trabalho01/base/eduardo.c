#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

// --- ESTRUTURAS DE DADOS PARA A SOLUÇÃO PARALELA ---

// Estrutura para representar uma tarefa (bucket/balde)
typedef struct {
    unsigned int *numbers; // Vetor dinâmico para os números da tarefa
    int count;             // Quantidade de números na tarefa
    int capacity;          // Capacidade atual do vetor 'numbers'
} Task;

// Estrutura para os argumentos que serão passados para cada thread
typedef struct {
    int thread_id;
    Task *tasks;
    int ntasks;
    pthread_mutex_t *task_mutex; // Mutex para acesso seguro ao contador de tarefas
    int *next_task_id;           // Ponteiro para o ID da próxima tarefa a ser processada
} ThreadArgs;


// --- FUNÇÕES FORNECIDAS (NÃO PODEM SER ALTERADAS) ---

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

// Funcao para ler os dados de um arquivo e armazenar em um vetor em memoroa. Não pode alterar.
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

// --- IMPLEMENTAÇÃO DA LÓGICA PARALELA ---

// Função que será executada por cada uma das threads trabalhadoras
void* worker_thread(void *args) {
    ThreadArgs *thread_args = (ThreadArgs*) args;
    int task_id;

    // Loop para consumir tarefas da "fila"
    while (1) {
        // Bloqueia o mutex para pegar a próxima tarefa de forma atômica e segura
        pthread_mutex_lock(thread_args->task_mutex);
        task_id = *(thread_args->next_task_id);
        if (task_id < thread_args->ntasks) {
            (*(thread_args->next_task_id))++;
        }
        pthread_mutex_unlock(thread_args->task_mutex);

        // Se o ID da tarefa for maior ou igual ao n. de tarefas, não há mais trabalho
        if (task_id >= thread_args->ntasks) {
            break; 
        }

        Task *current_task = &thread_args->tasks[task_id];

        // Otimização: ignora tarefas que ficaram vazias na Etapa 1
        if (current_task->count == 0) {
            continue;
        }

        // Imprime o log de processamento exigido
        printf("Thread %d processando tarefa %d\n", thread_args->thread_id, task_id);
        fflush(stdout); // Garante que o log seja impresso imediatamente

        // Ordena os elementos da tarefa usando a função fornecida
        // É necessário fazer um cast para (int*) pois bubble_sort espera um ponteiro para int
        bubble_sort((int*)current_task->numbers, current_task->count);
    }

    pthread_exit(NULL);
}


// Funcao principal de ordenacao. Deve ser implementada com base nas informacoes fornecidas no enunciado do trabalho.
// Os numeros ordenados deverao ser armazenanos no proprio "vetor".
int sort_paralelo(unsigned int *vetor, unsigned int tam, unsigned int ntasks, unsigned int nthreads) {
    // Validação dos parâmetros de entrada, conforme solicitado
    if (nthreads < 1 || ntasks > tam) {
        fprintf(stderr, "Erro: O numero de threads deve ser >= 1 e o numero de tarefas deve ser <= ao tamanho do vetor.\n");
        return 0;
    }

    // --- ETAPA 1: DISTRIBUIÇÃO DAS TAREFAS ---

    // Aloca memória para as tarefas (baldes)
    Task *tasks = (Task*) calloc(ntasks, sizeof(Task));
    // Aloca memória para guardar os limites dos intervalos de cada tarefa
    int *task_ranges = (int*) malloc((ntasks + 1) * sizeof(int));

    // Calcula as faixas de valores para cada tarefa, distribuindo o resto da divisão
    int base_interval = tam / ntasks;
    int remainder = tam % ntasks;
    task_ranges[0] = 0;
    for (int i = 1; i <= ntasks; i++) {
        // As primeiras 'remainder' tarefas terão tamanho 'base_interval + 1'
        task_ranges[i] = task_ranges[i - 1] + base_interval + (i - 1 < remainder ? 1 : 0);
    }
    
    // Itera sobre o vetor original e distribui cada número na sua respectiva tarefa
    for (unsigned int i = 0; i < tam; i++) {
        unsigned int value = vetor[i];
        for (int j = 0; j < ntasks; j++) {
            // Verifica se o valor pertence ao intervalo [início, fim) da tarefa j
            if (value >= (unsigned int)task_ranges[j] && value < (unsigned int)task_ranges[j+1]) {
                // Adiciona o número à tarefa 'j', realocando memória se necessário
                if (tasks[j].count >= tasks[j].capacity) {
                    tasks[j].capacity = (tasks[j].capacity == 0) ? 10 : tasks[j].capacity * 2;
                    tasks[j].numbers = (unsigned int*) realloc(tasks[j].numbers, tasks[j].capacity * sizeof(unsigned int));
                }
                tasks[j].numbers[tasks[j].count++] = value;
                break; // Passa para o próximo número do vetor original
            }
        }
    }
    free(task_ranges);

    // --- ETAPA 2: PROCESSAMENTO PARALELO ---
    pthread_t *threads = (pthread_t*) malloc(nthreads * sizeof(pthread_t));
    ThreadArgs *thread_args = (ThreadArgs*) malloc(nthreads * sizeof(ThreadArgs));
    
    pthread_mutex_t task_mutex;
    pthread_mutex_init(&task_mutex, NULL);
    int next_task_id = 0;

    // Cria as threads
    for (unsigned int i = 0; i < nthreads; i++) {
        thread_args[i].thread_id = i;
        thread_args[i].tasks = tasks;
        thread_args[i].ntasks = ntasks;
        thread_args[i].task_mutex = &task_mutex;
        thread_args[i].next_task_id = &next_task_id;
        pthread_create(&threads[i], NULL, worker_thread, &thread_args[i]);
    }

    // Aguarda todas as threads terminarem sua execução
    for (unsigned int i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
    }

    // --- ETAPA 3: CONCATENAÇÃO DOS RESULTADOS ---
    int k = 0; // Índice para o vetor original (resultado final)
    // Itera sobre as tarefas em ordem (0, 1, 2, ...)
    for (unsigned int i = 0; i < ntasks; i++) {
        // Copia os números (já ordenados) de cada tarefa de volta para o vetor original
        for (int j = 0; j < tasks[i].count; j++) {
            vetor[k++] = tasks[i].numbers[j];
        }
    }
    
    // --- LIMPEZA DA MEMÓRIA ALOCADA ---
    for (unsigned int i = 0; i < ntasks; i++) {
        if (tasks[i].numbers != NULL) {
            free(tasks[i].numbers);
        }
    }
    free(tasks);
    free(threads);
    free(thread_args);
    pthread_mutex_destroy(&task_mutex);
    
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
    if (le_vet(argv[1], vetor, nnumbers) == 0) {
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
