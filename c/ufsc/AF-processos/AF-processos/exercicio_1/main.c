#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


//       (pai)      
//         |        
//    +----+----+
//    |         |   
// filho_1   filho_2


// ~~~ printfs  ~~~
// pai (ao criar filho): "Processo pai criou %d\n"
//    pai (ao terminar): "Processo pai finalizado!\n"
//  filhos (ao iniciar): "Processo filho %d criado\n"

// Obs:
// - pai deve esperar pelos filhos antes de terminar!


int main(int argc, char** argv) {

    // ....

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/
     /* Cria um processo filho. */
    pid_t pid = fork();
    for (int i =0; i < 2; i++) {
        if (pid > 0 && i == 1) {
            pid = fork();
        }
            // exception handling
            if (pid == -1) {
                perror("Erro ao criar processo");
                exit(1);
            }
            
            if (pid > 0) {  // Apenas o processo pai executa os prints
            printf("Processo pai criou %d\n", pid);
            fflush(stdout); //força a saída do buffer da stdout (saída padrão) para o terminal imediatamente.
            
            }
            else if (pid == 0) {  // Apenas o processo filho executa os print
            if (i == 1) {
                printf("Processo filho %d criado\n", getpid());
                fflush(stdout);
            }
            } else {
                perror("Erro Inesperado ao criar processo");
                exit(1);
            }
     }
     while(wait(NULL) >= 0) {  

     }
     if (pid > 0) {
        printf("Processo pai finalizado!\n");   
     }
     return 0;
}
