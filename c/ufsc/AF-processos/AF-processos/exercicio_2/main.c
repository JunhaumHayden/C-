#include <stdio.h> // Blioteca padrão de entrada e saída
#include <stdlib.h> // Biblioteca padrão de funções gerais
#include <unistd.h> // Biblioteca de chamadas de sistema POSIX
#include <sys/wait.h> // Biblioteca para manipulação de processos

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar


void criar_netos() {

    pid_t pid_neto;
    for (int i = 0; i < 3; i++) {
        fflush(stdout); // Garante que os prints anteriores não sejam duplicados após o fork
        pid_neto = fork();
        if (pid_neto < 0) {
            perror("Erro ao criar processo neto");
            exit(1);
        } else if (pid_neto == 0) {
            // Código do processo neto
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            fflush(stdout);
            sleep(5); // Aguarda 5 segundos
            printf("Processo %d finalizado\n", getpid());
            fflush(stdout);
            exit(0);
        }
    }

    // Espera os três netos terminarem
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    // Processo filho (que criou os netos) termina
    printf("Processo %d finalizado\n", getpid());
    fflush(stdout);
    exit(0);
}

int main(int argc, char** argv) {

    // ....

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/

    pid_t pid_filho;
    for (int i = 0; i < 2; i++) {
        fflush(stdout);
        pid_filho = fork();
        if (pid_filho < 0) {
            perror("Erro ao criar processo filho");
            exit(1);
        } else if (pid_filho == 0) {
            // Código dos filhos do processo principal
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            fflush(stdout);
            criar_netos(); // Cada filho cria 3 netos
        }
    }

    // Processo principal espera os dois filhos
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    // Finaliza o processo principal
    printf("Processo principal %d finalizado\n", getpid());
    fflush(stdout);

    return 0;
}
