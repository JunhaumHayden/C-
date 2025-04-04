#ifndef CARRO_H
#define CARRO_H

#include <iostream>
#include <sstream> // Para formatar a saída como string
using namespace std;

class Carro {
private:
    string marca;
    int ano;
    double valor;

public:
    // Construtor
    Carro(string m, int a, double v) {
        marca = m;
        ano = a;
        setValor(v);
    }

    // GETTERS
    string getMarca() {
        return marca;
    }

    int getAno() {
        return ano;
    }

    double getValor() {
        return valor;
    }

    // SETTERS
    void setMarca(string m) {
        marca = m;
    }

    void setAno(int a) {
        ano = a;
    }

    void setValor(double v) {
        valor = v * 1.1; // Aumenta o valor passado em 10%
    }

    // Agora retorna uma string com as informações do carro
    string exibirInfo() {
        stringstream ss;
        ss << "Marca: " << marca << ", Ano: " << ano << ", Valor: R$ " << valor;
        return ss.str(); // Retorna a string formatada
    }
};

#endif // CARRO_H
