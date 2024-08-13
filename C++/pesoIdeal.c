/*
Tendo como dados de entrada a altura e o sexo de uma pessoa, construa um algoritmo que calcule seu peso ideal, utilizando as seguintes fórmulas:
Para Homens: (72,7* altura) – 58
Para Mulheres: (62,1 * altura) – 44.7
• Na leitura do sexo só poderão ser aceitos M (masculino) ou F (feminino)
• Realizar a seguinte pergunta ao usuário: ‘DESEJA CONTINUAR (S/N) ?’ e repetir caso a resposta for afirmativa.
*/



#include <stdio.h>

int main() {
    char sexo;
    float altura, pesoIdeal;

    do {
        printf("Digite o sexo (M para masculino, F para feminino): ");
        scanf(" %c", &sexo);

        // Verifica se o sexo é válido
        if (sexo != 'M' && sexo != 'F') {
            printf("Sexo inválido. Por favor, digite M ou F.\n");
            continue;  // Pula para a próxima iteração do loop
        }

        printf("Digite a altura (em metros): ");
        scanf("%f", &altura);

        // Calcula o peso ideal
        if (sexo == 'M') {
            pesoIdeal = 72.7 * altura - 58;
            printf("O peso ideal para um homem com %.2f metros de altura é %.2f kg.\n", altura, pesoIdeal);
        } else {
            pesoIdeal = 62.1 * altura - 44.7;
            printf("O peso ideal para uma mulher com %.2f metros de altura é %.2f kg.\n", altura, pesoIdeal);
        }

        printf("DESEJA CONTINUAR (S/N)? ");
        scanf(" %c", &sexo);
    } while (sexo == 'S' || sexo == 's');

    return 0;
}
