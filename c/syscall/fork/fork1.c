#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    /* Cria um processo filho. */
    pid_t pid = fork();
    printf("Retorno do fork()\nProcesso: %d: pid = %d\n", getpid(), pid);
    // trat excecao
    if (pid == -1) {
        perror("Erro ao criar processo");
        exit(1);
    }
    
    if (pid > 0) {  // Apenas o processo pai executa os prints
        printf("Apenas o proceeso pai imprime\n");
        printf("Processo Pai: Meu PID é %d e meu filho tem PID %d\n", getpid(), pid);
        printf("\tProcesso %d executando!\n", getpid());
        fflush(stdout); //força a saída do buffer da stdout (saída padrão) para o terminal imediatamente.
    }
    else if (pid == 0) {  // Apenas o processo filho executa os prints
        printf("Apenas o proceeso filho imprime\n");
        printf("Processo Filho: Meu PID é %d e meu Pai tem PID %d\n", getpid(), getppid());
        printf("\tProcesso %d executando!\n", getpid());
        fflush(stdout);
    } else {
        perror("Erro ao criar processo");
        exit(1);
    }
    /* Cria um processo filho. */
    //fork();
    printf("\nCada processo imprime essa linha após a chamada fork()\n");
    printf("\tProcesso %d executando!\n\n", getpid());
    fflush(stdout);

    while(wait(NULL) >= 0) {
    printf("######## Aguardando ##########\n");
    printf("\tProcesso %d\n", getpid());
    fflush(stdout);
    }
    return 0;
}