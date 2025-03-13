#ifndef INICIAIS_H
#define INICIAIS_H

struct maxpos {
    int max;
    int pos;
};

int maximo(int vet[], int N);
int posicao(int vet[], int N);
maxpos maximo_posicao(int vet[], int N);
void maximo_vetores(int vet1[], int vet2[], int N);
void inversao(int vet[], int N);

#endif
