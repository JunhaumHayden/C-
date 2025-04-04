// Copyright [2025] <Carlos Benedito Hayden de Albuquerque Junior>
#ifndef CHAVES_H
#define CHAVES_H

#include "./array_stack.h"
#include <string>

bool verificaChaves(std::string trecho_programa) {
    bool resposta = true;
    int tamanho = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);

    for (int i = 0; i < tamanho; i++) {
        // Se encontrar '{', empilha
        if (trecho_programa[i] == '{') {
            pilha.push('{');
        }
        // Se encontrar '}', verifica se há um '{' correspondente
        if (trecho_programa[i] == '}') {
            if (pilha.empty()) {
                resposta = false;  // Não há '{' correspondente
                break;  // Interrompe o loop pois já há erro
            }
            pilha.pop();  // Remove '{' correspondente
        }
    }

    // Se ainda houver '{' na pilha, há erro de aninhamento
    if (!pilha.empty()) {
        resposta = false;
    }

    return resposta;
}


#endif // CHAVES_H
