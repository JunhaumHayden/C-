/*
 *g++ -std=c++17 -Wall -o main main.cpp
*/

#include <iostream>
#include "linked_list.h"


int main() {
    structures::LinkedList<int> lista;
    constexpr int element = 27;
    // Inserindo elementos na lista
    for (int i = 0; i < element; i++) {
    lista.push_back(i);
    }

    lista.push_front(5);
    lista.insert(15, 2);  // [5, 10, 15, 20, 30]

    std::cout << "Lista original:\n";
    for (std::size_t i = 0; i < lista.size(); ++i) {
        std::cout << lista.at(i) << " ";
    }
    std::cout << "\n";

    // Removendo um elemento
    lista.remove(20);

    std::cout << "Após remover 20:\n";
    for (std::size_t i = 0; i < lista.size(); ++i) {
        std::cout << lista.at(i) << " ";
    }
    std::cout << "\n";

    // Clonando a lista
    structures::LinkedList<int> copia = lista.clone();
    std::cout << "Lista clonada:\n";
    for (std::size_t i = 0; i < copia.size(); ++i) {
        std::cout << copia.at(i) << " ";
    }
    std::cout << "\n";

    // Invertendo a lista original
    lista.invert();
    std::cout << "Lista invertida:\n";
    for (std::size_t i = 0; i < lista.size(); ++i) {
        std::cout << lista.at(i) << " ";
    }
    std::cout << "\n";

    // Slicing da lista (índices de 1 a 4 com step 2)
    structures::LinkedList<int> sublista = lista.slicing(1, 4, 2);
    std::cout << "Sublista slicing(1, 4, 2):\n";
    for (std::size_t i = 0; i < sublista.size(); ++i) {
        std::cout << sublista.at(i) << " ";
    }
    std::cout << "\n";

    structures::LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    structures::LinkedList<int> outra;
    outra.push_back(10);
    outra.push_back(20);
    outra.push_back(30);

    lista.append(&outra);  // resultado: [A, B, C, D, E, X, Y, Z]

    auto halves = list.halve();
    //halves.at(0) contém [1, 3, 5] (índices pares)
    // halves.at(1) contém [2, 4] (índices ímpares)
    //for (std::size_t i = 0; i < halves.size(); ++i) {
    //    std::cout << halves << " ";
    //}


    return 0;
}
