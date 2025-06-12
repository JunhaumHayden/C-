// Copyright [2024] <Autor>

#include <algorithm>
#include <cstddef>

#include "array_list.h"


namespace structures {

template<typename T>
class AVLTree {
public:
    AVLTree();

    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

    void clear();

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            height_ = 0;
            left = nullptr;
            right = nullptr;
        }

        ~Node() {
            delete left;
            delete right;
        }

        T data;
        int height_;
        Node* left;
        Node* right;

        Node* insert(Node* node, const T& data) {
            if (!node) {
                //size_++;
                return new Node(data);
            }

            if (data < node->data) {
                node->left = insert(node->left, data);
            } else if (node->data < data) {
                node->right = insert(node->right, data);
            } else {
                return node;  // Duplicados não são permitidos
            }

            node->updateHeight();
            return balance(node);
        }

        Node* remove(Node* node, const T& data) {
            if (!node) return nullptr;

            if (data < node->data) {
                node->left = remove(node->left, data);
            } else if (node->data < data) {
                node->right = remove(node->right, data);
            } else {
                if (!node->left || !node->right) {
                    Node* temp = node->left ? node->left : node->right;
                    if (!temp) {
                        temp = node;
                        node = nullptr;
                    } else {
                        *node = *temp;
                    }
                    delete temp;
                    //size_--;
                } else {
                    Node* temp = minValueNode(node->right);
                    node->data = temp->data;
                    node->right = remove(node->right, temp->data);
                }
            }

            if (!node) return nullptr;

            node->updateHeight();
            return balance(node);
        }

        bool contains(Node* node, const T& data) const {
            if (!node) return false;
            if (data < node->data) return contains(node->left, data);
            if (node->data < data) return contains(node->right, data);
            return true;
        }
        
        void updateHeight()  {
            int left_height = left ? left->height_ : -1;
            int right_height = right ? right->height_ : -1;
            height_ = 1 + std::max(left_height, right_height);
        }

        Node* balance(Node* node) {
            int balance = node->balanceFactor();

            // Caso esquerda-esquerda
            if (balance > 1 && node->left->balanceFactor() >= 0)
                return node->simpleRight();

            // Caso esquerda-direita
            if (balance > 1 && node->left->balanceFactor() < 0)
                return node->doubleRight();

            // Caso direita-direita
            if (balance < -1 && node->right->balanceFactor() <= 0)
                return node->simpleLeft();

            // Caso direita-esquerda
            if (balance < -1 && node->right->balanceFactor() > 0)
                return node->doubleLeft();

            return node;
        }

        int balanceFactor() const {
            int left_height = left ? left->height_ : -1;
            int right_height = right ? right->height_ : -1;
            return left_height - right_height;
        }

        Node* simpleLeft() {
            Node* new_root = right;
            right = new_root->left;
            new_root->left = this;
            this->updateHeight();
            new_root->updateHeight();
            return new_root;
        }

        Node* simpleRight() {
            Node* new_root = left;
            left = new_root->right;
            new_root->right = this;
            this->updateHeight();
            new_root->updateHeight();
            return new_root;
        }

        Node* doubleLeft() {
            right = right->simpleRight();
            return this->simpleLeft();
        }
        
        Node* doubleRight() {
            left = left->simpleLeft();
            return this->simpleRight();
        }

        void pre_order(ArrayList<T>& v) const {
            //VLR
            v.push_back(data);
            if (left != nullptr)
            {
                left->pre_order(v);
            }
            if (right != nullptr)
            {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            //LVR
            if (left != nullptr)
            {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr)
            {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            //LRV
            if (left != nullptr)
            {
                left->post_order(v);
            }
            if (right != nullptr)
            {
                right->post_order(v);
            }
            v.push_back(data);
        }

        int height() {
            return height_;
        }
        Node* minValueNode(Node* node) {
            Node* current = node;
            while (current->left)
                current = current->left;
            return current;
        }

        void clear(Node* node) {
            if (node) {
                clear(node->left);
                clear(node->right);
                delete node;
            }
        }
    };

    Node* root;
    std::size_t size_;
};

}

// -----

template<typename T>
int structures::AVLTree<T>::height() const {
    return root ? root->height_ : -1;
}

template<typename T>
structures::AVLTree<T>::AVLTree() {
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    clear();
}

template<typename T>
void structures::AVLTree<T>::clear() {
    delete root;
    root = nullptr;
    size_ = 0;
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    root = root->insert(root, data);
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    root = root->remove(root, data);
    size_--;
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    return root->contains(root, data);
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> L;
	if (root != nullptr) {
		root->pre_order(L);
	}
	return L;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> L;
    if (root != nullptr) {
        root->in_order(L);
    }
    return L;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> L;
    if (root != nullptr) {
        root->post_order(L);
    }
    return L;
}
