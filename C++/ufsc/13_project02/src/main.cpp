// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include "trie.hpp"

void carregarDicionario(const std::string& caminho, Trie& trie) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << caminho << std::endl;
        return;
    }
    std::string linha;
    unsigned long pos = 0;

    while (std::getline(arquivo, linha)) {
        size_t ini = linha.find('[');
        size_t fim = linha.find(']');
        if (ini != std::string::npos && fim != std::string::npos) {
            std::string palavra = linha.substr(ini + 1, fim - ini - 1);
            trie.inserir(palavra, pos, linha.length());
        }
        pos += linha.length() + 1; // +1 por causa do '\n' consumido
    }
}

int main() {
    std::string nomeArquivo;
    std::cin >> nomeArquivo;

    Trie trie;
    carregarDicionario(nomeArquivo, trie);

    std::string palavra;
    while (std::cin >> palavra && palavra != "0") {
        int qtd = trie.contarPrefixos(palavra);
        if (qtd == 0) {
            std::cout << palavra << " is not prefix" << std::endl;
        } else {
            std::cout << palavra << " is prefix of " << qtd << " words" << std::endl;
            unsigned long pos, comp;
            if (trie.buscarPalavra(palavra, pos, comp)) {
                std::cout << palavra << " is at (" << pos << "," << comp << ")" << std::endl;
            }
        }
    }

    return 0;
}
