#include  <iostream>
#include "alocacoes.h"
int main(){
    std::string nomes1[] = {"Fulano", "Beltrano", "Ciclano"};
    int matriculas1[] = {1010, 2020, 3030};
    int N1 = 3;

    Aluno *t1 = turma(nomes1, matriculas1, N1);
    std::cout << "Turma 1" << std::endl;
    for (int i = 0; i < N1; i++) {
        std::cout << t1[i].devolveNome() << " " << t1[i].devolveMatricula() << std::endl;
    }
    std::cout << "+++++++++++++++++++++++" << std::endl;

    std::string nomes2[] = {"Fulana", "Beltrana", "Cicrana"};
    int matriculas2[] = {7070, 8080, 9090};
    int N2 = 3;

    Aluno *t2 = turma(nomes2, matriculas2, N2);
    std::cout << "Turma 2" << std::endl;
    for (int i = 0; i < N2; i++) {
        std::cout << t2[i].devolveNome() << " " << t2[i].devolveMatricula() << std::endl;
    }
    std::cout << "+++++++++++++++++++++++" << std::endl;

    Aluno *tu = turmas_uniao(t1, t2, N1, N2);
    std::cout << "Turma Uniao" << std::endl;
    for (int i = 0; i < N1 + N2; i++) {
        std::cout << tu[i].devolveNome() << " " << tu[i].devolveMatricula() << std::endl;
    }
    std::cout << "+++++++++++++++++++++++" << std::endl;
    delete[] t1;
    delete[] t2;
    delete[] tu;
    return 0;

}