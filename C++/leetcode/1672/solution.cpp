#include "solution.h"
#include <algorithm> // Para a função max()

int Solution::maximumWealth(vector<vector<int>>& accounts) {
    int response = 0;
    for (int i = 0; i < accounts.size(); i++) {
        int temporary = 0;
        for (int j = 0; j < accounts[i].size(); j++) {
            temporary += accounts[i][j];
        }
        response = max(response, temporary);
    }
    return response;


    // Complexidade de Tempo e Espaço  
    // Tempo: O(m×n), onde m é o número de clientes e n é o número de contas por cliente.
    // Percorremos todos os elementos da matriz uma única vez.
    // Espaço: O(1), pois usamos apenas variáveis auxiliares.
}
