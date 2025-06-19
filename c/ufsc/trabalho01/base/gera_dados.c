#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <quantidade_de_numeros>\n", argv[0]);
        return 1;
    }

    int quantidade = atoi(argv[1]);
    if (quantidade <= 0) {
        fprintf(stderr, "A quantidade deve ser um número positivo.\n");
        return 1;
    }

    // Gera nome do arquivo: dataset<quantidade>.txt
    char nome_arquivo[64];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "dataset%d.txt", quantidade);

    FILE *f = fopen(nome_arquivo, "w");
    if (!f) {
        perror("Erro ao criar arquivo");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < quantidade; i++) {
        int num = rand() % quantidade; // 0 a 100000
        fprintf(f, "%d", num);
        if (i < quantidade - 1)
            fprintf(f, " ");
    }

    fclose(f);
    printf("Arquivo '%s' gerado com %d números.\n", nome_arquivo, quantidade);
    return 0;
}
