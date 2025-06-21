\documentclass[12pt]{article}
\usepackage[utf8]{inputenc}
\usepackage[brazil]{babel}
\usepackage{amsmath, amssymb}
\usepackage{graphicx}
\usepackage{float}
\usepackage{listings}
\usepackage{geometry}
\geometry{margin=2.5cm}

\title{Projeto II — Estrutura de Dados: Implementação de Trie para Indexação de Palavras}
\author{Hayden Junior \ Universidade Federal de Santa Catarina (UFSC) \ INE5408 — Estrutura de Dados e Algoritmos (2025/1)}
\date{Junho de 2025}

\begin{document}

\maketitle

\section\*{Resumo / Introdução}
O objetivo deste projeto é implementar uma estrutura de dados do tipo \textit{Trie} para realizar a indexação e identificação de prefixos em um conjunto de palavras provenientes de arquivos com extensão \texttt{.dic}. Esta estrutura é particularmente eficiente para buscas prefixadas e é amplamente utilizada em sistemas de sugestão automática, correção ortográfica e compressão de dados.

A proposta foi desenvolvida como parte da disciplina INE5408 — Estrutura de Dados e Algoritmos (2025/1) da UFSC, com foco em consolidar conhecimentos sobre estruturas hierárquicas e seu uso prático.

\section{Descrição da Solução e Algoritmos}

\subsection{Representação da Trie}
A \textit{Trie} foi implementada utilizando uma estrutura de nó com os seguintes campos:

\begin{itemize}
\item Um vetor de ponteiros com tamanho igual ao alfabeto suportado (neste caso, 26 letras minúsculas);
\item Um campo booleano que indica se aquele nó representa o final de uma palavra válida;
\item Um vetor dinâmico de strings que armazena os índices das palavras inseridas, utilizado para permitir a indexação reversa.
\end{itemize}

\subsection{Inserção de Palavras}
Para inserir uma palavra, percorre-se a Trie a partir da raiz, criando nós intermediários conforme necessário. Cada letra da palavra corresponde a um nível na árvore. Ao final, o nó terminal é marcado como fim de palavra.

\begin{lstlisting}[language=C++, caption={Função de inserção}]
void Trie::inserir(const std::string& palavra, const std::string& origem) {
Trie\* no = this;
for (char c : palavra) {
int index = c - 'a';
if (!no->filhos[index])
no->filhos[index] = new Trie();
no = no->filhos[index];
}
no->ehFim = true;
no->origens.push\_back(origem);
}
\end{lstlisting}

\subsection{Busca por Prefixo}
A busca por prefixos percorre a Trie conforme o prefixo fornecido. Caso o prefixo completo seja encontrado, o algoritmo lista todas as palavras abaixo daquele nó, utilizando recursão para percorrer a sub-árvore.

