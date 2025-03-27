# A função printf()
A função `printf()` tem a seguinte forma geral:
`printf(string_de_controle, lista_de_argumentos)`

Teremos, na string de controle, uma descrição de tudo que a
função vai colocar na tela.
Isto é feito usando-se os códigos de controle (especificador de formato - format specifies type), veja alguns
exemplos:

| Código | Significado       |
|--------|-------------------|
| %d     | Inteiro (**D**ecimal) |
| %f     | **F**loat            |
| %c     | **C**aractere        |
| %s     | **S**tring           |
| %p     | **P**ointer addresses   |
| %x     | he**X**adecimal      |
| %%     | Coloca um % na tela |

> O especificador de tipo %x em C é usado em funções como printf() e scanf() para representar números inteiros no formato hexadecimal (base 16).

> 📌 Uso no printf()
> `%x` → Exibe o número em hexadecimal com letras minúsculas (a a f).
> 
> `%X` → Exibe o número em hexadecimal com letras maiúsculas (A a F).
>
> `%02x`→ Exibe o número em formato hexadecimal, com dois dígitos (completando com 0 à esquerda, se necessário).
> 
> 📌 Dica: Se quiser exibir um número hexadecimal com o prefixo 0x, use # antes do x no printf():
>```c
>printf("Hexadecimal com prefixo: %#x\n", num);
>```
>Saída:
>```c
>Hexadecimal com prefixo: 0xff
>```
>```c
>#include <stdio.h>
>
>int main() {
>    int num = 255;
>
>    printf("Decimal: %d\n", num);    // Saída: Decimal: 255
>    printf("Hexadecimal: %x\n", num); // Saída: Hexadecimal: ff
>    printf("Hexadecimal (maiúsculas): %X\n", num); // Saída: Hexadecimal (maiúsculas): FF
>    printf("Hexadecimal (dois digitos): %02x\n", num); // Saída: Hexadecimal (maiúsculas): FF
>    printf("Hexadecimal (prefixo 0x): %#x\n", num); // Saída: Hexadecimal (maiúsculas): FF
>
>    return 0;
>}
>```
> ver [arquivo](../firstSteps/formatSpecifiesType.c)




# Struct
> ver arquivo /struct/hellostruct.c
estrutura de dados imutavel com elementos de tipos diferentes que vão concatenando. Pode nomear essa nova estrutura dentro da linguagem, serve como um molde que quebra os valores passados como argumentos para dentro do espaço de elemento.
# Tuple != Array
Tuple é como um Struct anomino, sem nomes ou etiquetas
- Tuple: estrutura de dados (conjunto) imutavel com elementos de tipos diferentes.
- Array: estrutura de dados (conjunto) imutavel com elementos de mesmo tipo.
- Struct: estrutura de dados 