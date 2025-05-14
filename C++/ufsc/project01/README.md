




<h1 align="center"> Projeto de Verificação de Cenários e Determinação de Área Limpa para um Robô Aspirador  </h1>

---

<p align="center">
<img src="http://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=GREEN&style=for-the-badge"/>
</p>


## 🧐 O que é isso?  

### Objetivo

Este projeto consiste na utilização de estruturas lineares, vistas até o momento no curso, e aplicação de conceitos de pilha e/ou fila para o processamento de arquivos XML contendo matrizes binárias que representam cenários de ação de um robô aspirador. A implementação deverá resolver dois problemas (listados a seguir), e os resultados deverão ser formatados em saída padrão de tela de modo que possam ser automaticamente avaliados no VPL.

**Entradas**:
    - cenarios.zip
**Saídas esperadas**
    - Saída padrão de tela
    - Arquivo de saída: vpl_evaluate.cases:

## Materiais

De modo a exemplificar uma entrada para o programa, segue o arquivo XML utilizado no primeiro teste:

Arquivo compactado com todos os arquivos XML: 
- cenarios.zip

>dicas sobre leitura e escrita com arquivos em C++
http://www.cplusplus.com/doc/tutorial/files/
para a criação e concatenação de palavras/caracteres, sugere-se o uso da classe string:
http://www.cplusplus.com/reference/string/string/


## Primeiro problema: validação de arquivo XML

Verificação de aninhamento e fechamento das marcações (tags) no arquivo XML (qualquer outra fonte de erro pode ser ignorada). 
- Se houver um erro de aninhamento, deve se impresso `erro` na tela. 
- Um identificador constitui uma marcação entre os caracteres `<` e `>`, podendo ser de abertura (por exemplo: `<cenario>`) ou de fechamento com uma / antes do identificador (por exemplo: `</cenario>`).
- O algoritmo para resolver este problema é baseado em pilha (LIFO):

1. Ao encontrar uma marcação de abertura, empilha o identificador
2. Ao encontrar uma marcação de fechamento, verifica se o topo da pilha tem o mesmo identificador e desempilha. Aqui duas situações de erro podem ocorrer:
   1. Ao consultar o topo, o identificador é diferente (ou seja, uma marcação aberta deveria ter sido fechada antes)
   2. Ao consultar o topo, a pilha encontra-se vazia (ou seja, uma marcação é fechada sem que tenha sido aberta antes)
3. Ao finalizar a análise (parser) do arquivo, é necessário que a pilha esteja vazia. Caso não esteja, mais uma situação de erro ocorre, ou seja, há marcação sem fechamento
   
## Segundo problema: determinação de área do espaço que o robô deve limpar

Cada XML, contém matrizes binárias, com altura e largura, definidas respectivamente pelas marcações `<altura>` e `<largura>`, e sequência dos pontos, em modo texto, na marcação `<matriz>`. Cada ponto corresponde a uma unidade de área, sendo `0` para *não pertencente* ou `1` para *pertencente* ao espaço que deve ser limpo, como passo mínimo do robô em uma de quatro direções possíveis (vizinhança-4),  Para cada uma dessas matrizes, pretende-se determinar a área (quantidade de pontos iguais a `1` na região do robô) que deve ser limpa, conforme a posição inicial, linha `<x>` e coluna `<y>`, do robô (primeira linha e primeira coluna são iguais a zero). Para isso, seguem algumas definições importantes:

1. A vizinhança-4 de um ponto na linha x e coluna y, ou seja, na coordenada (x,y), é um conjunto de pontos adjacentes nas coordenadas:
    
    (x-1, y)
    
    (x+1, y)
    
    (x, y-1)
    
    (x, y+1)

2. Um caminho entre um um ponto p1 e outro pn é em um sequência de pontos distintos <p1,p2,...,pn>, de modo que pi é vizinho-4 de pi+1., sendo i=1,2,...,n-1

3. Um ponto p é conexo a um ponto q se existir um caminho de p a q (no contexto deste trabalho, só há interesse em pontos com valor 1, ou seja, pertencentes ao espaço a ser limpo)

4. Um componente conexo é um conjunto maximal (não há outro maior que o contenha) C de pontos, no qual quaisquer dois pontos selecionados deste conjunto C são conexos

Para a determinação da área a ser limpa, é necessário identificar quantos pontos iguais a `1` estão na região em que o robô se encontra, ou seja, é preciso determinar a área do componente conexo. 

- O algoritmo de reconstrução de componente conexo usando uma fila (FIFO):

