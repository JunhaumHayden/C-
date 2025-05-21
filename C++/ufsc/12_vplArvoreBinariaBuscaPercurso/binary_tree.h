// Copyright [2025] <Autor>

#include <iostream>

#include "array_list.h"

namespace structures {

// AS IMPLEMENTAÇÕES PODEM SER RECURSIVAS OU NÃO
// SE NECESSÁRIO, OPERAÇÕES ALTERNATIVAS OU AUXILIARES PODEM SER ADICIONADAS
// (NESTE CASO, A OPERAÇÃO TESTADA É BASICAMENTE UMA CHAMADA A OUTRO MÉTODO)

template<typename T>
class BinaryTree {
public:
    BinaryTree();

    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

    void clear();

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            left = nullptr;
            right = nullptr;
        }

        //destrutor recursivo
        //Como delete nullptr é seguro em C++, você não precisa testar se left ou right são nullptr.
        ~Node() {
            delete left;
            delete right;
        }

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            // COLOQUE SEU CÓDIGO AQUI... SE IMPLEMENTAÇÃO RECURSIVA
        }

        bool remove(const T& data_) {
            // COLOQUE SEU CÓDIGO AQUI... SE IMPLEMENTAÇÃO RECURSIVA
        }

        bool contains(const T& data_) const {
            if (data_ == this->data) {
                return true;
            } else if (data_ < this->data) {
                if (this->left != nullptr) {
                    return this->left->contains(data_);
                } else {
                    return false;
                }
            } else {  // data_ > data
                if (right != nullptr) {
                    return right->contains(data_);
                } else {
                    return false;
                }
            }
        }

        void pre_order(ArrayList<T>& v) const {
            // VLR
            v.push_back(this->data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            //LVR
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            //LRV
            if (left != nullptr) {
                left->post_order(v);
            }

            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

//-------------------------------------

template<typename T>
structures::BinaryTree<T>::BinaryTree() {
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    clear(); // Agora ele só chama o clear que deleta root
}

template<typename T>
void structures::BinaryTree<T>::clear() {
    delete root;      // Isso já chama o destrutor de todos os nós recursivamente
    root = nullptr;
    size_ = 0;
}


template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    Node* P = root;
    Node* prev = nullptr;
    while (P != nullptr) { // encontrar um no para inserir
        prev = P;
        if (data < P->data) {
            P = P->left;
        } else if (data > P->data) {
            P = P->right;
        } else {
            throw std::out_of_range("Duplicated data");
        }
    }
    if (root == nullptr)  // arvore vazia
    {
        root = new Node(data);
    }
    else if (data < prev->data) {  // inserir a esquerda
        prev->left = new Node(data);
    } else {
        prev->right = new Node(data);
    }

    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr && current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        throw std::out_of_range("Data not found");
    }

    if (current->left == nullptr || current->right == nullptr) {
        Node* newChild = (current->left != nullptr) ? current->left : current->right;

        if (parent == nullptr) {
            root = newChild;
        } else if (parent->left == current) {
            parent->left = newChild;
        } else {
            parent->right = newChild;
        }
    } else {
        Node* maxLeft = current->left;
        Node* parentMaxLeft = current;

        while (maxLeft->right != nullptr) {
            parentMaxLeft = maxLeft;
            maxLeft = maxLeft->right;
        }

        current->data = maxLeft->data;

        if (parentMaxLeft->right == maxLeft) {
            parentMaxLeft->right = maxLeft->left;
        } else {
            parentMaxLeft->left = maxLeft->left;
        }

        current = maxLeft;
    }

    // evita double delete (pois destrutor de Node libera filhos)
    current->left = nullptr;
    current->right = nullptr;
    delete current;
    size_--;
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (root != nullptr) {
        return root->contains(data);
    } else {
        return false;
    }
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> L;
	if (root != nullptr) {
		root->pre_order(L);
	}
	return L;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->in_order(L);
    }
    return L;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->post_order(L);
    }
    return L;
}


