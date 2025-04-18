//! Copyright [Year] <Copyright ...>


#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>



namespace structures {


//! ...
template<typename T>
class ArrayList {
 public:
    //! ...
    ArrayList();
    //! ...
    explicit ArrayList(std::size_t max_size);
    //! ...
    ~ArrayList();

    //! ...
    void clear();
    //! ...
    void push_back(const T& data);
    //! ...
    void push_front(const T& data);
    //! ...
    void insert(const T& data, std::size_t index);
    //! ...
    void insert_sorted(const T& data);
    //! ...
    T pop(std::size_t index);
    //! ...
    T pop_back();
    //! ...
    T pop_front();
    //! ...
    void remove(const T& data);
    //! ...
    bool full() const;
    //! ...
    bool empty() const;
    //! ...
    bool contains(const T& data) const;
    //! ...
    std::size_t find(const T& data) const;
    //! ...
    std::size_t size() const;
    //! ...
    std::size_t max_size() const;
    //! ...
    T& at(std::size_t index);
    //! ...
    T& operator[](std::size_t index);
    // descricao do 'operator []' na FAQ da disciplina
    //! ...
    const T& at(std::size_t index) const;
    //! ...
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};



//-------------------------------------



//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! ...
    ArrayListString() : ArrayList() {}
    //! ...
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! ...
    ~ArrayListString();

    //! ...
    void clear();
    //! ...
    void push_back(const char *data);
    //! ...
    void push_front(const char *data);
    //! ...
    void insert(const char *data, std::size_t index);
    //! ...
    void insert_sorted(const char *data);
    //! ...
    char *pop(std::size_t index);
    //! ...
    char *pop_back();
    //! ...
    char *pop_front();
    //! ...
    void remove(const char *data);
    //! ...
    bool contains(const char *data);
    //! ...
    std::size_t find(const char *data);
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    insert(data, size());
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    insert(data, 0);
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else if (index > size()) {  // se index == size(), insere no fim
        throw std::out_of_range("índice inválido para a inserção");
    }
    if (index < size_) {
        for (std::size_t i = size_; i > index; --i) {
            contents[i] = contents[i - 1];
        }
    }
    contents[index] = data;
    size_++;
    // for (std::size_t i = size_; i > index; --i) {
    //     contents[i] = contents[i - 1];
    // }
    // contents[index] = data;
    // size_++;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    std::size_t index = 0;
    while (index < size_ && contents[index] < data) {
        index++;
    }
    insert(data, index);
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index >= size()) {
        throw std::out_of_range("índice inválido para a remoção");
    }
    T aux = contents[index];
    if (index < size_ - 1) {
        for (std::size_t i = index; i < size_ - 1; ++i) {
            contents[i] = contents[i + 1];
        }
    }
    size_ --;
    return aux;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    return pop(size()-1);
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    return pop(0);
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    // remove primeira ocorrência de 'data' (pelo conteúdo e não pelo índice)
    // se não encontrar 'data', mantém a lista como estava
    std::size_t index = find(data);
    if (index < size_) {
        pop(index);
    }
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (size() == 0);
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size() == max_size());
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    std::size_t index = find(data);
    return (index < size());
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    // retorna o índice da primeira ocorrência de 'data' na lista, se houver
    // retorna 'size()', se 'data' não fizer parte da lista
    std::size_t index = 0;
    while (index < size_ && contents[index] != data) {
        index++;
    }
    return index;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index >= size()) {
        throw std::out_of_range("índice inválido");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    // difere do 'at()' por ser uma alternativa sem verificação de 'index'
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    const T aux = at(index);
    return aux;
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    // difere do 'at()' por ser uma alternativa sem verificação de 'index'
    const T aux = contents[index];
    return aux;
}
//-------------------------------------
// destrutor
structures::ArrayListString::~ArrayListString() {
    clear();
}

// limpa a lista e libera a memória das strings
void structures::ArrayListString::clear() {
    for (std::size_t i = 0; i < this->size(); ++i) {
        delete[] this->at(i);  // libera cada string
    }
    ArrayList<char*>::clear();  // limpa a lista base
}

// insere no final
void structures::ArrayListString::push_back(const char* data) {
    char* datanew = new char[std::strlen(data) + 1];
    std::strcpy(datanew, data);
    ArrayList<char*>::push_back(datanew);
}

// insere no início
void structures::ArrayListString::push_front(const char* data) {
    char* datanew = new char[std::strlen(data) + 1];
    std::strcpy(datanew, data);
    ArrayList<char*>::push_front(datanew);
}

// insere na posição index
void structures::ArrayListString::insert(const char* data, std::size_t index) {
    char* datanew = new char[std::strlen(data) + 1];
    std::strcpy(datanew, data);
    ArrayList<char*>::insert(datanew, index);
}

// insere de forma ordenada (alfabética)
void structures::ArrayListString::insert_sorted(const char* data) {
    std::size_t i = 0;
    while (i < this->size() && std::strcmp(this->at(i), data) < 0) {
        ++i;
    }
    insert(data, i);
}

// remove da posição index e retorna o ponteiro da string
char* structures::ArrayListString::pop(std::size_t index) {
    char* removed = this->at(index);
    ArrayList<char*>::pop(index);
    return removed;  // o chamador é responsável por liberar
}

// remove do fim
char* structures::ArrayListString::pop_back() {
    char* removed = this->at(this->size() - 1);
    ArrayList<char*>::pop_back();
    return removed;
}

// remove do início
char* structures::ArrayListString::pop_front() {
    char* removed = this->at(0);
    ArrayList<char*>::pop_front();
    return removed;
}

// remove a primeira ocorrência de uma string
void structures::ArrayListString::remove(const char* data) {
    std::size_t index = find(data);
    if (index != this->size()) {
        delete[] this->at(index);  // libera a memória da string
        ArrayList<char*>::pop(index);
    }
}

// verifica se a string está na lista
bool structures::ArrayListString::contains(const char* data) {
    return find(data) != this->size();
}

// encontra o índice da primeira ocorrência
std::size_t structures::ArrayListString::find(const char* data) {
    for (std::size_t i = 0; i < this->size(); ++i) {
        if (std::strcmp(this->at(i), data) == 0) {
            return i;
        }
    }
    return this->size();  // não encontrado
}