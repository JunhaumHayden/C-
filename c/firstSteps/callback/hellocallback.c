// Refatorando a Struct  para executar callback de funcoes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

struct Person {
    char name[10];
    uint8_t age;
    uint8_t height;
};

void createPerson(char name[], uint8_t age, uint8_t height, void(*function_pointer)(struct Person)){ // é um ponteiro para uma fincao que nao retorna nada,mas temo como argumento um tipo struct Person
    struct Person person;
    strcpy(person.name, "John"); // em C para string deve-se usar o strcpy
    person.age = age;
    person.height = height;
    (*function_pointer)(person); // executa a funcao que veio no endereco chamado function_pointer
    } 

    // Declaracao da funcao que ira ter o seu endereco apontado na funcao creatPerson. Não é necessário declarar antes porque sera passada como referencia e o compilador não saberá que será a funcão declarada a baixo de onde é chamada. Ao contrario se tivesse sido declarada explicitamente, deveria ter sido declarada antes.
    void printPerson(struct Person person) {
        printf("Person: %s %d %d\n", person.name, person.age, person.height);

    }
    // Declaracao de uma outra funcao que terá seu endereco passado na funcao creatPerson tb
    void printPerson2(struct Person person) {
        printf("Nome: %s Age: %d height: %d\n", person.name, person.age, person.height);

    }

int main() {
    // No main() é feito a chamada para a funcao createPerson e passado os argumentos
       createPerson("John", 43, 172, &printPerson); // Usado o & porque queremos a referencia para a funcao
       // Esta ocorrendo um cast para a funcao. Que é a açao de declarar que tipo esse numero representa do compilador saber o que fazer
       createPerson("John", 43, 172, &printPerson2);
       // Com isso nota-se que a funcao createPerson aceita qualquer funcao compativel, ou seja que tenha a mesma assinatura (tipo de retorno e tipos de argumentos que ele espera). E assim esta configurado o callback
    return 0;   
}