1. Criar uma matriz R de 0 (zeros) com o mesmo tamanho da matriz de entrada E lida

2. Inserir (x,y) na fila
   - na coordenada (x,y) da imagem R, atribuir 1

3. Enquanto a fila não estiver vazia
   - (x,y) ← remover da fila
   - inserir na fila as coordenadas dos quatro vizinhos que estejam dentro do domínio da matriz (não pode ter coordenada negativa ou superar o número de linhas ou de colunas), com intensidade 1 (em E) e ainda não tenha sido visitado (igual a 0 em R)
      - na coordenada de cada vizinho selecionado, na imagem R, atribuir 1
      
O conteúdo final da matriz R corresponde ao resultado da reconstrução. A quantidade de 1 (uns) deste único componente conexo é a resposta do segundo problema.

## Estrutura do Projeto

```bash
robot_cleaner/
├── include/
│   ├── XmlValidator.hpp         # Validação de XML (pilha)
│   ├── MatrixLoader.hpp         # Leitura e modelagem das matrizes
│   ├── ConnectedArea.hpp        # Busca do componente conexo (fila)
│   └── Utils.hpp                # Funções auxiliares (ex: trim, split, etc)
├── src/
│   ├── XmlValidator.cpp
│   ├── MatrixLoader.cpp
│   ├── ConnectedArea.cpp
│   └── main.cpp                 # Função principal
├── data/
│   └── cenarios/                # Onde os XMLs serão descompactados
│       ├── cenarios1.xml
│       ├── cenarios2.xml
│       ├── cenarios3.xml
│       ├── cenarios4.xml
│       ├── cenarios5.xml
│       └── cenarios6.xml
├── output/
│   └── vpl_evaluate.cases       # Resultados do programa
├── Makefile                     # Compilação do projeto
└── README.md                    # Instruções e explicações
``` 

## Explicação detalhada da implementação
### 1. Classe Cenario

#### Propósito:
Extrai e armazena os dados de cada cenário do arquivo XML.

#### Funcionamento detalhado:

```cpp
Cenario(string& texto, size_t indice_inicial) {
    size_t pos = indice_inicial;
    nome = proxima_tag_conteudo(texto, pos, "nome");
    altura = stoi(proxima_tag_conteudo(texto, pos, "altura"));
    largura = stoi(proxima_tag_conteudo(texto, pos, "largura"));
    x = stoi(proxima_tag_conteudo(texto, pos, "x"));
    y = stoi(proxima_tag_conteudo(texto, pos, "y"));
    matriz = matriz_remove_espacos(proxima_tag_conteudo(texto, pos, "matriz"));
    indice_final = pos;
}
```

#### Métodos auxiliares:

- `proxima_tag()`: Encontra a próxima tag no texto (ex: <altura>)
- `proximo_conteudo()`: Extrai o valor entre tags (ex: 10 em <altura>10</altura>)
- `matriz_remove_espacos()`: Filtra apenas '0's e '1's da matriz, removendo quebras de linha e espaços

#### Exemplo de fl uxo:

- 1. Encontra <nome>, extrai "cenario-01"
- 2. Encontra <altura>, converte "5" para inteiro
- 3. Continua até extrair toda a matriz binária

### 2. Função validar_xml()

#### Algoritmo:

``` cpp 
stack<string> tag_stack;
while (pos < texto.length()) {
    if (texto[pos] == '<') {
        // Extrai nome da tag
        if (texto[pos+1] == '/') {
            // Tag de fechamento
            if (tag_stack.empty() || tag_stack.top() != tag_name) {
                return false; // Erro!
            }
            tag_stack.pop();
        } else {
            // Tag de abertura
            tag_stack.push(tag_name);
        }
    }
    pos++;
}
return tag_stack.empty(); // True se todas tags foram fechadas
```

#### Casos de teste:

- Válido: <cenario><nome>teste</nome></cenario>
- Inválido: <cenario><nome>teste</cenario></nome>
- Inválido: <cenario><nome>teste</nome>

### 3. Função calcular_area_limpa()

#### Passo a passo:

- 1. Conversão da matriz:
```cpp
for (i = 0; i < altura; i++)
for (j = 0; j < largura; j++)
matriz[i][j] = matriz_str[i*largura + j] - '0';
```

- 2. Inicialização do BFS:
```cpp
queue<pair<size_t, size_t>> fila;
fila.push({x, y});
visitados[x][y] = true;
```

