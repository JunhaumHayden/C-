// trie.hpp
#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <vector>

struct TrieNode {
    TrieNode* filhos[26] = {nullptr};
    bool fimPalavra = false;
    unsigned long posicao = 0;
    unsigned long comprimento = 0;
    int prefixCount = 0; // conta quantas palavras têm este prefixo
};

class Trie {
public:
    Trie();
    ~Trie();
    void inserir(const std::string& palavra, unsigned long pos, unsigned long comp);
    int contarPrefixos(const std::string& prefixo) const;
    bool buscarPalavra(const std::string& palavra, unsigned long& pos, unsigned long& comp) const;
    void liberar(TrieNode* no);

private:
    TrieNode* raiz;
};

#endif
