//
// Created by Junhaum Hayden on 5/5/25.
//comparar o comportamento de um array C tradicional com std::vector do C++ usando acesso direto ([]) e acesso seguro (.at()), especialmente quando tentamos acessar um índice inválido.
//
#include <iostream>
#include <vector>

int main() {
    // Array tradicional (C-style)
    int vetorC[4] = {0, 1, 2, 3};

    // std::vector do C++
    std::vector<int> vetorCpp = {0, 1, 2, 3};

    std::cout << "Acesso com vetorC[10] (array tradicional): ";
    std::cout << vetorC[10] << std::endl;  // comportamento indefinido

    std::cout << "Acesso com vetorCpp[10] (std::vector com []): ";
    std::cout << vetorCpp[10] << std::endl;  // comportamento indefinido também

    std::cout << "Acesso com vetorCpp.at(10) (std::vector com at()): ";
    try {
        std::cout << vetorCpp.at(10) << std::endl;  // lança exceção
    } catch (const std::out_of_range& e) {
        std::cout << "Exceção capturada: " << e.what() << std::endl;
    }

    return 0;
}
