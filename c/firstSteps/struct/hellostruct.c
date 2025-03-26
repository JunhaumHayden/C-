// Struct é uma estrutura de dados em C que pode conter membros(elementos) de diferentes tipos de dados e com tamanhos diferentes. Ao contrário de um arrays que tem que ser do mesmo tipo e tamanho fixo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> //fornece um conjunto de macros, constantes e tipos de dados para manipulação de inteiros de tamanho fixo. Ela é especialmente útil para garantir que seu código seja portátil entre diferentes plataformas e arquiteturas, onde o tamanho dos tipos de dados inteiros pode variar.
// Principais recursos fornecidos por inttypes.h:
//Tipos de dados inteiros de tamanho fixo: Tipos como int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t garantem que você tenha inteiros com tamanhos específicos, independentemente da plataforma.
//Macros de formatação: Macros como PRId8, PRIu8, PRId16, PRIu16, etc., que ajudam a formatar esses tipos de dados de tamanho fixo ao usar funções como printf e scanf.
//Constantes de inteiros: Macros como INT8_MAX, UINT8_MAX, INT16_MAX, UINT16_MAX, etc., que definem os valores máximos e mínimos para esses tipos de dados.


struct Person {
    //declaracao de uma struct chamada Person
    char name[10];
    //primeiro elemento da struct é um array de 10 bytes
    uint8_t age;
    //segundo elemento da struct é um inteiro de 8 bits ou 1 byte
    uint8_t height;
    //terceiro elemento da struct é um inteiro de 8 bits ou 1 byte
};

int main() {
    // Definindo um tipo de dado novo chamado Person com o tamanho total sempre será 12 bytes
    // A struct Person é uma estrutura de dados que contém três membros: name, age e height, e o C irá preencher com os dados passados em sequencia apartir do endereço apontado em person.
    // O primeiro endereco conterá o char 'J', o segundo o char 'o', o terceiro o char 'h', o quarto o char 'n', os demais preencherá com '00' (ou lixo), o decimo primeiro o int 43, o decimo segundo o int 172.
    //   Exemplo de preenchimento na stack
    // Address in person: 0x16fdfe95c
    // Address: 0x16fdfe95c, Value: 4a // J
    // Address: 0x16fdfe95d, Value: 6f // o
    // Address: 0x16fdfe95e, Value: 68 // h
    // Address: 0x16fdfe95f, Value: 6e // n
    // Address: 0x16fdfe960, Value: 00 // caracter de parada
    // Address: 0x16fdfe961, Value: 00 // lixo
    // Address: 0x16fdfe962, Value: 47 // lixo
    // Address: 0x16fdfe963, Value: fa // lixo
    // Address: 0x16fdfe964, Value: 01 // lixo
    // Address: 0x16fdfe965, Value: 00 // lixo
    // Address: 0x16fdfe966, Value: 2b // 43
    // Address: 0x16fdfe967, Value: ac // 172  
    struct Person person;
    strcpy(person.name, "John"); // em C para string deve-se usar a função strcpy() para copiar a string para o array de char
    person.age = 43;             // em C para inteiros deve-se usar o '=' e '.' para acessar o membro da struct   
    person.height = 172;

    printf("Address in person: %p\n", &person);
    // char *person2 = ((char*)&person) + 6;
    // printf("from person2: %s\n", person2);

    for (size_t i = 0; i < sizeof(person); i++) {
        printf("Address: %p, Value: %02x\n", (unsigned char*)&person + i, *((unsigned char*)&person + i));
        // %02x: Especificador de formato usado para imprimir o valor do byte em formato hexadecimal, com dois dígitos (completando com 0 à esquerda, se necessário).
        // &person: Obtém o endereço da estrutura person na memória.
        // (unsigned char*): Faz um cast (conversão) do ponteiro para o tipo unsigned char*. Isso é necessário porque queremos acessar a memória byte a byte, e unsigned char é o menor tipo de dado em C (1 byte).
    }    

// Explicação do loop para interar sobre os endereços:
// Inicialização: size_t i = 0 - Inicializa a variável i com 0.
// size_t é um tipo de dado definido na biblioteca padrão do C (em <stddef.h> ou <stdio.h>). Ele é usado para representar tamanhos de objetos em bytes e é o tipo de retorno da função sizeof.
// Condição: i < sizeof(person) - Continua o loop enquanto i for menor que o tamanho da estrutura person.
// Incremento: i++ - Incrementa i em 1 a cada iteração.
// Dentro do loop, o código imprime o endereço e o valor de cada byte da estrutura Person.

// Por que usar size_t?
// Usar size_t é uma prática recomendada porque ele é garantido para ser grande o suficiente para conter o tamanho de qualquer objeto em bytes, o que evita problemas de overflow que poderiam ocorrer se um tipo com sinal fosse usado.
    printf("Heap Allocation Example\n");
    struct Person *heapPerson = (struct Person*) malloc(sizeof(struct Person));
    strcpy(heapPerson->name, "John"); 
    heapPerson->age = 43;  
    heapPerson->height = 172;

    printf("Address in heapPerson: %p\n", heapPerson);
    // char *person2 = ((char*)heapPerson) + 6;
    // printf("from person2: %s\n", person2);

    for (size_t i = 0; i < sizeof(*heapPerson); i++) {
        printf("Address: %p, Value: %02x\n", (unsigned char*)heapPerson + i, *((unsigned char*)heapPerson + i));
    }

    free(heapPerson); // libera a memória alocada na heap

    return 0;
    
};
