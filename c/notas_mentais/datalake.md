# Datalake Test

No MacBook M1 com Homebrew instalado, pode-se testar vazamentos de memória em programas C utilizando ferramentas como:

## 1️⃣ Valgrind (com Homebrew) 
**failed in 2025**

Por padrão, o Valgrind não tem suporte oficial para macOS no M1/ARM64, mas pode ser instalado e usado via Rosetta.

### Passos para instalar e rodar:

- Instale o Valgrind com Homebrew:
```bash
brew install --HEAD valgrind
```
Como o Valgrind não tem suporte oficial para macOS ARM, pode ser necessário rodá-lo em modo Rosetta.
Compilar o código C com debug symbols (-g):
```bash
gcc -g -o meu_programa meu_programa.c
```
Rodar o Valgrind (via Rosetta):
```bash
arch -x86_64 valgrind --leak-check=full ./meu_programa
```
Se houver vazamentos, o Valgrind mostrará detalhes como endereços e quantidade de memória não liberada.

### fault 👎
```bash
(base) hayden@cliente-150-162-230-48 struct % brew install --HEAD valgrind

valgrind: Linux is required for this software.
Error: valgrind: An unsatisfied requirement failed this build.
```

## 2️⃣ AddressSanitizer (Alternativa mais eficiente)
O AddressSanitizer (ASan) é embutido no compilador `clang` do macOS e funciona bem no M1.

### Como usar ASan

Compilar com as flags `-fsanitize=address e -g` para debug:
```bash
clang -fsanitize=address -g -o meu_programa meu_programa.c
```
Executar normalmente:
```bash
./meu_programa
```
Se houver vazamentos, o programa imprimirá mensagens detalhadas informando os locais do erro.

## 3️⃣ libmalloc (Ferramenta Nativa do macOS)
**Operacional em 2025**

O macOS tem uma ferramenta integrada para detectar vazamentos de memória.

Necessário compilar com a flag de debbuging:
```bash
gcc meu_programa.c -g -o meu_programa
```
Isso evita que bloqueie a inspeção detalhada da memória de processos que não foram marcados como "debuggáveis".

Execute o programa com leaks e permissão de administrador:
```bash
sudo leaks -atExit -- ./meu_programa
```
Se houver vazamentos, o comando imprimirá os blocos de memória alocados e não liberados.

### Conclusão
Para uma solução completa: Tente Valgrind (via Rosetta) ou AddressSanitizer.
Para algo rápido e nativo: Use leaks do próprio macOS.

## Exemplo de Saida Sem Vazamento

A saída do comando `leaks -atExit -- ./main` no MacBook M1 apresenta algumas informações importantes sobre a execução do programa, a alocação de memória e a análise de possíveis vazamentos. Vamos analisar a saída passo a passo:

