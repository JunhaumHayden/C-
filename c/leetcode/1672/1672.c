/*
1. Percorrer cada cliente (linha da matriz): para cada cliente, somar o valor de todas as contas.
2. Armazenar a maior riqueza encontrada: Manter uma variavel maxWealth que armazena a maior riqueza encontrada até o momento.
3. Retornar a maior riqueza encontrada.
int** accounts: matriz de contas bancárias, onde accounts[i][j] representa o valor da j-ésima conta do i-ésimo cliente.
int accountsSize: número de clientes (linhas) na matriz.
int* accountsColSize: número de contas (colunas) para cada cliente.
*/
#include <stdio.h>
int maximumWealth(int** accounts, int accountsSize, int* accountsColSize) {
    int maxWealth = 0;

    for (int row =0; row < accountsSize; row++) {
        int wealth = 0;
        // printf(accounts[row]);
        for (int col = 0; col < accountsColSize[row]; col++) {
            // print(accounts[row][col]);
            wealth += accounts[row][col];
        }
        if (wealth > maxWealth) {
            maxWealth = wealth;
        }
    }
    return maxWealth;
}