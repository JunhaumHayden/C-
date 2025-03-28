#include <stdio.h>
#include "1672.c"
int main() {
    int accounts01[2][3]    = {{1,2,3},{4,5,6}};    // matriz de contas bancárias - 2 clientes e 3 contas
    int accountsSize01      = 2;                    // número de clientes (linhas) na matriz
    int accountsColSize01[] = {3,3};                // número de contas (colunas) para cada cliente

    int* accountsPointers01[2] = {accounts01[0], accounts01[1]}; // ponteiros para as contas dos clientes
    printf("Maior riqueza: %d\n", maximumWealth(accountsPointers01, accountsSize01, accountsColSize01)); // 15  

    int index=2;
    int vector[5]={1,2,3,4,5};
    printf("Conteudo Array com brackets: %d\n", vector[index]);
    printf("Conteudo Array com pointers: %d\n", *vector+index);
    printf("Conteudo Hex Array         : %02x\n", *vector+index);
    printf("Endereco Array             : %p\n", &vector[index]);
    
    int ccounts02[3][3] = { 
        {1,2,3},
        {3,2,1},
        {4,5,6}
    };
    // printf("Conteudo Array: %d\n", ccounts02[0][1]);
    // printf("Endereco Array: %p\n", &ccounts02[0][1]);
    // printf("Ponteiro Array: %d\n", *ccounts02[0]);
    // printf("Ponteiro Array: %d\n", *ccounts02[1]);
    // printf("Ponteiro Array: %d\n", *ccounts02[2]);

    int row1[] = {1, 2, 3};
    int row2[] = {3, 2, 1};
    int row3[] = {4, 5, 6};
    int* ccounts03[] = {row1, row2, row3};

    int* accounts04[3]; // declarando um array com 3 posições de ponteiros para int

    int a = 5, b = 10, c = 15;

    // Atribuindo os ponteiros no array
    accounts04[0] = &a; // forma1 - Atribuindo array ([]) diretamente
    printf("%d\n", *accounts04[0]);  // Imprime 5
    *accounts04 = &a; // forma2 - Atribuindo o ponteiro (*) diretamente
    // a forma 1 é um alias da forma 2
    printf("%d\n", *accounts04[0]);  // Imprime 5


    accounts04[1] = &b;
    printf("%d\n", *accounts04[1]);
    *(accounts04+1) = &b;
    printf("%d\n", *accounts04[1]);

    accounts04[2] = &c;
    printf("%d\n", *accounts04[2]);  // Imprime 15


    // uma matriz com número variável de colunas
    int* accounts[3];
    accounts[0] = (int[]){2, 8};     // Cliente 0 tem 2 contas
    accounts[1] = (int[]){7, 1, 3};  // Cliente 1 tem 3 contas
    accounts[2] = (int[]){1, 9, 5, 4}; // Cliente 2 tem 4 contas
    //accountsColSize seria:
    int accountsColSize[] = {2, 3, 4};
    printf("Maior riqueza: %d\n", maximumWealth(accounts, 3, accountsColSize)); // 19
    return 0;

}