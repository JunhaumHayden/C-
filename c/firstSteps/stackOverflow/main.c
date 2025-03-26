/*
Por recursão infinita, o programa vai estourar a pilha de execução, pois a cada chamada da função f1, um novo endereço de memória é alocado na pilha de execução, e como a função f1 é chamada recursivamente, a pilha de execução vai estourar (zsh: segmentation fault  ./main).
Os endereços da pilha de execução inicam nos endereços mais altos (logo depois da alocação do Kernel na memoria) da memoria e vão decrementando até o meio da memória (STACK).
*/

#include <stdio.h>
void f1(char hello[]) {
    printf("from f3: %x\n", &hello); // print the address of the local pointer hello (first element of the array) in the function f1 stack
    f1(hello); // pass by value
}

void main() {
    char hello[] = "Hello, World!";
    printf("from main: %x\n", &hello); // print the address of the local pointer hello (first element of the array) in the function main stack
    f1(hello); // pass by value
}