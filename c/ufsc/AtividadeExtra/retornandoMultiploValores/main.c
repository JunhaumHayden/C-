/*
Teste de vazamento de mamoria
gcc main.c -g -o main 
sudo leaks -atExit -- ./main 
*/

#include <stdio.h> // biblioteca para usar a função printf()
#include <stdlib.h> // biblioteca para usar a função rand()

typedef struct MinMax {
    int min;
    int max;
} MinMax;

MinMax *getMinMax(int *array, const int SIZE) {
    if (array == NULL || SIZE <= 0) {
        return NULL; // retorna NULL se o array for nulo ou o tamanho for menor ou igual a 0
    }
    MinMax *result = (MinMax *)malloc(sizeof(MinMax)); // aloca memória para a struct MinMax
    if (result == NULL) {
        perror("Erro ao alocar memória para a struct MinMax"); // imprime uma mensagem de erro
        exit(EXIT_FAILURE); // finaliza o programa
    }
    result->min = array[0]; // inicializa o min com o primeiro elemento do array
    result->max = array[0]; // inicializa o max com o primeiro elemento do array
    for (int i=1; i<SIZE; i++) {
        if (array[i] < result->min) {
            result->min = array[i];
        }
        if (array[i] > result->max) {
            result->max = array[i];
        }
    }
    return result; // retorna a struct MinMax
}
int main() {
   int vector[] = {10,3,5,20,8,-2,30}; // vetor de inteiros
   int SIZE = sizeof(vector)/sizeof(vector[0]); // tamanho do vetor
   MinMax *result = getMinMax(vector, SIZE); // chama a função getMinMax
   if (result != NULL) {
    printf("Valor Minimo: %d\n", result->min); // imprime o menor valor
    printf("Valor Maximo: %d\n", result->max); // imprime o maior valor
    free(result); // libera a memória alocada para a struct MinMax
   }else {
    printf("Erro ao retornar os valores min e max\n"); // imprime uma mensagem de erro
   }
   return 0; // finaliza o programa
}