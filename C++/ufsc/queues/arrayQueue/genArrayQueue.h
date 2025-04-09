// fila generica implementada com matriz
#ifndef ARRAY_QUEUE
#define ARRAY_QUEUE

#include <stdexcept> // Para tratamento de exceções
template<class T, int size=100> // Declering the class template

class ArrayQueue {              // Declerinf the class
    public:
        ArrayQueue() {          // Constructor
            first = last = -1;
        }
        ~ArrayQueue() {}; // Destructor
        
    // Methods Declaration
    void enqueue(T); // Add one element to the queue

    T dequeue();     // Remove one element from the queue

    bool isFull() { // Verifica se a fila está cheia
    return first == 0 && last == size-1 || first == ((last+1)%size); // Condicoes de fila cheia
    }
    bool isEmpty() { // Verifica se a fila está vazia
        return first == -1; // Condicao de fila vazia
    }
    void clear() { // Limpa a fila
        first = last = -1;
    }
    void setFirst(int f) { // Define o primeiro elemento
        first = f%size; // Garante que o primeiro elemento esteja dentro do tamanho da fila
    }
    void setLast(int l) { // Define o último elemento
        last = l%size; // Garante que o último elemento esteja dentro do tamanho da fila
    }
    // Declaracao dos atributos
    private:
        int first, last; // Variaveis para controle da fila
        T storage[size]; // Armazena os elementos da fila
};

// Definindo o metodo enqueue
template<class T, int size>
void ArrayQueue<T, size>::enqueue(T element) { // Adiciona um elemento na fila
    if (isFull()) { // Verifica se a fila está cheia
        throw std::out_of_range("Fila cheia");
    }
    if (isEmpty()) { // Se a fila estiver vazia
        setFirst(0); // Define o primeiro elemento   
    } 
    setLast(last + 1);
    storage[last] = element; // Incrementa e Armazena o elemento na fila
}
// Definindo o metodo dequeue
template<class T, int size>
T ArrayQueue<T, size>::dequeue() { // Remove e devolve um elemento da fila
    if (isEmpty()) { // Verifica se a fila está vazia
        throw std::out_of_range("Fila vazia");
    }
    T tempElement = storage[first]; // Armazena o primeiro elemento
    if (first == last) { // Se houver apenas um elemento na fila
        clear(); // Limpa a fila
    } else {
        setFirst(first + 1); // Incrementa o primeiro elemento
    }
    return tempElement; // Retorna o elemento removido
}
#endif