- 3. Expansão da área:
```cpp
while (!fila.empty()) {
auto [x, y] = fila.front(); fila.pop();
area++;

    // Verifica 4 vizinhos
    for (int i = 0; i < 4; i++) {
        size_t nx = x + dx[i], ny = y + dy[i];
        if (nx < altura && ny < largura 
            && matriz[nx][ny] == 1 
            && !visitados[nx][ny]) {
            fila.push({nx, ny});
            visitados[nx][ny] = true;
        }
    }
}
```

#### Exemplo visual:
```
Matriz:     Visitados:
1 1 0       1 1 0
1 0 1       1 0 0
0 1 0       0 0 0
```

> Área limpa = 3 (partindo de (0,0))

### 4. Função main()

#### Fluxo principal:

```cpp
int main() {
    // 1. Leitura do arquivo
    ifstream filexml(filename);
    string texto((istreambuf_iterator<char>(filexml)), {});

    // 2. Validação XML
    if (!validar_xml(texto)) {
        cout << "erro" << endl;
        return 0;
    }

    // 3. Processamento dos cenários
    vector<Cenario> cenarios;
    size_t pos = 0;
    while (pos < texto.length()) {
        size_t inicio = texto.find("<cenario>", pos);
        if (inicio == string::npos) break;
        
        Cenario c(texto, inicio);
        cenarios.push_back(c);
        pos = c.indice_final;
    }

    // 4. Cálculo e saída
    for (auto& c : cenarios) {
        cout << c.nome << " " << calcular_area_limpa(c) << endl;
    }
}
```
#### Pontos-chave:

1. Lê todo o arquivo para uma string
2. Valida estrutura antes de processar
3. Cria objetos Cenario para cada bloco <cenario>...</cenario>
4. Para cada cenário, calcula área e imprime no formato "nome área"

#### Diagrama de Sequência (Simplificado)
```c
main() → validar_xml() → Cenario() → calcular_area_limpa()
↑                ↑
(pilha)          (fila BFS)
```
Esta implementação combina eficientemente processamento de texto (XML), estruturas de dados (pilha/fila) e algoritmos de grafos (BFS) para resolver o problema proposto.

## Algoritmo BFS (Breadth-First Search)

1. Conceito Fundamental

O BFS (Busca em Largura) é um algoritmo para percorrer ou buscar elementos em estruturas de dados como grafos e árvores. Ele explora todos os vértices vizinhos na profundidade atual antes de avançar para os vértices no próximo nível de profundidade.

2. Aplicação no Projeto

No contexto do robô aspirador, usamos BFS para:

Calcular a área conexa: Determinar todos os pontos alcançáveis a partir da posição inicial
Vizinhança-4: Considerando apenas movimentos para cima, baixo, esquerda e direita
3. Implementação Detalhada

```cpp
size_t calcular_area_limpa(const Cenario& cenario) {
// 1. Pré-processamento
vector<vector<int>> matriz(cenario.altura, vector<int>(cenario.largura));
// ... conversão da matriz string para 2D ...

    // 2. Inicialização
    queue<pair<size_t, size_t>> fila;
    vector<vector<bool>> visitado(cenario.altura, vector<bool>(cenario.largura, false));
    
    // 3. Posição inicial
    fila.push({cenario.x, cenario.y});
    visitado[cenario.x][cenario.y] = true;
    size_t area = 0;

    // 4. Direções possíveis (cima, baixo, esquerda, direita)
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    // 5. Núcleo do BFS
    while (!fila.empty()) {
        auto [x, y] = fila.front();
        fila.pop();
        area++;

        // 6. Explorar vizinhos
        for (int i = 0; i < 4; i++) {
            size_t nx = x + dx[i];
            size_t ny = y + dy[i];

            // 7. Verificar se o vizinho é válido
            if (nx < cenario.altura && ny < cenario.largura && 
                !visitado[nx][ny] && matriz[nx][ny] == 1) {
                visitado[nx][ny] = true;
                fila.push({nx, ny});
            }
        }
    }
    return area;
}
```
4. Passo a Passo do Algoritmo

- 1. Inicialização:
   - Cria uma fila vazia
   - Matriz de visitados inicializada como falsa
   - Adiciona a posição inicial à fila
- 2. Processamento:
   - Remove o primeiro elemento da fila
   - Incrementa o contador de área
   - Para cada vizinho (cima, baixo, esquerda, direita):
     - Verifica se está dentro dos limites da matriz
     - Verifica se não foi visitado
     - Verifica se é área limpa (valor 1)
     - Se válido, marca como visitado e adiciona à fila
