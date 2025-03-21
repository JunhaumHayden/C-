// Copyright [2022] <Carlos Benedito Hayden de Albuquerque Junior>
#include <string>


class Aluno {
 public:
    Aluno() {}  // construtor
    ~Aluno() {}  // destrutor
    std::string devolveNome() {
        return nome;
    }
    int devolveMatricula() {
        return matricula;
    }
    void escreveNome(std::string nome_) {
        nome = nome_;
    }
    void escreveMatricula(int matricula_) {
        matricula = matricula_;
    }
 private:
    std::string nome;
    int matricula;
};

// cria um novo vetor somente com matrículas maiores ou iguais a menor_matr, a partir de um vetor de N objetos do tipo Aluno:
Aluno *turma_filtra(Aluno t[], int N, int menor_matr) {
    int count = 0;

    // Count the number of students with matricula >= menor_matr
    for (int i = 0; i < N; i++) {
        if (t[i].devolveMatricula() >= menor_matr) {
            count++;
        }
    }

    // Allocate memory for the filtered array
    Aluno *tf = new Aluno[count];
    int aux = 0;

    // Populate the filtered array
    for (int i = 0; i < N; i++) {
        if (t[i].devolveMatricula() >= menor_matr) {
            tf[aux++] = t[i];
        }
    }

    return tf;
}


// crie um vetor de inteiros com 26 posições, na qual cada posição corresponda a contagem de alunos com a respectiva primeira letra do nome em maiúsculo ('A' na posição 0, 'B' na posição 1, ..., 'Z' na posição 25):
int *turma_conta(Aluno t[], int N) {
    int *c;
    c = new int[26]();  // retirar e alocar (com new)
    for (int i=0; i < N; i++) {
        c[t[i].devolveNome()[0] - 'A']++;
    }
    return c;
}




/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
