// Copyright [2025] <Carlos Benedito Hayden de Albuquerque Junior>
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>   // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures {

template <typename T>
//! CLASSE PILHA
class ArrayStack {
public:
    //! construtor simples
    ArrayStack();
    //! construtor com parametro tamanho
    explicit ArrayStack(std::size_t max);
    //! destrutor
    ~ArrayStack();
    //! metodo empilha
    void push(const T& data);
    //! metodo desempilha
    T pop();
    //! metodo retorna o topo
    T& top();
    //! metodo limpa pilha
    void clear();
    //! metodo retorna tamanho
    std::size_t size() const;
    //! metodo retorna capacidade maxima
    std::size_t max_size() const;
    //! verifica se esta vazia
    bool empty() const;
    //! verifica se esta cheia
    bool full() const;

private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

// Implementações

template <typename T>
structures::ArrayStack<T>::ArrayStack() : max_size_(DEFAULT_SIZE), top_(-1) {
    contents = new T[max_size_];
}

template <typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) : max_size_(max), top_(-1) {
    contents = new T[max_size_];
}

template <typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete[] contents;
}

template <typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("Pilha cheia");
    }
    contents[++top_] = data;
}

template <typename T>
T structures::ArrayStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Pilha vazia");
    }
    return contents[top_--];
}

template <typename T>
T& structures::ArrayStack<T>::top() {
    if (empty()) {
        throw std::out_of_range("Pilha vazia");
    }
    return contents[top_];
}

template <typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

template <typename T>
std::size_t structures::ArrayStack<T>::size() const {
    return static_cast<std::size_t>(top_ + 1);
}

template <typename T>
std::size_t structures::ArrayStack<T>::max_size() const {
    return max_size_;
}

template <typename T>
bool structures::ArrayStack<T>::empty() const {
    return top_ == -1;
}

template <typename T>
bool structures::ArrayStack<T>::full() const {
    return static_cast<std::size_t>(top_ + 1) == max_size_;
}

} // namespace structures

#endif
