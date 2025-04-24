#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures {
    template<typename T>
    class LinkedStack {
        public:
            LinkedStack();

            ~LinkedStack();

            void clear(); // limpa pilha

            void push(const T& data); // empilha

            T pop(); // desempilha

            T& top() const; // dado no topo

            bool empty() const; // pilha vazia

            std::size_t size() const; // tamanho da pilha


        private:
            class Node {
                public:
                    Node(const T& data);
                    Node(const T& data, Node* next);

                    T& data(); // getter: info
                    const T& data() const; // getter-constante: info

                    Node* next(); // getter: próximo
                    const Node* next() const; // getter-constante: próximo

                    void next(Node* next); // setter: próximo
                private:
                    T data_;
                    Node* next_;
            };
            Node* top_; // nodo-topo
            std::size_t size_; // tamanho da pilha
    };
} // namespace structures
#endif
//-------------------------------------
// Definitions for Linkedstack class methods
//! Construtor
template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0u;
}
//! Destrutor
template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
  clear();
}
//! Limpa
template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
    size_ = 0u;
}
template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* new_node = new Node(data, top_);
    if (new_node == nullptr) {
      throw std::out_of_range("memória insuficiente");
    }
    top_ = new_node;
    size_ ++;
}
//! Desempilha
template<typename T>
T structures::LinkedStack<T>::pop() {
  if (empty()) {
    throw std::out_of_range("pilha vazia");
  }
    Node* to_remove = top_;
    T aux = to_remove->data();
    top_ = top_->next();
    delete to_remove;
    size_--;
    return aux;
}
template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    }
    return top_->data();
}
template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return size_ == 0u;
}
template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
// Definitions for Node class methods
template<typename T>
structures::LinkedStack<T>::Node::Node(const T& data) : data_{data}, next_{nullptr} {}

template<typename T>
structures::LinkedStack<T>::Node::Node(const T& data, Node* next) : data_{data}, next_{next} {}

template<typename T>
T& structures::LinkedStack<T>::Node::data() {
    return data_;
}

template<typename T>
const T& structures::LinkedStack<T>::Node::data() const {
    return data_;
}

template<typename T>
typename structures::LinkedStack<T>::Node* structures::LinkedStack<T>::Node::next() {
    return next_;
}

template<typename T>
const typename structures::LinkedStack<T>::Node* structures::LinkedStack<T>::Node::next() const {
    return next_;
}

template<typename T>
void structures::LinkedStack<T>::Node::next(Node* next) {
    next_ = next;
}