### 1️⃣ Mensagens iniciais do MallocStackLogging
```bash
main(37897) MallocStackLogging: could not tag MSL-related memory as no_footprint, so those pages will be included in process footprint - (null)
main(37897) MallocStackLogging: recording malloc (and VM allocation) stacks using lite mode
```
### 📌 Explicação:
O [MallocStackLogging](https://developer-apple-com.translate.goog/library/archive/documentation/Performance/Conceptual/ManagingMemory/Articles/FindingLeaks.html?_x_tr_sl=en&_x_tr_tl=pt&_x_tr_hl=pt&_x_tr_pto=tc) é um recurso do macOS usado para rastrear alocações de memória, permitindo que ferramentas como `leaks` e `Instruments` detectem problemas de vazamento.

- Ele informa que não conseguiu excluir a memória alocada pelo próprio sistema (no_footprint), o que significa que esses blocos serão contabilizados na análise.
- Está operando no modo "lite", que gera menos impacto no desempenho do programa.

### 4️⃣ Mensagem de restrição de segurança
```bash
Process 37897 is not debuggable. Due to security restrictions, leaks can only show or save contents of readonly memory of restricted processes.
```
### 📌 Explicação:

O macOS bloqueia a inspeção detalhada da memória de processos que não foram marcados como "debuggáveis".
Para obter mais informações, rode o programa com privilégios de depuração, por exemplo:
```bash
sudo leaks -atExit -- ./main
```
ou desative as restrições SIP (não recomendado).

### 5️⃣ Relatório do leaks
```bash 
Process:         main [37897]
Path:            /Users/USER/*/main
Load Address:    0x100260000
Identifier:      main
Version:         0
Code Type:       ARM64
Platform:        macOS
Parent Process:  leaks [37895]

Date/Time:       2025-03-26 19:34:38.759 -0300
Launch Time:     2025-03-26 19:34:38.565 -0300
OS Version:      macOS 15.3.2 (24D81)
Report Version:  7
Analysis Tool:   /usr/bin/leaks
Physical footprint:         1905K
Physical footprint (peak):  1905K
Idle exit:                  untracked
```
### 📌 Explicação:

Aqui temos informações gerais sobre o processo analisado, o tempo de execução e a versão do macOS.
A memória física ocupada pelo programa foi 1905 KB.

### 6️⃣ Resumo da análise de vazamento
```bash
leaks Report Version: 4.0, multi-line stacks
Process 37897: 187 nodes malloced for 15 KB
Process 37897: 0 leaks for 0 total leaked bytes.
```
### 📌 Explicação:

O programa alocou 187 blocos de memória, totalizando 15 KB.
Nenhum vazamento foi detectado! 🎉 Isso significa que todas as alocações foram liberadas corretamente.

## 🔎 Conclusão

Seu programa não apresenta vazamentos de memória! ✅

A struct person foi alocada corretamente na Stack.
A struct heapPerson foi alocada na Heap e aparentemente foi liberada corretamente.
O leaks não encontrou memória não liberada, indicando que free() foi usado corretamente (se malloc() foi usado).

## Exemplo de Saida com vazamento 

A saída do comando leaks -atExit -- ./main mostra um relatório de vazamento de memória no seu programa main. Vamos analisar as partes principais do relatório e destacar as linhas mais importantes.

### 1. Interpretação da Saída

- 🔹 Mensagem inicial
```bash
main(40491) MallocStackLogging: could not tag MSL-related memory as no_footprint, so those pages will be included in process footprint - (null)
main(40491) MallocStackLogging: recording malloc (and VM allocation) stacks using lite mode
```
➡️ Isso informa que a ferramenta MallocStackLogging está ativa e coletando informações sobre alocações de memória.

- 🔹 Relatório de vazamento de memória
```bash
Process 40491: 1 leak for 32 total leaked bytes.
```
➡️ Há 1 vazamento de memória detectado no processo, totalizando 32 bytes.

- 🔹 Stack trace do vazamento
```bash
STACK OF 1 INSTANCE OF 'ROOT LEAK: <malloc in main>':
2   dyld                                  0x19091c274 start + 2840
1   main                                  0x102e43e2c main + 216  hellostruct.c:66
0   libsystem_malloc.dylib                0x190ad376c _malloc_zone_malloc_instrumented_or_legacy + 148 
```
➡️ O vazamento ocorreu na linha 66 do arquivo hellostruct.c, onde provavelmente há um malloc() sem um correspondente free().

- 🔹 Informação detalhada do vazamento
```bash
1 (32 bytes) ROOT LEAK: <malloc in main 0x12ff040f0> [32]
```
➡️ Foi alocado um bloco de 32 bytes que não foi liberado corretamente.

### 1. Linhas mais importantes para analisar

- 1️⃣ Número de vazamentos e tamanho total
```bash
Process 40491: 1 leak for 32 total leaked bytes.
```
🧐 Isso indica se seu programa tem vazamentos e quantos bytes foram perdidos.

- 2️⃣ Linha do código onde o vazamento ocorre
```bash
1   main                                  0x102e43e2c main + 216  hellostruct.c:66
```
🧐 Aqui você encontra a linha exata onde a alocação aconteceu. No seu caso, é a linha 66 de hellostruct.c.

- 3️⃣ Tamanho do bloco de memória vazado
```bash
1 (32 bytes) ROOT LEAK: <malloc in main 0x12ff040f0> [32]
```
🧐 Isso mostra que há um bloco de 32 bytes não liberado.