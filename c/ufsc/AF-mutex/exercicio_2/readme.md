# Exercício 2
Um estagiário escreveu um programa paralelo de multiplicação de matrizes. 
Para gerar e multiplicar 2 matrizes 40 x 40 usando 2 threads, o programa é chamado 
assim:
```c
./program 40 2
```
Quando o programa é executado com uma thread apenas, tudo funciona. 
Mas quando o programa é chamado com 2 threads ou mais, há erros no resultado.

O estagiário não teve disciplina de programação concorrente antes, e por isso não 
usou nenhum mutex. Conserte o código do estagiário inserindo um mutex e o utilizando 
nos pontos adequados do arquivo `main.c` e no arquivo `thread.c`. 
Preserve ao máximo o paralelismo!

> **Importante**:
> 
> A seção crítica que precisa ser sincronizada está na função matrix_mult_worker (em thread.c).
>
> Inicialize e destrua o mutex na função main (em main.c).
>
> O arquivo helper.c não poderá ser alterado.