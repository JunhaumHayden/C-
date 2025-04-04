#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

using namespace std;

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    std::size_t size();
    //! metodo retorna tamanho maximo
    std::size_t max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular)
    int end_;  // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

//! construtor padrao
template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    begin_ = -1;
    end_ = -1;
    size_ = 0;
}

//! construtor com parametro
template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    begin_ = -1;
    end_ = -1;
    size_ = 0;
}

//! destrutor padrao
template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

//! metodo enfileirar
template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw std::out_of_range("Queue is full");
    }
    if (empty()) {
        begin_ = 0;
    }
    end_ = (end_ + 1)% max_size_;
    contents[end_] = data;
    size_++;
}

//! metodo desenfileirar
template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    T dataTemp = contents[begin_];
    if (begin_ == end_) {
        clear();
    } else {
        begin_ = (begin_ + 1) % max_size_;
        size_--;
    }
    return dataTemp;
}

//! metodo retorna o ultimo
template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return contents[end_];
}

//! metodo limpa a fila
template<typename T>
void structures::ArrayQueue<T>::clear() {
    begin_ = end_ = -1;
    size_ = 0;
}

//! metodo retorna tamanho atual
template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

//! metodo retorna tamanho maximo
template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

//! metodo verifica se vazio
template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return begin_ == -1;
}

//! metodo verifica se esta cheio
template<typename T>
bool structures::ArrayQueue<T>::full() {
    return begin_ == (end_ + 1) % static_cast<int>(max_size_);
}

// Função auxiliar para imprimir o conteúdo da fila
void printQueue(structures::ArrayQueue<int>& f, const string& label) {
    cout << label << " [ ";
    int size = f.size();
    for (int i = 0; i < size; i++) {
        int value = f.dequeue();
        cout << value << " ";
        f.enqueue(value);  // Recoloca na fila
    }
    cout << "] (Tamanho: " << f.size() << ")\n";
}

// Função para remover o k-ésimo veículo da fila
void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    if (k < 1 || k > static_cast<int>(f->size())) {
        throw std::out_of_range("Posição inválida.");
    }

    int tamanhoAtual = static_cast<int>(f->size());

    for (int i = 1; i <= tamanhoAtual; i++) {
        int dataTemp = f->dequeue();
        if (i != k) {
            f->enqueue(dataTemp);
        }
    }
}

// Função para manter apenas o k-ésimo veículo na fila
void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    if (k < 1 || k > static_cast<int>(f->size())) {
        throw std::out_of_range("Posição inválida.");
    }

    int tamanhoAtual = static_cast<int>(f->size());
    int elementoParaManter;

    for (int i = 0; i < static_cast<int>(f->size()); i++) {
        int dataTemp = f->dequeue();
        if (i == k-1) {
            elementoParaManter = dataTemp;
            f->clear();
            break;
        }
    }

    f->enqueue(elementoParaManter);
}

// Função para testar a remoção do k-ésimo veículo
void testRetiraVeiculo(int carros_e[], int N, int k, string label) {
    structures::ArrayQueue<int> f;
    for (int i = 0; i < N; i++) {
        f.enqueue(carros_e[i]);
    }

    printQueue(f, label + " antes");
    retira_veiculo(&f, k);
    printQueue(f, label + " depois");
}

// Função para testar a manutenção apenas do k-ésimo veículo
void testMantenhaVeiculo(int carros_e[], int N, int k, string label) {
    structures::ArrayQueue<int> f;
    for (int i = 0; i < N; i++) {
        f.enqueue(carros_e[i]);
    }

    printQueue(f, label + " antes");
    mantenha_veiculo(&f, k);
    printQueue(f, label + " depois");
}

int main() {
    int N = 5;
    int carros_e[5] = {11, 44, 55, 22, 33};

    // Testes para retira_veiculo
    cout << "\n===== Testando retira_veiculo =====\n";
    testRetiraVeiculo(carros_e, N, 3, "Fila 1");
    testRetiraVeiculo(carros_e, N, 1, "Fila 2");
    testRetiraVeiculo(carros_e, N, 5, "Fila 3");

    // Testes para mantenha_veiculo
    cout << "\n===== Testando mantenha_veiculo =====\n";
    testMantenhaVeiculo(carros_e, N, 3, "Fila 1");
    testMantenhaVeiculo(carros_e, N, 1, "Fila 2");
    testMantenhaVeiculo(carros_e, N, 5, "Fila 3");

    return 0;
}
