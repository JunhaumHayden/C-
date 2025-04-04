#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Cria um novo processo

    if (pid > 0) {
        printf("Sou o pai! Meu PID é %d e meu filho tem PID %d\n", getpid(), pid);
    } else if (pid == 0) {
        printf("Sou o filho! Meu PID é %d e o PID do meu pai é %d\n", getpid(), getppid());
    } else {
        perror("Erro ao criar processo");
        exit(1);
    }

    return 0;
}
