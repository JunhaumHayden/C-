// Passagem por valor
// cada chamada recursiva é passada por valor, ou seja duplicada. 
// Cada chamada recursiva esta empilhando um novo endereço de memória para onde o return vai dar jump de volta (64-bits ou 4 bytes) + a duplicata de "hello world" (12 bytes) totalizando 16 bytes a cada chamada.
// Caso ao invés de "hello world" fosse um vetor de 1 milhão de bytes, a cada chamada recursiva seriam empilhados 1 milhão de bytes. O que esgotaria a memoria rapidamente.
#include <stdio.h> 
void f2 (char hello[]) {
    printf("from f2: %p\n", (void*)&hello);
    printf("%s\n", hello);
}
void f1 (char hello[]) {
    printf("from f1: %p\n", (void*)&hello);
    f2(hello);
}
int main () {
    char hello[] = "Hello World!";
    printf("from main: %p\n", (void*)&hello);
    f1(hello);
    return 0;
}