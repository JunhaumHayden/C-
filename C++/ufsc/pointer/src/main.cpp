#include <iostream>
#include "atribuicao.h"

int main() {
    int i = 15;  // Variável local ao main
    int* p = &i; // Atribuição local
    *p = 20;     // Manipulação de ponteiro
    std::cout << "Novo valor de i: " << i << std::endl;

    atribuicao();
    return 0;
}