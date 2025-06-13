// Substituido por 'NoRB.h' para ter colocaracao do codigo no Moodle

#ifndef _NO_RB_HPP_
#define _NO_RB_HPP_

#include <iostream>
#include <vector>

#define RB_RUBRO true
#define RB_NEGRO false

template <typename T>
class NoRB {
 private:
    T* dado;
    NoRB<T>* esquerda;
    NoRB<T>* direita;
    NoRB<T>* pai;
    bool cor;

    NoRB<T>* rotacionaEsquerda(NoRB<T>* nodo);
    NoRB<T>* rotacionaDireita(NoRB<T>* nodo);
    NoRB<T>* corrigeInsercao(NoRB<T>* raiz, NoRB<T>* novo);


 public:
    explicit NoRB(const T& dado);
    virtual ~NoRB();

    T* getDado();
    NoRB<T>* getPai();
    bool getCor(NoRB<T>* nodo);
    std::vector<NoRB<T>*> getElementos();
    NoRB<T>* getEsquerda();
    NoRB<T>* getDireita();

    NoRB<T>* inserir(const T& dado, NoRB<T>* arv);
    T* busca(const T& dado, NoRB<T>* arv);
    NoRB<T>* remover(NoRB<T>* raiz, const T& valor);

    void preOrdem(NoRB<T>* nodo);
    void emOrdem(NoRB<T>* nodo);
    void posOrdem(NoRB<T>* nodo);

    NoRB<T>* transplanta(NoRB<T>* raiz, NoRB<T>* u, NoRB<T>* v);
    NoRB<T>* minimo(NoRB<T>* nodo);
    NoRB<T>* corrigeRemocao(NoRB<T>* raiz, NoRB<T>* x, NoRB<T>* paiDeX);

};

// ---------- IMPLEMENTAÇÃO ----------

template <typename T>
NoRB<T>::NoRB(const T& valor) {
    dado = new T(valor);
    esquerda = direita = pai = nullptr;
    cor = RB_RUBRO;  // Novos nós são sempre vermelhos
}

template <typename T>
NoRB<T>::~NoRB() {
    delete dado;
}

template <typename T>
bool NoRB<T>::getCor(NoRB<T>* nodo) {
    return nodo ? nodo->cor : RB_NEGRO;
}

template <typename T>
T* NoRB<T>::getDado() {
    return dado;
}

template <typename T>
NoRB<T>* NoRB<T>::getPai() {
    return pai;
}

template <typename T>
NoRB<T>* NoRB<T>::getEsquerda() {
    return esquerda;
}

template <typename T>
NoRB<T>* NoRB<T>::getDireita() {
    return direita;
}

template <typename T>
std::vector<NoRB<T>*> NoRB<T>::getElementos() {
    std::vector<NoRB<T>*> elementos;
    if (esquerda)
        elementos.push_back(esquerda);
    if (direita)
        elementos.push_back(direita);
    return elementos;
}

// ---------- INSERÇÃO ----------