- 3. Terminação:
     Quando a fila estiver vazia, retorna a área total
5. Complexidade

Tempo: O(V + E), onde V é o número de vértices (altura × largura) e E o número de arestas (até 4 por vértice)
Espaço: O(V) para armazenar a fila e a matriz de visitados
6. Exemplo Visual

``` 
Para a matriz:

1 1 0
1 0 1
0 1 0
```
Partindo de (0,0):

**Passo 1**: Visita (0,0), área=1

**Passo 2**: Visita (0,1) e (1,0), área=3

**Passo 3**: Tenta visitar vizinhos de (0,1) e (1,0)

**Resultado**: Área total = 3

7. Por que BFS e não DFS?

   - Vantagens do BFS:
     - Encontra o caminho mais curto em grafos não ponderados
     - Mais eficiente para áreas grandes e esparsas
     - Naturalmente adequado para problemas de vizinhança em grids
   - DFS seria menos eficiente:
     - Poderia causar maior uso de stack (risco de estouro para matrizes grandes)
     - Não garante encontrar o caminho mais curto primeiro
8. Otimizações Implementadas

- 1. Matriz de visitados: Evita reprocessamento
- 2. Checagem de limites: Antes de cada acesso à matriz
- 3. Conversão eficiente: Da matriz string para representação 2D
- 4. Vizinhança-4: Processada em ordem fixa (cima, baixo, esquerda, direita)

Esta implementação de BFS é particularmente eficaz para o problema de determinação de áreas conexas em matrizes binárias, garantindo que todos os pontos alcançáveis sejam contabilizados exatamente uma vez.



# Author

| [<img src="https://avatars.githubusercontent.com/u/79289647?v=4" width=115><br><sub>Carlos Hayden</sub>](https://github.com/JunhaumHayden) |
| :---: |




### Arquivo de saída: vpl_evaluate.cases:
```bash
case=1
        input=cenarios1.xml
        output=cenario-01 25
        cenario-02 107
        cenario-03 28
        cenario-04 0
        cenario-05 22
        cenario-06 174

        case=2
        input=cenarios2.xml
        output=erro

        case=3
        input=cenarios3.xml
        output=erro

        case=4
        input=cenarios4.xml
        output=P1020583 1604
        P1020590 2132
        P1020592 29
        P1020595 444
        P1020597 2056
        P1020598 4
        P1020611 0
        P1020617 0
        P1020619 25
        P1020623 1442
        P1020626 35
        P1020629 2434
        P1020631 484
        P1020635 0
        P1020640 2437
        P1020643 1107
        P1020645 3208
        P1020651 4333
        P1020663 99
        P1020664 3135
        P1020665 0
        P1020670 14
        P1020689 0
        P1020691 7
        P1020692 3
        P1020693 3
        P1020695 0
        P1020696 28
        P1020697 2887
        P1020698 3978
        P1020699 3765
        P1020700 3199
        P1020701 26
        P1020706 3384
        P1020712 0
        P1020716 4798
        P1020723 2098
        P1020724 1154
        P1020725 610
        P1020726 3390
        P1020730 0
        P1020739 102
        P1020740 22
        P1020757 30
        P1020766 0
        P1020767 0
        P1020769 0
        P1020770 8
        P1020771 0
        P1020772 0
        P1020773 0
        P1020776 2
        P1020777 0
        P1020811 0
        P1020812 0
        P1020813 0
        P1020822 0
        P1020823 2276
        P1030104 5
        P1030105 0
        P1030106 0
        P1030107 0
        P1030108 0
        P1030109 0
        P1030111 2
        P1030112 7
        P1030113 0
        P1030114 0
        P1030115 549
        P1030116 0
        P1030117 0
        P1030118 3
        P1030121 7
        P1030123 544
        P1030124 0
        P1030126 378
        P1030127 4396
        P1030128 2558
        P1030129 0
        P1030134 0
        P1030135 2877
        P1030138 3368
        P1030141 2871
        P1030142 0
        P1030144 0
        P1030145 616
        P1030146 0
        P1030149 0
        P1030150 304
        P1030152 0
        P1030153 0
        P1030154 0
        P1030156 1448
        P1030157 0
        P1030158 0
        P1030159 0
        P1030162 971
        P1030163 0
        P1030164 28
        P1030165 0
        P1030173 11

        case=5
        input=cenarios5.xml
        output=erro

        case=6
        input=cenarios6.xml
        output=3_nouvel-obs_hbhnr300_constructedPdf_Nouvelobs2402PDF.clean.png 174
```