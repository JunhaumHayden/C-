// Exemplo de implementacao de orientaçao a objetos de uma forma pedagogica. (Não é assim na pratica).
// Devemos pensar em:
// um ponteiro para uma struct
// um ponteiro para uma funcao (que será o this ou self), que é um ponteiro de volta para a mesma struct
// refatorando o codigo para orientaçao a objetos
// Primeiro alterar o fato de que creatPerson()   esta declarando a struct na stack e quando chama a printPerson() tá duplicando a struct na stack por causa da passagem por valor.
// ao ivés disso vamos alocar a struct na heap e passar um ponteiro para a struct fazendo passagem por referencia.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#define Class struct // define uma macro chamada Class que é um alias para struct ou seja onde estiver escrito Class é o mesmo que struct.

Class Person {
    char name[10];
    uint8_t age;
    uint8_t height;
    void(*show)(Class Person *);
};


void person_print(Class Person *self) {
    printf("Nome: %s Age: %d height: %d\n", self->name, self->age, self->height);
}

 
Class Person * newPerson(char name[], uint8_t age, uint8_t height){ 
    Class Person *self = (Class Person *)malloc(sizeof(Class Person));
    strcpy(self->name, "John");
    self->height = height;
    self->age = age;

    self->show = &person_print;
    return self;
} 

int main() {
        Class Person *person2 = (Class Person *) newPerson("John", 43, 172);
        person2->show(person2);
        free(person2); // Libera a memória alocada para a struct Person
    return 0;   
}

