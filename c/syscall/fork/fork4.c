#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    // Cria o primeiro processo filho
    pid1 = fork();

    if (pid1 < 0) {
        perror("Erro ao criar o primeiro processo filho");
        exit(1);
    }

    if (pid1 == 0) {
        // Código executado apenas pelo primeiro filho
        printf("Processo filho %d criado\n", getpid());
        exit(0);
    } else {
        // Código do pai após criar o primeiro filho
        printf("Processo pai criou %d\n", pid1);

        // Cria o segundo processo filho
        pid2 = fork();

        if (pid2 < 0) {
            perror("Erro ao criar o segundo processo filho");
            exit(1);
        }

        if (pid2 == 0) {
            // Código executado apenas pelo segundo filho
            printf("Processo filho %d criado\n", getpid());
            exit(0);
        } else {
            // Código do pai após criar o segundo filho
            printf("Processo pai criou %d\n", pid2);

            // Espera os dois filhos terminarem
            wait(NULL);
            wait(NULL);

            // Após os filhos terminarem
            printf("Processo pai finalizado!\n");
        }
    }

    return 0;
}
