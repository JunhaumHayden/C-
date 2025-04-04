#include <stdio.h>
#include <stdlib.h> // biblioteca para usar a função malloc() e free(), exit()

// Declarar a Struct MinMax
typedef struct MinMax {
    int min;
    int max;
} MinMax;

// Protótipo dafuncao

MinMax *getMinMax(int* array, const int SIZE) {
// Tratar excecao: vetor vazio (NULL) ou tamanho menor ou igual a 0
    if (array == NULL || SIZE <= 0) {
        return NULL; 
    }
// Alocar a memoria para a Struct de retorno
    MinMax* result = (MinMax *)malloc(sizeof(MinMax));
// Tratar exececao: falha na alocacao de memoria
    if (result == NULL) {
        perror("Erro ao alocar memória para a struct MinMax");
        exit(EXIT_FAILURE);
    } 
    // Buscar o min e o max no vetor
    // result->min = array[0]; // Sintaxe mais utilizada (curta)
    (*result).min = array[0]; // Sintaxe alternativa
    (*result).max = array[0]; // Sintaxe alternativa

    for (int i = 1; i < SIZE; i++) {
        if (array[i] < (*result).min) {
            (*result).min = array[i];
        }
        if (array[i] > (*result).max) {
            (*result).max = array[i];
        }
    }
    return result; // Retornar o ponteiro para a struct MinMax
}

int main() {
    int vector[] = {10,3,5,20,8,-2,30};
    int SIZE = sizeof(vector) / sizeof(vector[0]); // Tamanho do vetor - tamanho total / tamanho de um elemento
    MinMax* result = getMinMax(vector, SIZE);
    if (result !=NULL) {
        printf("Valor Minimo: %d\n", result->min);
        printf("Valor Maximo: %d\n", result->max);
        free(result);
    }
}
