#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class CircularList {
public:
    CircularList();
    ~CircularList();

    void clear(); // limpar lista

    void push_back(const T& data); // inserir no fim
    void push_front(const T& data); // inserir no início
    void insert(const T& data, std::size_t index); // inserir na posição
    void insert_sorted(const T& data); // inserir em ordem

    T& at(std::size_t index); // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const; // versão const do acesso ao indice

    T pop(std::size_t index); // retirar da posição
    T pop_back(); // retirar do fim
    T pop_front(); // retirar do início
    void remove(const T& data); // remover dado específico

    bool empty() const; // lista vazia
    bool contains(const T& data) const; // lista contém determinado dado?
    std::size_t find(const T& data) const; // posição de um item na lista

    std::size_t size() const; // tamanho da lista
    
    private:
    struct Node {
        explicit Node(const T& data) : data(data), next(nullptr) {}
        
        T data;
        Node* next;
    };
    Node* head;
    std::size_t size_;
};

} // namespace structures

#endif

//constructor
template <typename T>
structures::CircularList<T>::CircularList()
{
    head = nullptr;
    size_ = 0u;
}

template <typename T>
structures::CircularList<T>::~CircularList() {
    clear();
}

template <typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}
template <typename T>
bool structures::CircularList<T>::empty() const {
    return size_ == 0;
}
template <typename T>
void structures::CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}
template <typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    
    Node* to_remove = head;
    T data = to_remove->data;
    
    if (size_ == 1) {
        head = nullptr;
    } else {
        // Encontrar o último nó
        Node* last = head;
        while (last->next != head) {
            last = last->next;
        }
        head = head->next;
        last->next = head;
    }
    
    delete to_remove;
    size_--;
    return data;
}
template <typename T>
T structures::CircularList<T>::pop_back() {
    return pop(size_ - 1);
}
template <typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        return pop_front();
    }
    
    Node* previous = head;
    for (std::size_t i = 0; i < index - 1; ++i) {
        previous = previous->next;
    }
    
    Node* to_remove = previous->next;
    T data = to_remove->data;
    previous->next = to_remove->next;
    delete to_remove;
    size_--;
    return data;
}
template <typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("Index inválido");
    }
    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* new_node = new Node(data);
        Node* previous = head;
        for (std::size_t i = 0; i < index - 1; ++i) {
            previous = previous->next;
        }
        new_node->next = previous->next;
        previous->next = new_node;
        size_++;
    }
}

template <typename T>
void structures::CircularList<T>::push_back(const T& data) {
    Node* new_node = new Node(data);
    if (empty()) {
        head = new_node;
        head->next = head;
    } else {
        Node* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        tail->next = new_node;
        new_node->next = head;
    }
    size_++;
}

template <typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (empty()) {
        head = new_node;
        head->next = head;
    } else {
        Node* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        tail->next = new_node;
        new_node->next = head;
        head = new_node;
    }
    size_++;
}
template <typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    if (empty() || data < head->data) {
        push_front(data);
    } else if (data >= head->next->data) {
        push_back(data);
    } else {
        Node* new_node = new Node(data);
        Node* current = head;
        while (current->next != head && current->next->data < data) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        size_++;
    }
}
template <typename T>
void structures::CircularList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    Node* current = head;
    Node* previous = nullptr;
    do {
        if (current->data == data) {
            if (previous == nullptr) {
                pop_front();
            } else {
                previous->next = current->next;
                delete current;
                size_--;
            }
            return;
        }
        previous = current;
        current = current->next;
    } while (current != head);
}

template <typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    Node* current = head;
    do {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    } while (current != head);
    return false;
}

template <typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index inválido");
    }
    Node* current = head;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}
template <typename T>
const T& structures::CircularList<T>::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index inválido");
    }
    Node* current = head;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
std::size_t structures::CircularList<T>::find(const T& data) const{
    if (empty()) {
        return size_;
    }
    Node* current = head;
    for (std::size_t i = 0; i < size_; ++i) {
        if (current->data == data) {
            return i;
        }
        current = current->next;
    }
    return size_;
}