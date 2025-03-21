#include <iostream>
#include "includes/iniciais.h"

int main() {
    // Call functions from iniciais.h
    int vetorEntrada[5]={10, 50, 30, 70, 20};
    int N = 5;
    int max = maximo(vetorEntrada, N);
    int pos = posicao(vetorEntrada, N);
    maxpos MP = maximo_posicao(vetorEntrada, N);


    std::cout << "Valor Maximo do vetor: " << max << std::endl;
    std::cout << "Posicao do valor maximo: " << pos << std::endl;
    std::cout << "max: " << MP.max << std::endl;
    std::cout << "pos: " << MP.pos << std::endl;

    return 0;
}