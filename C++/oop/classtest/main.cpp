#include <iostream>
#include <sstream> // Para formatar a saída como string
#include "carro.h"

int main() {
    Carro meuCarro("Toyota", 2022, 50000.0);

    string info = meuCarro.exibirInfo(); // Retorna a string
    cout << info << endl;

    // Modificando o valor
    meuCarro.setValor(60000.0);
    cout << meuCarro.exibirInfo() << endl;

    return 0;
}
