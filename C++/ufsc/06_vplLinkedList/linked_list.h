//! Copyright [year] <Copyright Owner>
// linked_list.h

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {
    template<typename T>
    class LinkedList {
         public:
            //! ...
            LinkedList();  // construtor padrão
            //! ...
            ~LinkedList();  // destrutor
            //! ...
            void clear();  // limpar lista
            //! ...
            void push_back(const T& data);  // inserir no fim
            //! ...
            void push_front(const T& data);  // inserir no início
            //! ...
            void insert(const T& data, std::size_t index);  // inserir na posição
            //! ...
            void insert_sorted(const T& data);  // inserir em ordem
            //! ...
            T& at(std::size_t index);  // acessar um elemento na posição index
            //! ...
            T pop(std::size_t index);  // retirar da posição
            //! ...
            T pop_back();  // retirar do fim
            //! ...
            T pop_front();  // retirar do início
            //! ...
            void remove(const T& data);  // remover específico
            //! ...
            bool empty() const;  // lista vazia
            //! ...
            bool contains(const T& data) const;  // contém
            //! ...
            std::size_t find(const T& data) const;  // posição do dado
            //! ...
            std::size_t size() const;  // tamanho da lista

            void invert();

            LinkedList clone();

            LinkedList slicing(int start, int stop, int step);

            void append(LinkedList<T>* list_add);

            LinkedList< LinkedList<T>* > halve();
;

        private:
            class Node {  // Elemento (implementação pronta)
             public:
                explicit Node(const T& data):
                    data_{data}
                {}

                Node(const T& data, Node* next):
                    data_{data},
                    next_{next}
                {}

                T& data() {  // getter: dado
                    return data_;
                }

                const T& data() const {  // getter const: dado
                    return data_;
                }

                Node* next() {  // getter: próximo
                    return next_;
                }

                const Node* next() const {  // getter const: próximo
                    return next_;
                }

                void next(Node* node) {  // setter: próximo
                    next_ = node;
                }

             private:
                T data_;
                Node* next_{nullptr};
            };

        Node* before_index(std::size_t index) {  // nó anterior ao 'index'
            auto it = head;
            for (auto i = 1u; i < index; ++i) {
                it = it->next();
            }
            return it;
        }

        Node* head{nullptr};
        Node* tail{nullptr};
        std::size_t size_{0u};
    };
}  // namespace structures

#endif
//-------------------------------------

//! Construtor
template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

//! Destrutor
template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

//! Esvazia
template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

//! Inserção no início
template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node *novo;
    novo = new Node(data, head);
    if (novo == nullptr) {
        throw std::out_of_range("memória insuficiente");
    }
    if (head == nullptr) {
        tail = novo;
    }
    head = novo;
    size_++;
}

//! Inserção no fim
template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    Node *novo;
    if (empty()) {
        return push_front(data);
    }
    novo = new Node(data, nullptr);
    if (novo == nullptr) {
        throw std::out_of_range("memória insuficiente");
    }
    tail->next(novo);
    tail = novo;
    size_++;
}

//! Dado da posição 'index'
template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (index >= size_) {
        throw std::out_of_range("índice inválido");
    }
    Node* current = head;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->next();
    }
    return current->data();
}

//! Inserção na posição 'index'
template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("índice inválido");
    }
    if (index == 0) {
      return push_front(data);
    }
    if (index == size_) {
      return push_back(data);
    }
    Node* previous = before_index(index);
    Node* new_node = new Node(data, previous->next());
    if (new_node == nullptr) {
        throw std::out_of_range("memória insuficiente");
    }
    previous->next(new_node);
    size_++;
}

//! Inserção ordenada
template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty() || data < head->data()) {
      return push_front(data);
    }
    if (data > tail->data()) {
      return push_back(data);
    }
    Node* current = head;
    std::size_t index = 0;

    while (current->next() != nullptr && current->next()->data() < data) {
        current = current->next();
        ++index;
    }
    insert(data, index + 1);
}