template <typename T>
NoRB<T>* NoRB<T>::inserir(const T& valor, NoRB<T>* raiz) {
    NoRB<T>* novo = new NoRB<T>(valor);
    NoRB<T>* atual = raiz;
    NoRB<T>* anterior = nullptr;

    while (atual) {
        anterior = atual;
        if (valor < *(atual->dado)) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    novo->pai = anterior;

    if (!anterior) {
        novo->cor = RB_NEGRO;
        return novo;
    } else if (valor < *(anterior->dado)) {
        anterior->esquerda = novo;
    } else {
        anterior->direita = novo;
    }

    return corrigeInsercao(raiz, novo);
}

// ---------- CORREÇÃO DE INSERÇÃO ----------

template <typename T>
NoRB<T>* NoRB<T>::corrigeInsercao(NoRB<T>* raiz, NoRB<T>* nodo) {
    while (nodo != raiz && nodo->pai->cor == RB_RUBRO) {
        NoRB<T>* pai = nodo->pai;
        NoRB<T>* avo = pai->pai;

        if (pai == avo->esquerda) {
            NoRB<T>* tio = avo->direita;
            if (getCor(tio) == RB_RUBRO) {
                pai->cor = RB_NEGRO;
                tio->cor = RB_NEGRO;
                avo->cor = RB_RUBRO;
                nodo = avo;
            } else {
                if (nodo == pai->direita) {
                    nodo = pai;
                    raiz = rotacionaEsquerda(nodo);
                }
                pai->cor = RB_NEGRO;
                avo->cor = RB_RUBRO;
                raiz = rotacionaDireita(avo);
            }
        } else {
            NoRB<T>* tio = avo->esquerda;
            if (getCor(tio) == RB_RUBRO) {
                pai->cor = RB_NEGRO;
                tio->cor = RB_NEGRO;
                avo->cor = RB_RUBRO;
                nodo = avo;
            } else {
                if (nodo == pai->esquerda) {
                    nodo = pai;
                    raiz = rotacionaDireita(nodo);
                }
                pai->cor = RB_NEGRO;
                avo->cor = RB_RUBRO;
                raiz = rotacionaEsquerda(avo);
            }
        }
    }

    raiz->cor = RB_NEGRO;
    return raiz;
}

// ---------- ROTAÇÕES ----------

template <typename T>
NoRB<T>* NoRB<T>::rotacionaEsquerda(NoRB<T>* x) {
    NoRB<T>* y = x->direita;
    x->direita = y->esquerda;

    if (y->esquerda)
        y->esquerda->pai = x;

    y->pai = x->pai;

    if (!x->pai) {
        // x é raiz
    } else if (x == x->pai->esquerda) {
        x->pai->esquerda = y;
    } else {
        x->pai->direita = y;
    }

    y->esquerda = x;
    x->pai = y;

    return y;
}

template <typename T>
NoRB<T>* NoRB<T>::rotacionaDireita(NoRB<T>* y) {
    NoRB<T>* x = y->esquerda;
    y->esquerda = x->direita;

    if (x->direita)
        x->direita->pai = y;

    x->pai = y->pai;

    if (!y->pai) {
        // y é raiz
    } else if (y == y->pai->esquerda) {
        y->pai->esquerda = x;
    } else {
        y->pai->direita = x;
    }

    x->direita = y;
    y->pai = x;

    return x;
}

// ---------- TRAVESSIAS ----------

template <typename T>
void NoRB<T>::preOrdem(NoRB<T>* nodo) {
    if (nodo) {
        std::cout << *(nodo->dado) << " ";
        preOrdem(nodo->esquerda);
        preOrdem(nodo->direita);
    }
}

template <typename T>
void NoRB<T>::emOrdem(NoRB<T>* nodo) {
    if (nodo) {
        emOrdem(nodo->esquerda);
        std::cout << *(nodo->dado) << " ";
        emOrdem(nodo->direita);
    }
}

template <typename T>
void NoRB<T>::posOrdem(NoRB<T>* nodo) {
    if (nodo) {
        posOrdem(nodo->esquerda);
        posOrdem(nodo->direita);
        std::cout << *(nodo->dado) << " ";
    }
}

// ---------- BUSCA ----------

template <typename T>
T* NoRB<T>::busca(const T& valor, NoRB<T>* nodo) {
    if (!nodo)
        return nullptr;
    if (valor == *(nodo->dado))
        return nodo->dado;
    else if (valor < *(nodo->dado))
        return busca(valor, nodo->esquerda);
    else
        return busca(valor, nodo->direita);
}

template <typename T>
NoRB<T>* NoRB<T>::transplanta(NoRB<T>* raiz, NoRB<T>* u, NoRB<T>* v) {
    if (!u->pai) {
        raiz = v;
    } else if (u == u->pai->esquerda) {
        u->pai->esquerda = v;
    } else {
        u->pai->direita = v;
    }
    if (v)
        v->pai = u->pai;
    return raiz;
}

template <typename T>
NoRB<T>* NoRB<T>::minimo(NoRB<T>* nodo) {
    while (nodo->esquerda)
        nodo = nodo->esquerda;
    return nodo;
}

template <typename T>
NoRB<T>* NoRB<T>::remover(NoRB<T>* raiz, const T& valor) {
    NoRB<T>* z = raiz;
    while (z && *(z->dado) != valor) {
        if (valor < *(z->dado)) {
            z = z->esquerda;
        } else {
            z = z->direita;
        }
    }

    if (!z) return raiz;  // Valor não encontrado

    NoRB<T>* y = z;
    bool yCorOriginal = y->cor;
    NoRB<T>* x = nullptr;

    if (!z->esquerda) {
        x = z->direita;
        raiz = transplanta(raiz, z, z->direita);
    } else if (!z->direita) {
        x = z->esquerda;
        raiz = transplanta(raiz, z, z->esquerda);
    } else {
        y = minimo(z->direita);
        yCorOriginal = y->cor;
        x = y->direita;

        if (y->pai == z) {
            if (x)
                x->pai = y;
        } else {
            raiz = transplanta(raiz, y, y->direita);
            y->direita = z->direita;
            if (y->direita)
                y->direita->pai = y;
        }

        raiz = transplanta(raiz, z, y);
        y->esquerda = z->esquerda;
        if (y->esquerda)
            y->esquerda->pai = y;
        y->cor = z->cor;
    }

    delete z;

    if (yCorOriginal == RB_NEGRO) {
        raiz = corrigeRemocao(raiz, x, z->pai);  // Passa pai do removido se x for null
    }

    return raiz;
}

template <typename T>
NoRB<T>* NoRB<T>::corrigeRemocao(NoRB<T>* raiz, NoRB<T>* x, NoRB<T>* paiDeX) {
    while ((x != raiz) && (getCor(x) == RB_NEGRO)) {
        NoRB<T>* pai = (x) ? x->pai : paiDeX;
        if (x == pai->esquerda) {
            NoRB<T>* w = pai->direita;
            if (getCor(w) == RB_RUBRO) {
                w->cor = RB_NEGRO;
                pai->cor = RB_RUBRO;
                raiz = rotacionaEsquerda(pai);
                w = pai->direita;
            }

            if (getCor(w->esquerda) == RB_NEGRO && getCor(w->direita) == RB_NEGRO) {
                w->cor = RB_RUBRO;
                x = pai;
            } else {
                if (getCor(w->direita) == RB_NEGRO) {
                    if (w->esquerda)
                        w->esquerda->cor = RB_NEGRO;
                    w->cor = RB_RUBRO;
                    raiz = rotacionaDireita(w);
                    w = pai->direita;
                }

                w->cor = pai->cor;
                pai->cor = RB_NEGRO;
                if (w->direita)
                    w->direita->cor = RB_NEGRO;
                raiz = rotacionaEsquerda(pai);
                x = raiz;
            }
        } else {
            NoRB<T>* w = pai->esquerda;
            if (getCor(w) == RB_RUBRO) {
                w->cor = RB_NEGRO;
                pai->cor = RB_RUBRO;
                raiz = rotacionaDireita(pai);
                w = pai->esquerda;
            }

            if (getCor(w->direita) == RB_NEGRO && getCor(w->esquerda) == RB_NEGRO) {
                w->cor = RB_RUBRO;
                x = pai;
            } else {
                if (getCor(w->esquerda) == RB_NEGRO) {
                    if (w->direita)
                        w->direita->cor = RB_NEGRO;
                    w->cor = RB_RUBRO;
                    raiz = rotacionaEsquerda(w);
                    w = pai->esquerda;
                }

                w->cor = pai->cor;
                pai->cor = RB_NEGRO;
                if (w->esquerda)
                    w->esquerda->cor = RB_NEGRO;
                raiz = rotacionaDireita(pai);
                x = raiz;
            }
        }
    }

    if (x)
        x->cor = RB_NEGRO;

    return raiz;
}


#endif  // _NO_RB_HPP_
