// trie.cpp
#include "trie.hpp"
#include <cstddef>

Trie::Trie() {
    raiz = new TrieNode();
}

Trie::~Trie() {
    liberar(raiz);
}

void Trie::liberar(TrieNode* no) {
    for (auto& filho : no->filhos) {
        if (filho) liberar(filho);
    }
    delete no;
}

void Trie::inserir(const std::string& palavra, unsigned long pos, unsigned long comp) {
    TrieNode* atual = raiz;
    for (char c : palavra) {
        int idx = c - 'a';
        if (!atual->filhos[idx]) {
            atual->filhos[idx] = new TrieNode();
        }
        atual = atual->filhos[idx];
        atual->prefixCount++; // aumenta a contagem de prefixos
    }
    atual->fimPalavra = true;
    atual->posicao = pos;
    atual->comprimento = comp;
}

int Trie::contarPrefixos(const std::string& prefixo) const {
    TrieNode* atual = raiz;
    for (char c : prefixo) {
        int idx = c - 'a';
        if (!atual->filhos[idx]) return 0;
        atual = atual->filhos[idx];
    }
    return atual->prefixCount;
}

bool Trie::buscarPalavra(const std::string& palavra, unsigned long& pos, unsigned long& comp) const {
    TrieNode* atual = raiz;
    for (char c : palavra) {
        int idx = c - 'a';
        if (!atual->filhos[idx]) return false;
        atual = atual->filhos[idx];
    }
    if (atual->fimPalavra) {
        pos = atual->posicao;
        comp = atual->comprimento;
        return true;
    }
    return false;
}
