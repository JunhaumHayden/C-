# Exercício 3
Um engenheiro fez um programa que funcionava em um computador antigo que, infelizmente, queimou. 
Ao rodar o programa em um computador moderno, o programa apenas trava e não faz nada. 
Arqueólogos  e outros estudiosos se debruçaram sobre o código-fonte e observaram o seguinte:

- O programa recebe como primeiro argumento um número de threads. Os argumentos subsequentes são argumentos da função `compute`, 
a ser executada por cada uma das threads com o argumento correspondente.
- O programa faz uso de mutex e sincroniza o acesso a uma variável global chamada `gValue`.
- Quando executado, o programa fica travado para sempre.
- De acordo com o código-fonte, a intenção do engenheiro seria de que, ao ser chamado com os 
argumentos 2 16 17, o programa produzisse o seguinte resultado:
```bash
$ ./program 2 16 17
results[0]: 987
results[1]: 1597
```
Estudiosos determinaram que os cálculos feitos pelo programa estão corretos, mas há um erro 
no uso do mutex `gMtx`.
## Encontre esse erro e o corrija.
Importante:
- O arquivo `helper.c` não poderá ser alterado. 
- Hás três abordagens possíveis para solucionar o problema:
1. Você pode alterar a forma como o mutex é usado, de modo que o programa não trave. 
Essa solução resolve o problema, mas é questionável. Se a adotar, pense nas consequências.
2. Outra opção é usar um mutex recursivo. Este tipo de mutex permite que uma thread que já é 
dona do mutex faça um segundo lock sem travar. Para liberar o mutex, a thread deve fazer um 
unlock para cada lock feito.

   **Essa é a solução mais "fácil"**.
   - Para criar um mutex recursivo, use o argumento `pthread_mutexattr_t attr` no `pthread_mutex_init()`.
   - Aloque uma variável `attrs` do tipo `pthread_mutexattr_t`;
   - Inicialize `attrs` usando `pthread_mutexattr_init(&attrs)`;
   - Sete o tipo do mutex para `PTHREAD_MUTEX_RECURSIVE` usando `pthread_mutexattr_settype()` 
   (se tiver dificuldades para fazê-lo, consulte essa [página](https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_init.html) e essa [outra](https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_settype.html);
   - Inicialize o mutex com os atributes em `attrs` usando `pthread_mutex_init()`;
   - Por fim, destrua `attrs` usando `pthread_mutexattr_destroy()`.
3. A função `compute()` pode ser reescrita de modo que nenhum mutex seja necessário no programa. 
Essa solução aproveita melhor o paralelismo!

## Comparação com as outras soluções:

Solução com mutex normal modificado (01)
- ✅ Mantém estrutura original
- ❌ Ainda tem problemas de serialização
- ❌ Resultados podem ser imprevisíveis

Solução com mutex recursivo (02)
- ✅ Mantém estrutura original intacta
- ✅ Fácil de implementar
- ❌ Performance inferior à solução ideal
- ❌ Ainda usa variável global desnecessariamente

Solução ideal (03): Elimina o mutex completamente, usando variáveis locais
- ✅ Melhor desempenho
- ✅ Design mais limpo
- ❌ Requer reescrever a função compute