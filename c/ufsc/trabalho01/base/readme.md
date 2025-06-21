<div align="center">

<h1>INE5410 - Programação Concorrente</h1>
<img src='assets/concurrency.jpg' alt="Logo Programação Concorrente" width="220">

</div>

# Trabalho – Ordenação de Números Inteiros em Paralelo
___
2025/1
### 

[![C](https://img.shields.io/badge/linguagem-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![POSIX Threads](https://img.shields.io/badge/POSIX-pthreads-yellow.svg)](https://man7.org/linux/man-pages/man7/pthreads.7.html)
[![CLion](https://img.shields.io/badge/IDE-CLion-green.svg)](https://www.jetbrains.com/clion/)
___

## Grupo T1 - 07:

| Nome Completo                             | Matrícula   |
|-------------------------------------------|-------------|
| Lucas de Oliveira Marisco           | 24104721    |
|Eduardo Favacho de Queiroz Filho           | 20104838    |
| Carlos Benedito Hayden de Albuquerque Jr | 23100455    |

___

## Introdução

Este projeto implementa uma solução paralela escrita em C para ordenação de números inteiros sem sinal utilizando POSIX threads (pthreads). Desenvolvido para a disciplina INE5410 - Programação Concorrente (2025/1), o projeto demonstra paralelização eficiente e distribuição de tarefas para ordenação de grandes volumes de dados.
___

## Funcionalidades

- Ordenação paralela de inteiros sem sinal usando pthreads
- Alocação dinâmica de tarefas e threads
- Distribuição eficiente dos intervalos para balanceamento de carga
- Algoritmo bubble sort para ordenação local das tarefas
- Concatenação dos intervalos ordenados para o resultado final
___

## Como Usar

### Pré-requisitos

- GCC ou compilador C compatível
- Sistema compatível com POSIX (Linux, macOS)
- IDE de desenvolvimento C (opcional)

### Makefile
Como usar:

No terminal, na mesma pasta onde está sort.c, digite:

``` bash
    make
``` 

Isso irá gerar o executável `./program`.

Para remover o binário gerado:
``` bash
    make clean
```
### Compilação

```sh
gcc -o parallel_sort main.c -lpthread
```
### Execução

```sh
./program <input_file> <nnumbers> <ntasks> <nthreads>
```
- `input_file`: Arquivo contendo inteiros sem sinal separados por espaço
- `nnumbers`: Quantidade de inteiros no arquivo
- `ntasks`: Número de tarefas de ordenação (intervalos)
- `nthreads`: Número de threads para execução paralela

#### Exemplo
```sh
./program input.txt 100 20 4
```
### Estrutura do Projeto
```plaintext
./base
├── sort.c           # Lógica principal do programa
├── Makefile         # Makefile para compilação do programa
├── gera_dados.c     # Programa para geração de datasets de entrada
├── run_tests.sh     # Script para execução de testes e medição de desempenho
├── dados.txt        # Arquivo de entrada fornecido
├── dataset10000.txt # Exemplo de arquivo de entrada gerado
└── readme.md        # Documentação do projeto
```
___

## 1 Definição
Desenvolvimento uma solução paralela em C para o problema da ordenação de números inteiros sem sinal (**unsigned int**). 

> A solução deverá ser implementada com uso de POSIX threads (não é permitido o uso de OpenMP).
### Comportamento Esperado
#### O programa deverá funcionar da seguinte forma:
- O programa deverá receber 4 parâmetros de entrada via linha de comando na seguinte ordem:
  - `input`: um arquivo contendo números inteiros sem sinal desordenados e separados por espaço;
  - `nnumbers`: a quantidade de números armazenados no arquivo de entrada;
  - `ntasks`: o número de tarefas a serem executadas;
  - `nthreads`: o número de threads que executarão as tarefas em paralelo.
- O vetor de entrada sempre conterá valores entre `0` e `nnumbers-1`. 
> Por exemplo, um vetor de entrada de tamanho 10 (`nnumbers=10`) poderá conter somente números dentro da faixa [0, 10) enquanto um vetor de entrada de tamanho 30 (`nnumbers=30`) poderá conter somente números dentro da faixa [0, 30);

- O programa deverá ler os números do arquivo e armazenar em um vetor na memória de tamanho `nnumbers` alocado dinamicamente (`malloc`);
- A versão paralela deverá ter 3 etapas, descritas a seguir:
  - **Etapa 1**: O vetor contendo os números desordenados deverá ser dividido em um número específico de tarefas (`ntasks`), identificadas de `0` até `ntasks-1`. Cada tarefa deverá conter números a serem ordenados
  pertencentes a uma determinada faixa de valores. O tamanho mínimo dos intervalos de números em cada tarefa deverá ser obtido da seguinte forma:`intervalo = nnumbers/ntasks`. 
  Então, cada tarefa `i` deverá cobrir um intervalo `[i· intervalo, (i + 1)· intervalo)`, onde `i` é a *identificação da tarefa*. 
  Um tratamento especial deverá ser dado para os casos em que houver resto da divisão entre `nnumbers` e `ntasks`. Nestes casos, as faixas de números permitidos em cada tarefa deverão ter **uma diferença de tamanho de no  máximo 1 número**
  - **Etapa 2**: As threads deverão computar as tarefas existentes em paralelo. A computação de uma tarefa é
    a ordenação dos elementos presentes na tarefa usando-se o algoritmo bubble_sort fornecido;
  - **Etapa 3**: Uma vez finalizada a computação das tarefas, o programa deverá concatenar os resultados ordenados em cada tarefa em um único vetor na memória. Esta concatenação fará com que o vetor final esteja ordenado.
    
``` plaintext
Etapa 1) Vetor original desordenado:
[8] [3] [9] [2] [8] [1] [5] [4] [9] [5]

Distribuição dos números nas tarefas (por intervalo de valores):

Intervalo 0-1:   |   [1]         |
Intervalo 2-3:   | [3] [2]       |
Intervalo 4-5:   | [5] [4] [5]   |
Intervalo 6-7:   |     (vazio)   |
Intervalo 8-9:   | [8] [9] [8] [9]|

Etapa 2) Processamento das tarefas (bubble sort em cada intervalo):

Intervalo 0-1:   |   [1]         |
Intervalo 2-3:   | [2] [3]       |
Intervalo 4-5:   | [4] [5] [5]   |
Intervalo 6-7:   |     (vazio)   |
Intervalo 8-9:   | [8] [8] [9] [9]|

Etapa 3) Concatenação dos resultados:

[1] [2] [3] [4] [5] [5] [8] [8] [9] [9]
```
Figura 1: Exemplo com nnumbers=10 elementos e ntasks=5.

> Por exemplo, para `nnumbers`=20 e `ntasks`=8 teríamos 20/8 = 2 com resto igual a
Nesse caso, 4 tarefas teriam intervalos de 3 elementos e 4 tarefas teriam intervalos de 2 elementos. 
> 
> Um exemplo de intervalos para esse caso seria: 
>
>[0, 3), [3, 6), [6, 9), [9, 12), [12, 14), [14, 16), [16, 18) e [18, 20).


   
No exemplo da Figura 1 considerou-se `nnumbers`= 10. Logo, o vetor de entrada contém obrigatoriamente números entre *[0, 10)*. Estes números foram divididos em 5 tarefas (Etapa 1), cada um armazenando números em uma faixa contendo 2 valores possíveis: **[0, 2), [2, 4), ..., [8, 10)**. 

Note que uma das tarefas ficou vazia, pois não havia nenhum número pertencente ao intervalo [6, 8). Logo, essa tarefa poderá ser simplesmente descartada na Etapa 2. Os números em cada tarefa foram ordenados em paralelo (Etapa 2). Por fim, na Etapa 3, os números ordenados em cada tarefa foram concatenados, gerando o resultado final.
O programa deverá funcionar em todos os casos, independentemente do tamanho do vetor, número de tarefas ou threads, exceto nos seguintes casos: quando o número de threads for menor que 1 ou quando o número de tarefas for maior que o tamanho do vetor.
___
### Saída

   Ao final da execução, o seu programa deverá mostrar obrigatoriamente uma saída no seguinte formato: 
    vetor desordenado, atribuição de threads/tarefas (uma por linha) e vetor ordenado. Um exemplo de saída válido é mostrado abaixo com `nnumbers`=100, `ntasks`=20 e `nthreads`=4:

```plaintext
   10 48 39 84 3 45 20 48 47 73 4 19 31 45 30 71 10 72 84 10 64 22 20 11 63 17 11 84 73 2 21 8 24 50 54 29 87 53 33 86
   68 88 1 26 38 15 45 96 30 13 17 62 60 42 76 75 92 74 73 11 86 79 92 75 18 0 52 46 34 88 58 50 95 7 29 36 77 82 57 71
   23 55 12 14 21 0 50 78 55 45 83 51 95 62 50 71 11 56 37 46
   Thread 0 processando tarefa 0
   Thread 1 processando tarefa 1
   Thread 0 processando tarefa 2
   Thread 2 processando tarefa 3
   Thread 3 processando tarefa 4
   Thread 1 processando tarefa 5
   Thread 0 processando tarefa 6
   Thread 2 processando tarefa 7
   Thread 3 processando tarefa 8
   Thread 1 processando tarefa 9
   Thread 0 processando tarefa 10
   Thread 2 processando tarefa 11
   Thread 3 processando tarefa 12
   Thread 1 processando tarefa 13
   Thread 0 processando tarefa 14
   Thread 2 processando tarefa 15
   Thread 3 processando tarefa 16
   Thread 1 processando tarefa 17
   Thread 0 processando tarefa 18
   Thread 2 processando tarefa 19
   0 0 1 2 3 4 7 8 10 10 10 11 11 11 11 12 13 14 15 17 17 18 19 20 20 21 21 22 23 24 26 29 29 30 30 31 33 34 36 37 38 39
   42 45 45 45 45 46 46 47 48 48 50 50 50 50 51 52 53 54 55 55 56 57 58 60 62 62 63 64 68 71 71 71 72 73 73 73 74 75 75
   76 77 78 79 82 83 84 84 84 86 86 87 88 88 92 92 95 95 96
```
___
### Bubble Sort
Utilizou-se a implementação do algoritmo bubble_sort mostrado a seguir para ordenar os elementos dentro das tarefas. 
   
Os parâmetros `v` e `tam` correspondem ao vetor a ser ordenado e o seu tamanho, respectivamente.
```c
    void b u b b l e _ s o r t ( int *v , int tam ) {
        int i , j , temp , trocou ;
        for ( j = 0; j < tam - 1; j ++) {
            trocou = 0;
            for ( i = 0; i < tam - 1; i ++) {
                if ( v [ i + 1] < v [ i ]) {
                    temp = v [ i ];
                    v [ i ] = v [ i + 1];
                    v [ i + 1] = temp ;
                    trocou = 1;
                }
            }
            if (! trocou ) break ;
        }
    }
   
```
---
## Utilitários do Projeto

### Medição de Speedup

#### Execução dos Testes

Para medir o desempenho da implementação sequencial em comparação com a versão paralela, utilizamos o script `run_tests.sh`, que executa o programa com:

- **1 tarefa e 1 thread** (modo sequencial)
- **Várias tarefas e threads** (modo paralelo)

```bash
/bin/bash ./run_tests.sh
```

#### Exemplo de saída:
```plaintext
Tempo sequencial: 0.005048
Tempo paralelo:   0.000884
Speedup:          5.71040723981900452488
```
Speedup é uma métrica que quantifica o ganho de desempenho obtido com paralelização.
```plaintext
  Speedup = Tempo_sequencial / Tempo_paralelo
``` 
Onde:

- `Tempo_sequencial`: tempo de execução com 1 tarefa e 1 thread

- `Tempo_paralelo`: tempo de execução com múltiplas tarefas e threads

#### Interpretação
No exemplo acima, o speedup foi aproximadamente:
```plaintext
Speedup ≈ 0.005048 / 0.000884 ≈ 5.71
```
> Isso significa que a versão paralela foi **5,7 vezes** mais rápida que a versão sequencial, o que indica uma paralelização eficiente do algoritmo.

---
### Geração de Dataset de Entrada

Para gerar arquivos de entrada de qualquer tamanho, que podem ser utilizados para testar a ordenação paralela, 
utilizamos o programa `gera_dataset.c`, que cria um arquivo contendo números inteiros aleatórios e recebe como argumento a quantidade de números que serão gerados.

#### Compilando o gerador

Compile o programa `gera_dataset.c` com o gcc:
```bash
  gcc gera_dataset.c -o gera_dataset
```
Isso criará um executável chamado gera_dataset.
#### Utilização

Execute o programa passando como argumento a quantidade de números que deseja gerar. Por exemplo, para gerar um arquivo com `10.000` números:
```bash
  ./gera_dataset 10000
```
#### Saída

O programa irá gerar um arquivo chamado:

`dataset10000.txt`

Esse arquivo conterá 10.000 números aleatórios, separados por espaços em uma única linha, prontos para serem utilizados como entrada no programa principal de ordenação.
💡 Exemplo de conteúdo do arquivo gerado

```plaintext
459 8823 132 491 29 4 9999 102 9432 ...
```

___
## Conclusão


Este projeto demonstra com eficácia a aplicação de técnicas de programação concorrente em C, utilizando a biblioteca `POSIX Threads (pthreads)` 
para realizar a ordenação paralela de números inteiros sem sinal. 
A arquitetura do sistema foi projetada para explorar o paralelismo por tarefas, em que os dados são distribuídos dinamicamente entre 
múltiplas threads, garantindo balanceamento de carga e escalabilidade.

Entre os principais destaques técnicos:

- Distribuição de tarefas baseada em intervalos de valor para melhor particionamento dos dados;

- Execução paralela controlada por mutex, permitindo que múltiplas threads realizem ordenações independentes de forma segura;

- Medição precisa de desempenho com `gettimeofday`, permitindo análise quantitativa de desempenho e cálculo de speedup;

-  Análise de speedup que evidencia o ganho de desempenho proporcionado pelo uso de múltiplas threads em comparação com a execução sequencial;

-  Inclusão de scripts auxiliares para execução automatizada de testes e geração de datasets personalizados, facilitando a reprodutibilidade e 
experimentação.

Este projeto serve como um exemplo prático dos principais conceitos da disciplina INE5410 - Programação Concorrente (UFSC), 
sendo útil para o estudo de sincronização, divisão de tarefas e análise de desempenho em sistemas concorrentes. 
Além disso, a estrutura modular e a documentação tornam o projeto extensível para investigações futuras com algoritmos de ordenação mais 
sofisticados ou diferentes modelos de paralelismo.
___

## 📚 Referências

- **Material didático da disciplina INE5410 - Programação Concorrente (UFSC)**, incluindo slides e exemplos fornecidos em aula.
- HARTLEY, Stephen J. *Concurrent Programming: The Java Programming Language*. Oxford University Press, 1998. ISBN: 978-0-19-511315-0.
- TANENBAUM, Andrew S. *Sistemas Operacionais Modernos*. 3. ed. Rio de Janeiro: Pearson Prentice Hall, 2010. xiii, 653 p. ISBN: 9788576052371.
- GNU Bash Reference Manual. Free Software Foundation. Disponível em: https://www.gnu.org/software/bash/manual/
- The Shell Scripting Tutorial. Disponível em: https://www.shellscript.sh/

___
## 📄 Licença

Projeto acadêmico – uso restrito à disciplina INE5406 – UFSC.
___

# Autores

| [<sub>Lucas de Oliveira</sub>](https://github.com/JunhaumHayden) | [<sub>Eduardo Favacho</sub>](https://github.com/JunhaumHayden) | [<sub>Carlos Hayden</sub>](https://github.com/JunhaumHayden) |
| :---: | :---: | :---: |

Disciplina: INE5410 - Programação Concorrente (2025/1)