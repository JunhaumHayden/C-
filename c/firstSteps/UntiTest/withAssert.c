/*
Testes Manuais com assert.h (Padrão do C)

Usa a biblioteca assert.h, que já vem na libc. Ela é uma forma simples de fazer testes unitários em C. Veja um exemplo:
para executar: gcc -o test test.c && ./test

Retorna uma mensagem de erro na linha de comando se o teste falhar.
``bash
Assertion failed: (soma(2, 2) == 5), function test_soma, file whitAssert.c, line 18.
zsh: abort      ./test
```
*/
#include <stdio.h>
#include <assert.h>

int soma(int a, int b) {
    return a + b;
}

void test_soma() {
    assert(soma(2, 3) == 5);  // Passa ✅
    assert(soma(-1, 1) == 0); // Passa ✅
    assert(soma(2, 2) == 5);  // Falha ❌
}

int main() {
    test_soma();
    printf("Todos os testes passaram!\n");
    return 0;
}