\subsection\*{Figura 1: Trie com palavras pequenas}
\begin{figure}[H]
\centering
\includegraphics[width=0.75\textwidth]{trie\_exemplo1.png}
\caption{Trie formada pelas palavras: bear, bell, bid, ...\
• Fase 3: P´os-Processamento\
return tag\_stack . empty () ; // Retorna true se\
todas as tags foram fechadas\
3\. Complexidade Computacional:\
• Tempo: O(n) — onde n ´e o n´umero total de caracteres do XML.\
• Espa¸co: O(m) — onde m representa a profundidade m´axima de aninhamento\
de tags.\
4\. Exemplo de Execu¸c˜ao:\
\<cenario>\
\<nome>teste\</nome>\
\</cenario>\
• Passos:\
→ Empilha "cenario"\
→ Empilha "nome"\
→ Desempilha "nome" (match com \</nome>)\
→ Desempilha "cenario" (match com \</cenario>)\
→ Retorna true (pilha vazia)\
5\. Otimiza¸c˜oes Implementadas:\
• Processamento em um ´unico passe: Evita m´ultiplas varreduras no texto\
• Early return: Retorna false imediatamente ao detectar erros\
• Uso eficiente de mem´oria: A pilha s´o armazena nomes de tags, n˜ao o\
conte´udo completo\
6

6\. Limita¸c˜oes Conhecidas:\
• N˜ao valida atributos em tags (\<tag attr=value>)\
• N˜ao verifica caracteres especiais em conte´udo\
• Case-sensitive (diferencia \<Tag> de \<tag>)\
7

2.2 Processamento dos Cen´arios\
A classe Cenario ´e respons´avel por extrair e armazenar os dados de cada cen´ario\
presente no XML. A extra¸c˜ao ´e feita por meio da navega¸c˜ao pelas tags com a fun¸c˜ao\
proxima tag conteudo. A matriz ´e reconstru´ıda como uma string de bin´arios e seus\
dados s˜ao convertidos em uma estrutura 2D para facilitar o processamento.\
2.3 Determina¸c˜ao da ´Area Limpa\
Utilizou-se uma fila (estrutura de dados queue) para realizar a busca em largura\
(BFS). A ´area naveg´avel ´e calculada a partir do ponto inicial fornecido. Apenas as c´elulas\
conectadas diretamente (4 dire¸c˜oes) que contenham valor 1 e ainda n˜ao tenham sido\
visitadas s˜ao consideradas.\
Algoritmo (BFS - Breadth-First Search): Para calcular a ´area conexa a partir\
da posi¸c˜ao inicial:\
1\. Inicializa¸c˜ao:\
• Convers˜ao da matriz string para representa¸c˜ao 2D\
• Cria¸c˜ao de matriz de visitados\
• Fila para gerenciar pontos a serem processados\
2\. Processamento:\
• Para cada ponto, verifica vizinhan¸ca-4\
• Pontos v´alidos (valor 1 e n˜ao visitados) s˜ao adicionados \`a fila\
• ´Area incrementada para cada ponto processado\
8

Figura 1: Exemplo de BFS em matriz bin´aria mostrando expans˜ao da busca\
Explica¸c˜ao da Implementa¸c˜ao da Fun¸c˜ao calcular area limpa()\
1\. Prop´osito e Contexto:\
A fun¸c˜ao calcular area limpa() implementa um algoritmo BFS (Breadth-First\
Search) para determinar a ´area conexa acess´ıvel por um robˆo aspirador em uma\
matriz bin´aria, considerando movimentos na vizinhan¸ca-4 (cima, baixo, esquerda,\
direita):\
2\. Assinatura e Estrutura:\
size\_t calcular\_area\_limpa ( const Cenario & cenario ) {\
// 1. Pre - processamento da matriz\
// 2. Inicializacao das estruturas\
// 3. Nucleo do algoritmo BFS\
// 4. Retorno do resultado\
}\
9

3\. Processamento Passo a Passo:\
• Passo 1: Pr´e-processamento da Matriz\
vector < vector < int > > matriz ( cenario . altura ,\
vector < int >( cenario . largura , 0) ) ;\
// Converte a string linear para matriz 2 D\
for ( size\_t i = 0; i < cenario . altura ; i ++) {\
for ( size\_t j = 0; j < cenario . largura ; j\
++) {\
size\_t index = i \* cenario . largura +\
j ;\
if ( index < cenario . matriz . size () ) {\
matriz [ i ][ j ] = cenario . matriz [\
index ] - ’0 ’; // Converte char\
’0 ’/ ’1 ’ para int\
}\
}\
}\
...\
• Passo 2: Inicializa¸c˜ao\
// Verifica se a posicao inicial e valida\
if ( cenario . x >= cenario . altura || cenario . y\
\>= cenario . largura ||\
matriz [ cenario . x ][ cenario . y ] != 1) {\
return 0;\
}\
// Estruturas auxiliares\
queue < pair < size\_t , size\_t > > fila ;\
10

vector < vector < bool > > visitado ( cenario . altura ,\
vector < bool >( cenario . largura , false ) ) ;\
// Configuracao inicial\
fila . push ( make\_pair ( cenario .x , cenario . y ) ) ;\
visitado [ cenario . x ][ cenario . y ] = true ;\
size\_t area = 0;\
...\
• Passo 3: N´ucleo do BFS\
// Direcoes da vizinhanca -4 ( cima , baixo ,\
esquerda , direita )\
const int dx [] = { -1 , 1 , 0 , 0};\
const int dy [] = {0 , 0 , -1 , 1};\
while (! fila . empty () ) {\
auto [x , y ] = fila . front () ;\
fila . pop () ;\
area ++;\
// Explora os 4 vizinhos\
for ( int i = 0; i < 4; i ++) {\
size\_t nx = x + dx [ i ];\
size\_t ny = y + dy [ i ];\
// Verifica se o vizinho e valido\
if ( nx < cenario . altura && ny <\
cenario . largura &&\
! visitado [ nx ][ ny ] && matriz [ nx ][\
ny ] == 1) {\
visitado [ nx ][ ny ] = true ;\
11

fila . push ( make\_pair ( nx , ny ) ) ;\
}\
}\
}\
4\. Fluxo de Execu¸c˜ao Exemplificado:\
• Para uma matriz 3x3:\
1 1 0\
1 0 1\
0 1 0\
Com ponto inicial (0,0):\
– Itera¸c˜ao 1: Processa (0,0), ´area=1\
Adiciona (1,0) e (0,1) \`a fila\
– Itera¸c˜ao 2: Processa (1,0), ´area=2\
Adiciona (2,0) - mas (2,0) ´e 0 (inv´alido)\
– Itera¸c˜ao 3: Processa (0,1), ´area=3\
Adiciona (1,1) - mas (1,1) ´e 0 (inv´alido)\
Adiciona (0,2) - mas (0,2) ´e 0 (inv´alido)\
– Resultado Final: ´Area = 3\
5\. Complexidade Computacional:\
Opera¸c˜ao Complexidade Descri¸c˜ao\
Convers˜ao da matriz O(n2) n = altura × largura\
BFS O(V + E) V = v´ertices, E = arestas (m´ax. 4V )\
Espa¸co O(n2) Matriz de visitados\
12

6\. Otimiza¸c˜oes Cr´ıticas:\
• Matriz de Visitados: Evita reprocessamento\
• Checagem de Limites: Antes de cada acesso \`a matriz\
• Early Return: Retorna 0 imediatamente se posi¸c˜ao inicial inv´alida\
• Aloca¸c˜ao Est´atica: Uso de vetores pr´e-alocados para desempenho\
7\. Diagrama de Estados do BFS:\
[Posi¸c\~ao Inicial]\
→ [Marcar como Visitada]\
→ [Adicionar \`a Fila]\
→ [Enquanto Fila n\~ao vazia]\
→ [Processar Vizinhan¸ca]\
→ [´Area++]\
→ [Retornar Total]\
8\. Alternativas Consideradas e Rejeitadas:\
• Vizinhan¸ca-8:\
Pr´os: Consideraria diagonais\
Contras: N˜ao atendia aos requisitos do projeto\
• Union-Find:\
Pr´os: Eficiente para m´ultiplas consultas\
Contras: Overhead desnecess´ario para caso de uso ´unico\
13

3 Dificuldades e Desafios\
3.1 Valida¸c˜ao de XML\
• Problema relativamente simples com uso direto de pilha\
• Dificuldade principal foi no parsing correto das tags considerando todos os casos\
extremos\
3.2 C´alculo da ´Area Limpa\
• Desafio significativo na convers˜ao da matriz string para representa¸c˜ao 2D\
• Dificuldade na implementa¸c˜ao eficiente do BFS com vizinhan¸ca-4\
• Problemas com ´ındices e limites da matriz\
• Necessidade de otimiza¸c˜ao para evitar processamento duplicado\
• Testes extensivos para garantir corretude em todos os cen´arios\
4 Referˆencias Bibliogr´aficas\
1\. DROZDEK, Adam. Estruturas de dados e algoritmos em C++. 4. ed. S˜ao Paulo:\
Cengage Learning, 2013.\
2\. LAFORE, Robert. Estruturas de dados & algoritmos em Java. 2. ed. Rio de\
Janeiro: Ciˆencia Moderna, 2005.\
3\. Documenta¸c˜ao C++: https\://en.cppreference.com/w/\
4\. Tutorial C++: https\://www\.cplusplus.com/doc/tutorial/\
14

5 Conclus˜ao\
O projeto demonstrou a efic´acia das estruturas de dados lineares na resolu¸c˜ao de\
problemas complexos. Enquanto a valida¸c˜ao de XML foi relativamente simples com uso de\
pilha, o c´alculo da ´area limpa exigiu maior esfor¸co na implementa¸c˜ao e testes do algoritmo\
BFS. A solu¸c˜ao final atende a todos os requisitos, mostrando robustez e eficiˆencia no\
processamento dos cen´arios.\
15bull, buy, sell, stock, stop}
\end{figure}

\subsection{Leitura dos Arquivos \texttt{.dic}}
Cada linha dos arquivos \texttt{.dic} contém uma única palavra. As palavras são normalizadas (convertidas para minúsculas e filtradas) antes da inserção. A origem de cada palavra (nome do dicionário) é registrada para fins de indexação.

\section{Execução do Programa}

O programa é executado com o seguinte formato:

\begin{verbatim}
./program \<arquivo\_dic>   ...&#x20;

dicionario1.dic bear bell bid bu bull buy but sell stock stop 0
\end{verbatim}

Onde:

\begin{itemize}
\item \texttt{arquivo\_dic}: caminho para o arquivo .dic contendo palavras
\item \texttt{palavraX}: prefixos a serem buscados
\item \texttt{modo}: define se a busca será por prefixo exato (0) ou por palavra completa (1)
\end{itemize}

\section\*{Figura 2: Resultado da Busca por Prefixo}
\begin{figure}[H]
\centering
\includegraphics[width=0.6\textwidth]{trie\_exemplo2.png}
\caption{Resultado da busca pelo prefixo \texttt{bu} retorna bull, buy, but}
\end{figure}

\section{Complexidade e Comparação}
\begin{itemize}
\item \textbf{Inserção e busca na Trie}: \(O(m)\), onde \(m\) é o tamanho da palavra ou prefixo. Como não há varredura linear, é mais eficiente que buscas em listas ou vetores ordenados.
\item \textbf{Busca linear tradicional}: \(O(n \cdot m)\), sendo \(n\) o número de palavras e \(m\) o tamanho médio das palavras. É significativamente menos eficiente para grandes volumes.
\end{itemize}

A Trie elimina comparações desnecessárias ao utilizar diretamente a estrutura da palavra para guiar o acesso à memória.

\section{Conclusão}

O de...\
• Fase 3: P´os-Processamento\
return tag\_stack . empty () ; // Retorna true se\
todas as tags foram fechadas\
3\. Complexidade Computacional:\
• Tempo: O(n) — onde n ´e o n´umero total de caracteres do XML.\
• Espa¸co: O(m) — onde m representa a profundidade m´axima de aninhamento\
de tags.\
4\. Exemplo de Execu¸c˜ao:\
\<cenario>\
\<nome>teste\</nome>\
\</cenario>\
• Passos:\
→ Empilha "cenario"\
→ Empilha "nome"\
→ Desempilha "nome" (match com \</nome>)\
→ Desempilha "cenario" (match com \</cenario>)\
→ Retorna true (pilha vazia)\
5\. Otimiza¸c˜oes Implementadas:\
• Processamento em um ´unico passe: Evita m´ultiplas varreduras no texto\
• Early return: Retorna false imediatamente ao detectar erros\
• Uso eficiente de mem´oria: A pilha s´o armazena nomes de tags, n˜ao o\
conte´udo completo\
6

6\. Limita¸c˜oes Conhecidas:\
• N˜ao valida atributos em tags (\<tag attr=value>)\
• N˜ao verifica caracteres especiais em conte´udo\
• Case-sensitive (diferencia \<Tag> de \<tag>)\
7

2.2 Processamento dos Cen´arios\
A classe Cenario ´e respons´avel por extrair e armazenar os dados de cada cen´ario\
presente no XML. A extra¸c˜ao ´e feita por meio da navega¸c˜ao pelas tags com a fun¸c˜ao\
proxima tag conteudo. A matriz ´e reconstru´ıda como uma string de bin´arios e seus\
dados s˜ao convertidos em uma estrutura 2D para facilitar o processamento.\
2.3 Determina¸c˜ao da ´Area Limpa\
Utilizou-se uma fila (estrutura de dados queue) para realizar a busca em largura\
(BFS). A ´area naveg´avel ´e calculada a partir do ponto inicial fornecido. Apenas as c´elulas\
conectadas diretamente (4 dire¸c˜oes) que contenham valor 1 e ainda n˜ao tenham sido\
visitadas s˜ao consideradas.\
Algoritmo (BFS - Breadth-First Search): Para calcular a ´area conexa a partir\
da posi¸c˜ao inicial:\
1\. Inicializa¸c˜ao:\
• Convers˜ao da matriz string para representa¸c˜ao 2D\
• Cria¸c˜ao de matriz de visitados\
• Fila para gerenciar pontos a serem processados\
2\. Processamento:\
• Para cada ponto, verifica vizinhan¸ca-4\
• Pontos v´alidos (valor 1 e n˜ao visitados) s˜ao adicionados \`a fila\
• ´Area incrementada para cada ponto processado\
8

Figura 1: Exemplo de BFS em matriz bin´aria mostrando expans˜ao da busca\
Explica¸c˜ao da Implementa¸c˜ao da Fun¸c˜ao calcular area limpa()\
1\. Prop´osito e Contexto:\
A fun¸c˜ao calcular area limpa() implementa um algoritmo BFS (Breadth-First\
Search) para determinar a ´area conexa acess´ıvel por um robˆo aspirador em uma\
matriz bin´aria, considerando movimentos na vizinhan¸ca-4 (cima, baixo, esquerda,\
direita):\
2\. Assinatura e Estrutura:\
size\_t calcular\_area\_limpa ( const Cenario & cenario ) {\
// 1. Pre - processamento da matriz\
// 2. Inicializacao das estruturas\
// 3. Nucleo do algoritmo BFS\
// 4. Retorno do resultado\
}\
9

3\. Processamento Passo a Passo:\
• Passo 1: Pr´e-processamento da Matriz\
vector < vector < int > > matriz ( cenario . altura ,\
vector < int >( cenario . largura , 0) ) ;\
// Converte a string linear para matriz 2 D\
for ( size\_t i = 0; i < cenario . altura ; i ++) {\
for ( size\_t j = 0; j < cenario . largura ; j\
++) {\
size\_t index = i \* cenario . largura +\
j ;\
if ( index < cenario . matriz . size () ) {\
matriz [ i ][ j ] = cenario . matriz [\
index ] - ’0 ’; // Converte char\
’0 ’/ ’1 ’ para int\
}\
}\
}\
...\
• Passo 2: Inicializa¸c˜ao\
// Verifica se a posicao inicial e valida\
if ( cenario . x >= cenario . altura || cenario . y\
\>= cenario . largura ||\
matriz [ cenario . x ][ cenario . y ] != 1) {\
return 0;\
}\
// Estruturas auxiliares\
queue < pair < size\_t , size\_t > > fila ;\
10

vector < vector < bool > > visitado ( cenario . altura ,\
vector < bool >( cenario . largura , false ) ) ;\
// Configuracao inicial\
fila . push ( make\_pair ( cenario .x , cenario . y ) ) ;\
visitado [ cenario . x ][ cenario . y ] = true ;\
size\_t area = 0;\
...\
• Passo 3: N´ucleo do BFS\
// Direcoes da vizinhanca -4 ( cima , baixo ,\
esquerda , direita )\
const int dx [] = { -1 , 1 , 0 , 0};\
const int dy [] = {0 , 0 , -1 , 1};\
while (! fila . empty () ) {\
auto [x , y ] = fila . front () ;\
fila . pop () ;\
area ++;\
// Explora os 4 vizinhos\
for ( int i = 0; i < 4; i ++) {\
size\_t nx = x + dx [ i ];\
size\_t ny = y + dy [ i ];\
// Verifica se o vizinho e valido\
if ( nx < cenario . altura && ny <\
cenario . largura &&\
! visitado [ nx ][ ny ] && matriz [ nx ][\
ny ] == 1) {\
visitado [ nx ][ ny ] = true ;\
11

fila . push ( make\_pair ( nx , ny ) ) ;\
}\
}\
}\
4\. Fluxo de Execu¸c˜ao Exemplificado:\
• Para uma matriz 3x3:\
1 1 0\
1 0 1\
0 1 0\
Com ponto inicial (0,0):\
– Itera¸c˜ao 1: Processa (0,0), ´area=1\
Adiciona (1,0) e (0,1) \`a fila\
– Itera¸c˜ao 2: Processa (1,0), ´area=2\
Adiciona (2,0) - mas (2,0) ´e 0 (inv´alido)\
– Itera¸c˜ao 3: Processa (0,1), ´area=3\
Adiciona (1,1) - mas (1,1) ´e 0 (inv´alido)\
Adiciona (0,2) - mas (0,2) ´e 0 (inv´alido)\
– Resultado Final: ´Area = 3\
5\. Complexidade Computacional:\
Opera¸c˜ao Complexidade Descri¸c˜ao\
Convers˜ao da matriz O(n2) n = altura × largura\
BFS O(V + E) V = v´ertices, E = arestas (m´ax. 4V )\
Espa¸co O(n2) Matriz de visitados\
12

6\. Otimiza¸c˜oes Cr´ıticas:\
• Matriz de Visitados: Evita reprocessamento\
• Checagem de Limites: Antes de cada acesso \`a matriz\
• Early Return: Retorna 0 imediatamente se posi¸c˜ao inicial inv´alida\
• Aloca¸c˜ao Est´atica: Uso de vetores pr´e-alocados para desempenho\
7\. Diagrama de Estados do BFS:\
[Posi¸c\~ao Inicial]\
→ [Marcar como Visitada]\
→ [Adicionar \`a Fila]\
→ [Enquanto Fila n\~ao vazia]\
→ [Processar Vizinhan¸ca]\
→ [´Area++]\
→ [Retornar Total]\
8\. Alternativas Consideradas e Rejeitadas:\
• Vizinhan¸ca-8:\
Pr´os: Consideraria diagonais\
Contras: N˜ao atendia aos requisitos do projeto\
• Union-Find:\
Pr´os: Eficiente para m´ultiplas consultas\
Contras: Overhead desnecess´ario para caso de uso ´unico\
13

3 Dificuldades e Desafios\
3.1 Valida¸c˜ao de XML\
• Problema relativamente simples com uso direto de pilha\
• Dificuldade principal foi no parsing correto das tags considerando todos os casos\
extremos\
3.2 C´alculo da ´Area Limpa\
• Desafio significativo na convers˜ao da matriz string para representa¸c˜ao 2D\
• Dificuldade na implementa¸c˜ao eficiente do BFS com vizinhan¸ca-4\
• Problemas com ´ındices e limites da matriz\
• Necessidade de otimiza¸c˜ao para evitar processamento duplicado\
• Testes extensivos para garantir corretude em todos os cen´arios\
4 Referˆencias Bibliogr´aficas\
1\. DROZDEK, Adam. Estruturas de dados e algoritmos em C++. 4. ed. S˜ao Paulo:\
Cengage Learning, 2013.\
2\. LAFORE, Robert. Estruturas de dados & algoritmos em Java. 2. ed. Rio de\
Janeiro: Ciˆencia Moderna, 2005.\
3\. Documenta¸c˜ao C++: https\://en.cppreference.com/w/\
4\. Tutorial C++: https\://www\.cplusplus.com/doc/tutorial/\
14

5 Conclus˜ao\
O projeto demonstrou a efic´acia das estruturas de dados lineares na resolu¸c˜ao de\
problemas complexos. Enquanto a valida¸c˜ao de XML foi relativamente simples com uso de\
pilha, o c´alculo da ´area limpa exigiu maior esfor¸co na implementa¸c˜ao e testes do algoritmo\
BFS. A solu¸c˜ao final atende a todos os requisitos, mostrando robustez e eficiˆencia no\
processamento dos cen´arios.\
15senvolvimento do projeto permitiu a aplicação prática de estruturas de dados não-lineares em um cenário real de busca e indexação. As principais dificuldades encontradas envolveram:

\begin{itemize}
\item Tratamento correto de caracteres não alfabéticos;
\item Normalização das entradas e verificação de consistência;
\item Organização modular do projeto (uso de \texttt{main.cpp}, \texttt{trie.cpp}, \texttt{trie.hpp});
\item Integração com Makefile e organização por diretórios.
\end{itemize}

A estrutura de Trie provou ser eficiente e extensível, sendo possível adaptar o projeto para inclusão de buscas por sufixo, compressão (Trie compactada) e análise estatística de prefixos.

\section\*{Referências}
\begin{enumerate}
\item [https://en.wikipedia.org/wiki/Trie](https://en.wikipedia.org/wiki/Trie)
\item [https://www.geeksforgeeks.org/trie-insert-and-search/](https://www.geeksforgeeks.org/trie-insert-and-search/)
\item Cormen, T. H. et al. \textit{Introduction to Algorithms}, MIT Press, 3rd ed.
\item [https://cplusplus.com/doc/tutorial/](https://cplusplus.com/doc/tutorial/)
\end{enumerate}

\end{document}

