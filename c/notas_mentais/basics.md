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

# atoi() - ASCII to Integer
> Ex: Explicação da Linha int n_threads = atoi(argv[1]);

Esta linha de código está fazendo duas operações importantes:

### 1. argv[1] - Acessando o argumento da linha de comando

`argv` é o array de strings que contém os argumentos passados ao programa na linha de comando
- `argv[0]` é sempre o nome do próprio programa
- `argv[1]` é o primeiro argumento após o nome do programa
> Ex: No comando ./program 2 16 17, os valores seriam:
> `argv[0]` = "./program"
> `argv[1]` = "2" (número de threads)
> `argv[2]` = "16" (primeiro valor para compute)
> `argv[3]` = "17" (segundo valor para compute)
### 2. atoi() - Convertendo string para inteiro

> atoi significa "ASCII to integer"

É uma função da biblioteca padrão C (stdlib.h) que converte uma string em um valor inteiro
Recebe como parâmetro uma string (no caso, argv[1] que é "2")
Retorna o valor inteiro correspondente (no exemplo, retornaria 2)
#### Comportamento importante do atoi():

Se a string não representar um número válido, `retorna 0`

Isso é usado na verificação seguinte: if (!n_threads || ...)
> Exemplos:
> 
> atoi("123") → 123
>
> atoi("-45") → -45
>
> atoi("0") → 0
>
> atoi("abc") → 0
> 
> atoi("12a34") → 12 (converte até encontrar caractere não numérico)

Por que é necessário nesta aplicação?

O programa precisa saber quantas threads criar, e esse número é passado 
como primeiro argumento na linha de comando. 
Como todos os argumentos de linha de comando chegam como strings (char*),
precisamos converter para um número inteiro que possa ser usado no 
restante do programa.

### Alternativas modernas:

Em C moderno, poderia-se usar `strtol()` que tem melhor tratamento de 
erros:

```c
char* endptr;
int n_threads = strtol(argv[1], &endptr, 10);
if (endptr == argv[1] || *endptr != '\0') {
// Tratamento de erro - conversão falhou
}
```
Mas `atoi()` é suficiente para este contexto onde já há verificação 
posterior do valor (if (!n_threads...)).



O erro estava na função mult_matrix, utilizar "#pragma omp parallel for" dentro de outro "parallel for" (paralelismo aninhado) estava causando problemas como uma condição de corrida no out[i*cols_right + j] += ... porque várias threads estavam acessando e modificar a mesma posição da matriz de saida simultaneamente. para corrigir isso tiramos um dos "parallel for" e utilizamos somente um, esse aqui: #pragma omp parallel for collapse(2), utilizamos esse pois assim conseguiriamos paralelizar os dois primeiros loops (i e j) de forma combinada. Além disso utilizamos uma variavel local chamda sum para receber a soma e evitar acesso simultâneo à mesma posição da matriz de saída.

Olá estagiário,

Identificou-se alguns problemas no seu código de multiplicação de matrizes que explicam os resultados incorretos e o desempenho abaixo do esperado:

1. Race Condition (Condição de Corrida)

O principal erro está na paralelização do loop mais interno da multiplicação:

Problema: Várias threads estão tentando atualizar out[i*cols_right+j] ao mesmo tempo, causando uma condição de corrida. Quando múltiplas threads acessam e modificam a mesma variável simultaneamente sem sincronização, o resultado final fica incorreto.

Solução: Movemos a paralelização apenas para o loop externo e usamos uma variável local sum para acumular os resultados antes de escrever na matriz de saída.

2. Paralelização Excessiva

Você usou três níveis de paralelização:

No loop externo (i)
No loop do meio (j)
No loop interno (k)
Problema: Isso cria um overhead enorme de gerenciamento de threads sem benefício real, pois:

- Cada thread adicional tem custo de criação
- O trabalho por thread fica muito pequeno
- O sistema gasta mais tempo gerenciando threads do que computando
Solução: Paralelizamos apenas o loop mais externo (i), que fornece trabalho suficiente para cada thread e minimiza o overhead.

3. Agendamento Ineficiente

Você usou:

- schedule(guided) na inicialização
- schedule(dynamic,1) na multiplicação
Problema: Esses esquemas de agendamento introduzem overhead desnecessário para matrizes, onde o trabalho é uniformemente distribuído.

Solução: Usamos schedule(static), que:

- Divide o trabalho igualmente entre as threads no início
- Tem quase zero overhead durante a execução
- É ideal para cargas de trabalho regulares como matrizes