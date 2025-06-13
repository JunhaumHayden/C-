#include "NoRB.h"

int main() {
    NoRB<int>* raiz = nullptr;

    std::vector<int> valores = {10, 20, 30, 15, 5, 1};
    for (int val : valores) {
        raiz = raiz ? raiz->inserir(val, raiz) : new NoRB<int>(val);
    }

    std::cout << "Árvore em ordem: ";
    raiz->emOrdem(raiz);
    std::cout << std::endl;

    raiz = raiz->remover(raiz, 15);
    std::cout << "Após remover 15: ";
    raiz->emOrdem(raiz);
    std::cout << std::endl;

    return 0;
}
