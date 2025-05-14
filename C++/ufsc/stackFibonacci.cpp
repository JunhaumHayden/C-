#include <iostream>
#include "./02_vplPilha01/array_stack.h"

#include <chrono>
using namespace std;

int fibo_iterativa(int n) {  // mais eficiente
    int a = 1, b = 1;
    if (n==1 || n==2) {
        return 1;
    }
    int f = a + b;
    for (int i = 3; i < n; i++) {
        a = b;
        b = f;
        f = a + b;
    }
    return f;
}

int fibo(int n) {  // recursivo
    if (n==1 || n==2) {
        return 1;
    }
    return fibo(n-2) + fibo(n-1);
}

int fibo_pilha(int n) {  // recursivo transformado em nao recursivo
    structures::ArrayStack<int> p(10000);
    int f = 0;
    p.push(n);
    while (!p.empty()) {
        n = p.pop();
        if (n==1 || n==2) {
            f = f + 1;
        } else {
            p.push(n-2);
            p.push(n-1);
        }
    }
    return f;
}

int main() {
    int x, y, z;
    int n = 10;

    auto start_fibo_iterativa = chrono::high_resolution_clock::now();
    x = fibo_iterativa(n);
    auto end_fibo_iterativa = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo01 = end_fibo_iterativa - start_fibo_iterativa;
    cout << "fibo interativo(" << n << ") = " << x << endl;
    cout << "Tempo fibo interativo: " << tempo01.count() << " segundos" << endl;
    cout << "----------------------------------------" << endl;

    auto start_fibo_pilha = chrono::high_resolution_clock::now();
    y = fibo(n);
    auto end_fibo_pilha = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo02 = end_fibo_pilha - start_fibo_pilha;
    cout << "fibo(" << n << ") = " << y << endl;
    cout << "Tempo fibo recursivo: " << tempo02.count() << " segundos" << endl;
    cout << "----------------------------------------" << endl;

    auto start_fibonacci = chrono::high_resolution_clock::now();
    z = fibo_pilha(n);
    auto end_fibonacci = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo03 = end_fibonacci - start_fibonacci;
    cout << "fibo pilha(" << n << ") = " << z << endl;
    cout << "Tempo fibo pilha: " << tempo03.count() << " segundos" << endl;
    cout << "----------------------------------------" << endl;




    int vetor[4] = {0, 1, 2, 3};
    int index = -1;

    cout << vetor[0] << endl;
    cout << vetor[index++] << endl;
    cout << vetor[index] << endl;
    cout << vetor[++index] << endl;

    cout << vetor[index] << endl;
    return 0;
}