//!  Copyright [2024] <Autor>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "./array_list.h"
#include <queue>



namespace structures {

//! Classe Árvore binária
template<typename T>
class BinaryTree {
 public:
    //! ...
    BinaryTree();
    //! ...
    ~BinaryTree();
    //! ...
    void insert(const T& data);
    //! ...
    void remove(const T& data);
    //! ...
    bool contains(const T& data) const;
    //! ...
    bool empty() const;
    //! ...
    std::size_t size() const;
    //! ...
    ArrayList<T> pre_order() const;
    //! ...
    ArrayList<T> in_order() const;
    //! ...
    ArrayList<T> post_order() const;

    //******************************************************************
    // Prova prática - implementações necessárias:

    // (1) determinação da altura da árvore:
    int height();

    // (2) contagem do número de folhas:
    int leaves();

    // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
    //     valor da árvore:
    ArrayList<T> limits();

    // (4) criação de uma duplicação, em memória, da árvore:
    BinaryTree<T> clone();

    // (5) remove nós pelo número de seus filhos:
    void filter(int n_child);

    // (6) criação de um nova árvore que tenha todos os valores e a
    //     menor altura possível, ou seja, balanceada com base apenas
    //     no estabelecimento de uma nova ordem de inserção:
    BinaryTree<T> balance();

    //******************************************************************


 private:
    struct Node {
        //! Construtor
        explicit Node(const T& data) :
        data_{data}
        {}

        //! Destrutor
        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;
        Node* left_{nullptr};
        Node* right_{nullptr};

        //! Inserção
        void insert(const T& data) {
            // checar dado duplicado
            if (data == data_)
            {
                return;
            }
            // caso recursivo - procura na subárvore esquerda
            if (data < data_)
            {
                if (left_ == nullptr)
                {
                    left_ = new Node(data);
                }
                else
                {
                    left_->insert(data);
                }
            }
            else if (data > data_)
            {
                if (right_ == nullptr)
                {
                    right_ = new Node(data);
                }
                else
                {
                    right_->insert(data);
                }
            }
        }

        //! Remoção
        bool remove(const T& data) {
            bool existe = false;
            // caso base - este é o nó procurado
            if (data == data_)
            {
                existe = true;
                // remocao depende da quantidade de filhos
                // nó folha - é deletado diretamente
                if (left_ == nullptr && right_ == nullptr)
                {
                    delete this;
                    return existe;
                }
                // nó com um filho
                //O nó é substituído pelo seu único filho (esquerdo ou direito).
                //O filho é desconectado e o nó atual é deletado
                if (left_ == nullptr || right_ == nullptr)
                {
                    Node* temp = (left_ != nullptr) ? left_ : right_;
                    data_ = temp->data_;
                    left_ = temp->left_;
                    right_ = temp->right_;
                    temp->left_ = temp->right_ = nullptr;
                    delete temp;
                    return existe;
                }
                // nó com dois filhos
                //O menor valor da subárvore direita (sucessor in-order) é encontrado.
                Node* min = right_->minimum();
                //O valor do nó atual é substituído pelo valor do nó mínimo.
                data_ = min->data_;
                //O sucessor é removido recursivamente da subárvore direita.
                right_->remove(min->data_);
            }
            else
            {
                // caso recursivo - procura na subárvore esquerda
                if (data < data_)
                {
                    if (left_ != nullptr)
                        return left_->remove(data);
                }
                // caso recursivo - procura na subárvore direita
                else
                {
                    if (right_ != nullptr)
                        return right_->remove(data);
                }
            }
            return existe;
        }

        //! Contém
        bool contains(const T& data) const {
            bool existe = false;
            if (data == data_) {
                return true;
            }
            if (data < data_) {
                if (left_ != nullptr) {
                    return left_->contains(data);
                }
                return existe;
            }
            // data_ > data
            if (right_ != nullptr) {
                return right_->contains(data);
            }
            return existe;
        }

        //! Pré ordem
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        //! Em ordem
        void in_order(ArrayList<T>& v) const {
            //LVR
            if (left_ != nullptr){
                left_->in_order(v);
            }
            v.push_back(data_);
            if (right_ != nullptr){
                right_->in_order(v);
            }
        }

        //! Pós ordem
        void post_order(ArrayList<T>& v) const {
            //LRV
            if (left_ != nullptr)
            {
                left_->post_order(v);
            }
            if (right_ != nullptr)
            {
                right_->post_order(v);
            }
        }

     private:
        //! Complemento da funcão de remoção
        Node* remove(const T& data, Node* arv, bool& deleted) {
            Node* temp = nullptr;
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            return temp;
        }

        //! Encontrar o menor
        Node* minimum() {
            if (left_ == nullptr)
                return this;
            return left_->minimum();
        }
    };

