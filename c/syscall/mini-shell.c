// Um interpretador de comando simplificado
// demonstrando o uso de fork, wiatpid e execve

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1
#define MAX_INPUT 1024
#define MAX_ARGS 64

// Função para exibir o prompt
void type_prompt() {
    printf("mini-shell> ");
    fflush(stdout);
}

// Função para ler o comando e seus argumentos
void read_command(char *command, char* *parameters) {
    char input[MAX_INPUT];
    
    // Lê a linha de entrada
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        perror("fgets");
        exit(1);
    }

    // Remove o caractere de nova linha
    input[strcspn(input, "\n")] = '\0';

    // Divide a string em comando e argumentos
    char *token = strtok(input, " ");
    int i = 0;
    
    while (token != NULL) {
        parameters[i++] = token;
        token = strtok(NULL, " ");
    }

    parameters[i] = NULL; // Último elemento deve ser NULL para execve()
    
    // Copia o comando principal
    strcpy(command, parameters[0]);
}

int main() {
    char command[MAX_INPUT];
    char *parameters[MAX_ARGS];
    int status;
    
    // Loop infinito para o shell
    // O loop continua até que o usuário digite "exit"
    while(TRUE) {          // Loop infinito
        type_prompt();     // Chama a função type_prompt() para exibir o prompt
        read_command(command, parameters); // Chama a função read_command() para ler o comando e os parâmetros
        if (strcmp(command, "exit") == 0) { // Se o comando for "exit"
            printf("Saindo do mini-shell...\n");
            break; // Sai do loop
        }

        // Cria um novo processo
        pid_t pid = fork(); // pid_t é um tipo de dado definido no cabeçalho <sys/types.h>, usado para armazenar identificadores de processos (PIDs).
        
        if (pid != 0) {
            /*Processo-pai espera pelo filho*/
            waitpid(pid, &status, 0); // -1 espera qualquer filho, 0 espera qualquer filho
        } else if (pid == 0) {       // Se o fork() retornar 0, significa que estamos no processo filho
            /*Processo-filho tenta executar o comando*/
            execvp(command, parameters); // execve() substitui o processo atual pelo novo processo, 0 nao é passado nenhum ambiente.
            perror("execvp");
            exit(1);
        } else {
                /*Erro ao criar o processo*/
                perror("Deu ruim no fork");
                exit(1);
            }

    }
    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}