#include <iostream>
#include <vector>
#include "solution.h"

using namespace std;

int main() {
    //Instancia da classe Solution
    Solution solution;
    // Definição do vetor de contas
    vector<vector<int> > accounts = {
        {1,2,3},    // Cliente 1 -> Total: 6
        {4,5,6},    // Cliente 2 -> Total: 15
        {7,8,9}     // Cliente 3 -> Total: 24
    };
    // Chamada do método maximumWealth
    cout << "A maior riqueza de um cliente é: " << solution.maximumWealth(accounts) << endl;
    return 0;
}