    Node* root_{nullptr};
    std::size_t size_{0};
};




//******************************************************************
// Prova prática - implementações necessárias:

//! (1) determinação da altura da árvore:
template<typename T>
int BinaryTree<T>::height() {
    if (empty()) return -1;

    std::queue<Node*> nodes;
    nodes.push(root_);
    int height = -1;

    while (!nodes.empty()) {
        int level_size = nodes.size();
        height++;

        for (int i = 0; i < level_size; ++i) {
            Node* current = nodes.front();
            nodes.pop();

            if (current->left_ != nullptr)
                nodes.push(current->left_);
            if (current->right_ != nullptr)
                nodes.push(current->right_);
        }
    }

    return height;
}

//! (2) contagem do número de folhas:
template<typename T>
int BinaryTree<T>::leaves() {
    if (empty()) return 0;

    std::queue<Node*> nodes;
    nodes.push(root_);
    int leaf_count = 0;

    while (!nodes.empty()) {
        Node* current = nodes.front();
        nodes.pop();

        // Verifica se é um nó folha
        if (current->left_ == nullptr && current->right_ == nullptr) {
            leaf_count++;
        } else {
            // Adiciona os filhos não nulos à fila
            if (current->left_ != nullptr)
                nodes.push(current->left_);
            if (current->right_ != nullptr)
                nodes.push(current->right_);
        }
    }

    return leaf_count;
}

//! (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//!     valor da árvore:
template<typename T>
ArrayList<T> BinaryTree<T>::limits() {
    ArrayList<T> L(2);
    if (empty()) return L;

    // Encontrar o mínimo
    Node* current = root_;
    while (current->left_ != nullptr) {
        current = current->left_;
    }
    L.push_back(current->data_);

    // Encontrar o máximo
    current = root_;
    while (current->right_ != nullptr) {
        current = current->right_;
    }
    L.push_back(current->data_);
    return L;
}

//! (4) criação de uma duplicação, em memória, da árvore:
template<typename T>
BinaryTree<T> BinaryTree<T>::clone() {
    BinaryTree<T> C;
    if (empty()) return C;

    ArrayList<T> elements = pre_order();
    for (std::size_t i = 0; i < elements.size(); ++i) {
        C.insert(elements[i]);
    }

    return C;
}

//! (5) remove nós pelo número de seus filhos:
template<typename T>
void BinaryTree<T>::filter(int n_child) {
    if (empty()) return;
    if (empty()) return;

    // Lista de nós a serem removidos (evita modificar a árvore durante a busca)
    ArrayList<T> to_remove;

    // Função para percorrer a árvore e identificar os nós a remover
    std::function<void(Node*)> find_nodes = [&](Node* node) {
        if (node == nullptr) return;

        int children = 0;
        if (node->left_ != nullptr) children++;
        if (node->right_ != nullptr) children++;

        if (children == n_child) {
            to_remove.push_back(node->data_);
        }

        find_nodes(node->left_);
        find_nodes(node->right_);
    };

    find_nodes(root_);

    // Remove os nós identificados
    for (std::size_t i = 0; i < to_remove.size(); ++i) {
        remove(to_remove[i]);
    }
}

//! (6) criação de um nova árvore que tenha todos os valores e a
//!     menor altura possível, ou seja, balanceada com base apenas
//!     no estabelecimento de uma nova ordem de inserção:
template<typename T>
BinaryTree<T> BinaryTree<T>::balance() {
    BinaryTree<T> B;
    if (empty()) return B;

    ArrayList<T> elements = in_order();
    balance_insert(B, elements, 0, elements.size() - 1);

    return B;
}

template<typename T>
void balance_insert(BinaryTree<T>& tree, ArrayList<T>& elements, int start, int end) {
    if (start > end) return;

    int mid = (start + end) / 2;
    tree.insert(elements[mid]);

    balance_insert(tree, elements, start, mid - 1);
    balance_insert(tree, elements, mid + 1, end);
}

//******************************************************************



//! Construtor
template<typename T>
BinaryTree<T>::BinaryTree()
{}

//! Destrutor
template<typename T>
BinaryTree<T>::~BinaryTree() {
    delete root_;
}

//! Inserção
template<typename T>
void BinaryTree<T>::insert(const T& data) {
    Node* P = root_;
    Node* prev = nullptr;
    while (P != nullptr) { // encontrar um no para inserir
        prev = P;
        if (data < P->data_) {
            P = P->left_;
        } else if (data > P->data_) {
            P = P->right_;
        } else {
            throw std::out_of_range("Duplicated data");
        }
    }
    if (root_ == nullptr)  // arvore vazia
    {
        root_ = new Node(data);
    }
    else if (data < prev->data_) {  // inserir a esquerda
        prev->left_ = new Node(data);
    } else {
        prev->right_ = new Node(data);
    }
    size_++;
}

// Remoção
template<typename T>
void BinaryTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree");

    Node* parent = nullptr;
    Node* current = root_;
    while (current != nullptr && current->data_ != data) {
        parent = current;
        if (data < current->data_) {
            current = current->left_;
        } else {
            current = current->right_;
        }
    }
    if (current == nullptr) {
        throw std::out_of_range("Data not found");
    }
    if (current->left_ == nullptr || current->right_ == nullptr) {
        Node* newChild = (current->left_ != nullptr) ? current->left_ : current->right_;
        if (parent == nullptr) {
            root_ = newChild;
        } else if (parent->left_ == current) {
            parent->left_ = newChild;
        } else {
            parent->right_ = newChild;
        }
    } else {
        Node* maxLeft = current->left_;
        Node* parentMaxLeft = current;
        while (maxLeft->right_ != nullptr) {
            parentMaxLeft = maxLeft;
            maxLeft = maxLeft->right_;
        }
        current->data_ = maxLeft->data_;
        if (parentMaxLeft->right_ == maxLeft) {
            parentMaxLeft->right_ = maxLeft->left_;
        } else {
            parentMaxLeft->left_ = maxLeft->left_;
        }
        current = maxLeft;
    }
    current->left_ = nullptr;
    current->right_ = nullptr;
    delete current;

    size_--;
}

//! Contém
template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Vazio
template<typename T>
bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Tamanho
template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Pré ordem
template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->pre_order(v);
    return v;
}

//! Em ordem
template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

//! Pós ordem
template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

}  // namespace structures

#endif
