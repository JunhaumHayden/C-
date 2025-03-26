/*
Pointer
Com o objetivo de evitar o estouro da pilha de execução, podemos alocar memória no heap, que é uma região de memória que é compartilhada por todos os processos em execução e inicia nos endereços mais baixos e vão incrementando em direção ao meio (encontro com a Stack). A memória alocada no heap é liberada manualmente pelo programador, ao contrário da memória alocada na pilha de execução, que é liberada automaticamente quando a função que alocou a memória retorna.

As linguagens de programaçao alocam os blocos de dados de objetos instanciados na heap, pois a quantidade de memória necessária para armazenar esses objetos é desconhecida até o momento da execução, e na Stack são alocados apenas os ponteiros para esses objetos (tamanho fixo de 4 bytes independente de quanto espaço o objeto irá precisar).


*/
#include <stdio.h>
#include <stdlib.h> //biblioteca que da acesso a funcao malloc
// fornece uma variedade de funções utilitárias para realizar operações de alocação de memória, controle de processos, conversões e outras tarefas gerais. Aqui estão algumas das funções mais comuns fornecidas por stdlib.h:
// Alocação de Memória: malloc(), calloc(), realloc(), free()
// Conversões: atoi(), atof(), atol(), strtol(), strtod()
// Controle de Processos: exit(), abort(), system()
// Gerenciamento de Ambiente: getenv(), putenv()
// Outras Funções Utilitárias:abs(), rand(), srand(), bsearch(), qsort()
#include <string.h>
// fornece funções para manipulação de strings (cadeias de caracteres). Algumas das funções mais comuns incluídas nesta biblioteca são:
// strcpy: copia uma string para outra.
// strlen: retorna o comprimento de uma string.
// strcmp: compara duas strings.
// strcat: concatena duas strings.
// strncpy: copia um número específico de caracteres de uma string para outra.

int main() {
    char hello[] = "Hello World";
    printf("from main: %p\n", &hello);
    
    char *hello2 = (char *)malloc(sizeof(hello)); 
    // *hello2 é um ponteiro para char que foi alocado no heap. Aponta para o endereço de memoria do primeiro byte do bloco de memoria alocado no heap (pela funçao malloc())onde vai estar a string. Ou seja, vai armazenar  o endereço que é um numero de 4 bytes (64-bits). menor que o tamanho do vetor hello que foi alocado na stack.
    // a funcao malloc retorna um ponteiro para o primeiro byte do bloco de memoria alocado. Recebe como argumento o tamanho em bytes para reservar no heap. Neste caso do mesmo tamanho do vetor hello que foi alocado na stack.
    // o ponteiro é do tipo void, por isso é necessário fazer o cast para o tipo desejado.
    // a funcao sizeof() retorna o tamanho em bytes do tipo de dado passado como argumento. No caso o tamanho do vetor hello que foi alocado da stack (12 bytes que poderia ser passado direto no argumento).
    strcpy(hello2, hello); // unica duplicata no codigo. Copia o conteudo do vetor hello para o endereço apontado por hello2 na heap(conteudo de hello).
    printf("hello2: %p\n", hello2);

    char *hello3 = hello2 +6;
    // hello3 é um ponteiro para char que aponta para o endereço de memoria do 6 byte do bloco de memoria alocado no heap. 
    // Sabendo que hello2 aponta para o primeiro byte do bloco de memoria alocado no heap (hello world), hello3 aponta para o 6 byte do bloco de memoria alocado no heap(world = primeiro endereço + 6 bytes, pois sabemos que cada posiçao do array hello ocupa extamente 1 byte e acaba quando encontra o caracter nulo \0).
    printf("from hello2: %s\n", hello2);
    printf("from hello3: %s\n", hello3);

    free(hello2);
    return 0;
}
