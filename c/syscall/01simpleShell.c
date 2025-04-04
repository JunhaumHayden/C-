// Um interpretador de comando simplificado
// demonstrando o uso de fork, wiatpid e execve

#define TRUE 1

int main() {
    // Definindo variáveis
    char *args[10];
    char *arg;
    int i = 0;
    int status;
    pid_t pid;
    char command[100];
    
    // Loop infinito para o shell
    // O loop continua até que o usuário digite "exit"
while(TRUE) {
    i = 0;
    printf("Digite o comando: ");
    fgets(command, sizeof(command), stdin);
    
    arg = strtok(command, " \n");
    
    while (arg != NULL) {
        args[i++] = arg;
        arg = strtok(NULL, " \n");
    }
    
    args[i] = NULL;
    
    if (strcmp(args[0], "exit") == 0) {
        break;
    }
    
    pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Processo filho terminou com status %d\n", WEXITSTATUS(status));
        }
    }
}
    printf("Comando executado: %s\n", args[0]);
    printf("Saindo do shell...\n");
    return 0;
}