//! Copyright [year] <Copyright Owner>


#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions


namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho
    void validate_index(std::size_t index) const;

 private:
    class Node {
     public:
       explicit Node(const T& data):
                   data_{data},
                   prev_{nullptr},
                   next_{nullptr}
       {}
       Node(const T& data, Node* next):
           data_{data},
           prev_{nullptr},
           next_{next}
       {}
       Node(const T& data, Node* prev, Node* next):
           data_{data},
           prev_{prev},
           next_{next}
       {}

       T& data()
       {
          return data_;
       }

       const T& data() const
       {
          return data_;
       }

       Node* prev()
       {
          return prev_;
       }

       const Node* prev() const
       {
          return prev_;
       }

       void prev(Node* node)
       {
          prev_ = node;
       }

       Node* next()
       {
          return next_;
       }

       const Node* next() const
       {
          return next_;
       }

       void next(Node* node)
       {
          next_ = node;
       }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

}

//constructor
template <typename T>
structures::DoublyCircularList<T>::DoublyCircularList()
{
    head = nullptr;
    size_ = 0u;
}

//destructor
template <typename T>
structures::DoublyCircularList<T>::~DoublyCircularList()
{
    clear();
}

//member functions
template <typename T>
void structures::DoublyCircularList<T>::clear()
{
    while (!empty())
    {
        pop_front();
    }
    size_ = 0u;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data)
{
    Node* new_node = new Node(data);
    if (!new_node) {
        throw std::out_of_range("Memoria insuficiente");
    }
    if (empty())
    {
        new_node->next(new_node);
        new_node->prev(new_node);
    }else
    {
        new_node->next(head); // next of new node
        new_node->prev(head->prev()); // prev of new node
        head->prev()->next(new_node); // next of prev
        head->prev(new_node); // prev of head
    }
    head = new_node;
    size_++;
}

template <typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* new_node = new Node(data, head->prev(), head);
        if (!new_node) {
            throw std::out_of_range("memória insuficiente");
        }
        head->prev()->next(new_node);
        head->prev(new_node);
        size_++;
    }
}


template <typename T>
void structures::DoublyCircularList<T>::insert(const T& data, std::size_t index)
{
    if (index > size() || index < 0 || empty())
    {
        throw std::out_of_range("índice inexistente");
    }
    if (index == 0)
    {
        push_front(data);
    }
    if (index == size())
    {
        push_back(data);
    }
    else
    {
        Node* current = head;
        for (std::size_t i = 0; i < index; i++)
        {
            current = current->next();
        }
        Node* new_node = new Node(data, current->prev(), current);
        if (!new_node)
        {
            throw std::out_of_range("memória insuficiente");
        }
        current->prev()->next(new_node);
        current->prev(new_node);
        size_++;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data)
{
    if (empty() || data < head->data())
    {
        push_front(data);
    }
    else if (data >= head->prev()->data())
    {
        push_back(data);
    }
    else
    {
        Node* current = head;
        while (current != nullptr && current->data() < data)
        {
            current = current->next();
        }
        Node* new_node = new Node(data, current->prev(), current);
        if (!new_node)
        {
            throw std::out_of_range("memória insuficiente");
        }
        current->prev()->next(new_node);
        current->prev(new_node);
        size_++;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index)
{
    validate_index(index);
    if (index == 0)
    {
        return pop_front();
    }
    if (index == size() - 1)
    {
        return pop_back();
    }
    Node* current = head;
    for (std::size_t i = 0; i < index; i++)
    {
        current = current->next();
    }
    T data = current->data();
    current->prev()->next(current->next());
    current->next()->prev(current->prev());
    delete current;
    size_--;
    return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back()
{
    if (empty())
    {
        throw std::out_of_range("Lista vazia");
    }
    if (size() == 1)
    {
        T data = head->data();
        delete head;
        head = nullptr;
        size_--;
        return data;
    }
    T data = head->prev()->data();
    Node* previous = head->prev()->prev();
    delete head->prev();
    head->prev(previous);
    previous->next(head);
    size_--;
    return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front()
{
    if (empty())
    {
        throw std::out_of_range("Lista vazia");
    }
    T data = head->data();

    if (size() == 1)
    {
        delete head;
        head = nullptr;
    } else
    {
        Node* next = head->next();
        next->prev(head->prev());
        next->prev()->next(next);
        delete head;
        head = next;
    }
    size_--;
    return data;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data)
{
    if (empty())
    {
        throw std::out_of_range("Lista vazia");
    }
    Node* current = head;
    for (std::size_t i = 0; i < size(); ++i) {
        if (current->data() == data) {
            if (current == head) {
                pop_front();
            } else if (current == head->prev()) {
                pop_back();
            } else {
                current->prev()->next(current->next());
                current->next()->prev(current->prev());
                delete current;
                size_--;
            }
            return;
        }
        current = current->next();
    }
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const
{
    return size() == 0;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const
{
    if (empty())
    {
        throw std::out_of_range("Lista vazia");
    }
    Node* current = head;
    for (std::size_t i = 0; i < size(); ++i)
    {
        if (current->data() == data)
        {
            return true;
        }
        current = current->next();
    }
    return false;
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index)
{
    validate_index(index);
    Node* current = head;
    for (std::size_t i = 0; i < index; ++i)
    {
        current = current->next();
    }
    return current->data();
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const
{
    validate_index(index);
    Node* current = head;
    for (std::size_t i = 0; i < index; ++i)
    {
        current = current->next();
    }
    return current->data();
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const
{
    if (empty())
    {
        throw std::out_of_range("Lista vazia");
    }
    Node* current = head;
    for (std::size_t i = 0; i < size(); ++i)
    {
        if (current->data() == data)
        {
            return i;
        }
        current = current->next();
    }
    return size();
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const
{
    return size_;
}
template<typename T>
void structures::DoublyCircularList<T>::validate_index(std::size_t index) const {
    if (index >= size() || empty()) {
        throw std::out_of_range("índice inexistente");
    }
}