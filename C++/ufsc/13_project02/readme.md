<div align="center">

<h1>INE5408 - Estrutura de Dados e Algoritmos</h1>
<img src='https://identidade.inf.ufsc.br/Ensino_colorida_vertical.png' alt="Logo INE" width="200">

</div>


# Projeto II - identificação de prefixos e indexação de dicionários Laboratório Virtual de Programação
___
2025/1
### 

[![C++](https://img.shields.io/badge/linguagem-C++-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![trie](https://img.shields.io/badge/trie-retrieval-yellow.svg)](https://man7.org/linux/man-pages/man7/pthreads.7.html)
[![CLion](https://img.shields.io/badge/IDE-CLion-green.svg)](https://www.jetbrains.com/clion/)
___

## Introdução

Este projeto implementa, em C++, uma estrutura de dados do tipo Trie (árvore digital), com o objetivo de permitir a identificação eficiente de 
prefixos e a indexação de palavras contidas em arquivos de dicionário. Desenvolvido como parte da disciplina INE5408 – Estrutura de Dados e 
Algoritmos (2025/1) da UFSC, o projeto explora manipulação de strings, estruturas hierárquicas e busca eficiente em arquivos armazenados em 
memória secundária.

## Objetivo

Este trabalho consiste na construção e utilização de estrutura hierárquica denominada trie (do inglês "retrieval", sendo também 
conhecida como árvore de prefixos ou ainda árvore digital) para a indexação e recuperação eficiente de palavras em grandes arquivos 
de dicionários (mantidos em memória secundária). A implementação deverá resolver dois problemas (listados a seguir), e os resultados 
deverão ser formatados em saída padrão de tela de modo que possam ser automaticamente avaliados no VPL.

#### A figura a seguir exemplifica a organização de um arquivo de dicionário. 
Cada linha apresenta a definição de uma palavra, sendo composta, no início, pela própria palavra com todos os caracteres em minúsculo 
(somente entre `a` (97) e `z` (122) da tabela ASCII) e envolvida por colchetes, seguida pelo texto de seu significado. 

> Não há símbolos especiais, acentuação, cedilha, etc, no arquivo.


![Image](https://github.com/user-attachments/assets/5f611fc5-9ffb-4f6e-9f41-24613312dc10)

## Materiais

De modo a exemplificar as entradas para o seu programa, seguem os arquivos de dicionário utilizados nos testes:

- [dicionario1.dic](data/dicionario1.dic)
- [dicionario2.dic](data/dicionario2.dic)

#### Dicas para implementação de tries:

- [USP](https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/tries.html)

- [towardsdatascience](https://towardsdatascience.com/implementing-a-trie-data-structure-in-python-in-less-than-100-lines-of-code-a877ea23c1a1)

- [geeksforgeeks](https://www.geeksforgeeks.org/trie-insert-and-search/)
 
## Primeiro problema: identificação de prefixos

Construir a *trie*, em memória principal, a partir das palavras (definidas entre colchetes) de um arquivo de dicionário, conforme o 
exemplo acima. A partir deste ponto, a aplicação deverá receber uma série de palavras quaisquer (pertencentes ou não ao dicionário) 
e responder se trata de um prefixo (a mensagem `P is prefix of N words` deve ser produzida, onde `P` é o nome da palavra e `N` é a 
quantidade de palavras) ou não (a mensagem `P is not prefix` deve ser produzida na saída padrão). 

Sugestão de nó da trie:
```c
NoTrie {
char           letra;        //opcional
NoTrie        *filhos[26];
unsigned long  posição;
unsigned long  comprimento;  //se maior que zero, indica último caracter de uma palavra
}
``` 

## Segundo problema: indexação de arquivo de dicionário

A construção da *trie* deve considerar a localização da palavra no arquivo e o tamanho da linha que a define. 
Para isto, ao criar o nó correspondente ao último caracter da palavra, deve-se atribuir a **posição do caracter inicial** 
(incluindo o abre-colchetes `[`), seguida pelo **comprimento da linha** (não inclui o caracter de mudança de linha) na qual esta palavra 
foi definida no arquivo de dicionário. Caso a palavra recebida pela aplicação exista no dicionário, estes dois inteiros devem ser 
determinados. 
> **Importante**: uma palavra existente no dicionário também pode ser prefixo de outra; neste caso, o caracter final da palavra será 
> encontrado em um nó **não-folha** da *trie* e duas linhas deverão ser produzidas na saída padrão, a mensagem `P is prefix of N words` na 
> primeira linha, e `P is in (D,C)` na linha seguinte (sendo `D` a posição, e `C` o comprimento).

### Exemplo:

Segue uma entrada possível para a aplicação, exatamente como configurada no VPL, contendo o nome do arquivo de dicionário a ser 
considerado, cuja a trie deve ser construída (no caso para `dicionario1.dic` da figura acima), e uma sequência de palavras, 
separadas por um espaço em branco e finalizada por `0` (zero); e a saída que deve ser produzida neste caso.

**Entrada**:
```plaintext
dicionario1.dic bear bell bid bu bull buy but sell stock stop 0
```

**Saída**:
```plaintext
bear is prefix of 1 words
bear is at (0,149)
bell is prefix of 1 words
bell is at (150,122)
bid is prefix of 1 words
bid is at (273,82)
bu is prefix of 2 words
bull is prefix of 1 words
bull is at (356,113)
buy is prefix of 1 words
buy is at (470,67)
but is not prefix
sell is prefix of 1 words
sell is at (538,97)
stock is prefix of 1 words
stock is at (636,79)
stop is prefix of 1 words
stop is at (716,92)
```
---
## Funcionalidades

- Construção de uma Trie a partir de arquivos .dic contendo palavras e seus significados

- Verificação de prefixos: identifica se uma palavra é prefixo de outras palavras no dicionário

- Indexação: retorna a posição e o comprimento da definição no arquivo para palavras existentes

- Leitura e análise de grandes arquivos diretamente da memória secundária

- Estrutura otimizada para operações rápidas de busca
---

### Estrutura do Projeto
```plaintext
./project02
├── src/            
│   ├── main.cpp                 # Função principal
│   ├── trie.cpp
│   └── trie.hpp
├── data/
│   ├── dicionario.dic           # Arquivo de entrada fornecido
│   └── dicionario.dic           # Arquivo de entrada fornecido
├── Makefile                     # Compilação do projeto
└── README.md                    # Documentação do projeto
```
---
## Como Usar
### Pré-requisitos

- Compilador C++ compatível com C++11 ou superior (como g++)

- Sistema compatível com POSIX (Linux, WSL, macOS)

- CLion ou outra IDE C++ (opcional)

---
### Compilação

- Para compilar o projeto com o Makefile, use:
```bash
  make
```

Isso irá gerar o executável program.

- Para limpar os arquivos objeto e o executável gerado:
```bash
  make clean
```

Ou, para compilar manualmente:
```bash
  g++ -std=c++11 -o program src/main.cpp
```
### Execução

Execute o programa informando o nome do arquivo de dicionário seguido pelas palavras a serem verificadas, finalizando com 0.


Exemplo:
```bash
  ./program <dicionario.dic> <palavra1> <palavra2> ... <palavraN> 0

```
Parâmetros:

- `dicionario.dic`: Caminho para o arquivo contendo o dicionário a ser analisado. 
> Cada linha deve começar com uma palavra entre colchetes `[]`, seguida pela sua definição.

-  `palavra1` ... `palavraN`: Sequência de palavras que serão verificadas se são prefixos ou palavras completas no dicionário.

-   `0`: Valor sentinela que indica o fim da entrada de palavras.

Exemplo de uso:

```bash
  ./program data/dicionario1.dic bear bell bid bu bull buy but sell stock stop 0
```
Saída esperada:
```bash
    bear is prefix of 1 words
    bear is at (0,149)
    bell is prefix of 1 words
    bell is at (150,122)
    ...
```
---
## Análise de Complexidade

A escolha da estrutura Trie representa uma melhoria significativa em relação à busca linear tradicional:

| Operação               | 	Busca Linear | 	Trie        |
|------------------------|---------------|--------------|
| Inserção de N palavras | 	𝑂(𝑁 × 𝐿)  | 	𝑂(𝑁 × 𝐿) |
| Busca de palavra       | 	𝑂(𝑁 × 𝐿)  | 	𝑂(𝐿)      |
| Verificação de prefixo | 	𝑂(𝑁 × 𝐿)  | 	𝑂(𝐿)      |

> N = número de palavras no dicionário, L = comprimento médio das palavras

Com a Trie, a complexidade de busca deixa de depender do número de palavras e passa a depender apenas do tamanho da entrada, 
resultando em ganho expressivo de desempenho, especialmente em dicionários com milhares ou milhões de entradas.

___
## Conclusão

Este projeto demonstra com eficácia a aplicação da estrutura de dados Trie (árvore digital) em C++, voltada para a resolução 
eficiente de problemas de identificação de prefixos e indexação de palavras em grandes arquivos de dicionário. A arquitetura 
da aplicação foi cuidadosamente projetada para otimizar a leitura e análise de palavras diretamente de arquivos em memória 
secundária, mantendo uma estrutura hierárquica na memória principal para buscas rápidas.

Entre os principais destaques técnicos:

- Construção de uma Trie com 26 ponteiros por nó (um para cada letra minúscula do alfabeto), permitindo acesso direto aos ramos da árvore;

- Inserção eficiente de palavras, armazenando nos nós finais a posição e o comprimento da linha no arquivo de origem;

- Busca otimizada para verificação de prefixos e presença exata de palavras, permitindo geração de saídas conforme especificado no VPL;

- Organização modular do código, separando responsabilidades de leitura, construção da árvore e verificação das palavras;

- Compatibilidade com arquivos grandes, demonstrando escalabilidade da abordagem sem comprometer a performance.


Este projeto serve como um exemplo prático dos principais conceitos da disciplina INE5408 – Estrutura de Dados e Algoritmos (UFSC), sendo útil para o estudo de estruturas hierárquicas, manipulação de strings e eficiência de algoritmos de busca. Além disso, a estrutura modular e a documentação tornam o projeto extensível para investigações futuras, como o suporte a palavras com acentuação, compressão de nós da trie (trie compacta), ou integração com mecanismos de autocompletar.


___

## 📚 Referências

- **Material didático da disciplina INE5408 - Estrutura de Dados e Algoritmos (UFSC)**, incluindo slides e exemplos fornecidos em aula. 
- DROZDEK, Adam. Estruturas de dados e algoritmos em C++. 4. ed. São Paulo: Cengage Learning, 2013. 
- LAFORE, Robert. Estruturas de dados & algoritmos em Java. 2. ed. Rio de Janeiro: Ciˆencia Moderna, 2005.
- GNU Bash Reference Manual. Free Software Foundation. Disponível em: https://www.gnu.org/software/bash/manual/
- The Shell Scripting Tutorial. Disponível em: https://www.shellscript.sh/

___
## 📄 Licença

Projeto acadêmico – uso restrito à disciplina INE5406 – UFSC.
___


# Author

| [<img src="https://avatars.githubusercontent.com/u/79289647?v=4" width=115><br><sub>Carlos Hayden</sub>](https://github.com/JunhaumHayden) |
| :---: |

Disciplina: INE5410 - Programação Concorrente (2025/1)