//! Remoção do início
template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    T aux;
    Node *p;
    p = head;
    head = p->next();
    aux = p->data();
    delete p;
    if (head == nullptr) {
        tail = nullptr;
    }
    size_--;
    return aux;
}

//! Remoção do fim
template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (size() == 1) {
        return pop_front();
    }
    T aux;
    Node *p, *ant;
    ant = nullptr;
    p = head;
    while (p != tail) {  // 'ant' deve apontar para o penúltimo nó
        ant = p;
        p = p->next();
    }
    aux = p->data();
    delete p;
    if (ant == nullptr) {
        head = nullptr;
    } else {
        ant->next(nullptr);
    }
    tail = ant;
    size_--;
    return aux;
}

//! Remoção da posição 'index'
template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (index >= size_) {
        throw std::out_of_range("índice inválido");
    }
    if (index == 0) {
        return pop_front();
    }
    if (index == size_ - 1) {
        return pop_back();
    }
    Node* previous = before_index(index);
    Node* to_remove = previous->next();
    T aux_data = to_remove->data();
    previous->next(to_remove->next());
    delete to_remove;
    size_--;
    return aux_data;
}

//! Remoção de um dado
template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

//! Verificação de vazia
template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size() == 0u;
}

//! Verificação se contém um dado
template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    return find(data) != size();
}

//! Índice de um dado (se existir); ou 'size() (se não existir)
template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* current = head;
    std::size_t index = 0;
    while (current != nullptr) {
        if (current->data() == data) {
            return index;
        }
        current = current->next();
        index++;
    }
    return size();
}

//! Quantidade atual de elementos
template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

//! Metodo para inverter a lista
template<typename T>
void structures::LinkedList<T>::invert() {
    if (size() < 2 ) return;
    // tres ponteiros para manipulacao
    Node* next = nullptr;
    Node* current = head;
    Node* previous = nullptr;
    //iterar sobre a lista
    while (current != nullptr) {
        // atualizando ponteiros
        next = current->next();
        current->next(previous);
        // atualizando elementos
        previous = current;
        current = next;
    }
    head = previous;
}

template<typename T>
structures::LinkedList<T> structures::LinkedList<T>::clone() {
    LinkedList<T> new_list;
    Node* current = head;
    while (current != nullptr) {
        new_list.push_back(current->data());
        current = current->next();
    }
    return new_list;
}

template<typename T>
structures::LinkedList<T> structures::LinkedList<T>::slicing(int start, int stop, int step) {
    LinkedList<T> result;
    if (start < 0 || stop > size() || step <= 0) { // parametros fora da lista
        return result;
    }
    Node* current = head;
    int index = 0;

    while (current != nullptr && index < stop) { // teste de fim de lista ou index atingir o stop
        if (index >= start && (index - start) % step == 0) { // se index maior start E verificar se o index esta no intervalo correto.
            result.push_back(current->data());
        }
        current = current->next();
        ++index;
    }
    return result;
}

template<typename T>
void structures::LinkedList<T>::append(LinkedList<T>* list_add) {
    if (list_add == nullptr || list_add->empty()) {
        return;
    }

    Node* current = list_add->head;

    while (current != nullptr) {
        this->push_back(current->data());
        current = current->next();
    }
}

template<typename T>
structures::LinkedList<structures::LinkedList<T>*> structures::LinkedList<T>::halve() {
    LinkedList<T>* pares = new LinkedList<T>();
    LinkedList<T>* impares = new LinkedList<T>();

    Node* current = head;
    std::size_t index = 0;

    while (current != nullptr) {
        if (index % 2 == 0) {
            pares->push_back(current->data());
        } else {
            impares->push_back(current->data());
        }
        current = current->next();
        ++index;
    }

    LinkedList<LinkedList<T>*> resultado;
    resultado.push_back(pares);
    resultado.push_back(impares);

    return resultado;
}
