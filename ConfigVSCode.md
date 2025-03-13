Usando C++ no VSCode - MacOS

Parabéns por ter um Mac! Vocês definitivamente têm a configuração mais fácil dos três (na verdade, dois) sistemas operacionais para os quais fornecemos tutoriais.

Por que vocês têm isso tão fácil? Bem, o MacOS é baseado na família Unix OS , então você já tem acesso total às ferramentas de linha de comando do Linux - usuários do Windows não têm esse luxo. Grande parte do tutorial do Windows é gasto apenas configurando o sistema operacional Windows com um "psuedo ambiente Linux", chamado Windows Subsystem for Linux . Vocês têm tudo o que precisamos reunido em um único comando de terminal, fornecido pelos desenvolvedores da Apple.

Requisitos
Verificar as configuraçoes na documentação oficial na página da [Microsoft](https://code.visualstudio.com/docs/cpp/config-clang-mac).

O [tutorial](https://cse232--msu-github-io.translate.goog/CSE232/vscode_setup/macos.html?_x_tr_sl=en&_x_tr_tl=pt&_x_tr_hl=pt&_x_tr_pto=tc) a seguir pressupõe que você esteja executando o MacOS versão 10.13 (High Sierra) ou posterior, mas é possível que este tutorial ainda funcione em versões mais antigas - simplesmente não temos como testar. Você pode verificar sua versão do MacOS clicando no logotipo da Apple no canto superior esquerdo e selecionando “Sobre este Mac”.

Recomendo que você reserve um tempo para atualizar seu sistema agora se sua versão for inferior à 10.13.

Obtendo um compilador

A maneira mais fácil de obter um compilador C++ é usar as ferramentas Xcode fornecidas pela Apple, que vêm empacotadas com um compilador chamado “Clang”. Você pode já ter isso instalado, se você estava trabalhando com recursos de terminal antes desta aula.

Para testar se você tem o Clang instalado, abra o Terminal e use o seguinte comando:

> Neste Mac há um alias para o GNU Compiler Collection (GCC)

```bash
clang --version
```

Se o retorno for algo semelhante a:
```bash
zsh: command not found: clang
```

então use o seguinte comando para instalar as ferramentas de linha de comando do Xcode (aprove quaisquer solicitações que ele fizer, a instalação completa pode demorar um pouco):
```bash
xcode-select --install
```
Caso contrário, se você viu uma mensagem semelhante:

> Mensagem retornada por esse mac em 12/03/2025

```bash
(base) cliente-150-162-231-120:c_codes hayden$ clang --version
Apple clang version 16.0.0 (clang-1600.0.26.6)
Target: arm64-apple-darwin24.3.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```
ou

```bash
Apple clang version 11.0.3 (clang-1103.0.32.59)
Target: x86_64-apple-darwin20.2.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```
Então está tudo pronto!

Após a instalação, recomendo executar o `clang --version` comando novamente para ver se obtém a saída acima.

Na maioria das nossas aulas e laboratórios, faremos referência a um compilador diferente, `g++`, já que `g++` é de longe o compilador C++ mais popular. O MacOS atribui o nome g++como um alias para `clang++` depois de instalar as ferramentas de linha de comando do Xcode, que você pode ver usando:
```bash
g++ --version
```
Você provavelmente não usará o comando `clang` ou `clang++` novamente a partir deste ponto.

## Preparando VSCode para C++

Baixe e instale a versão estável do Visual Studio Code aqui.

Recomendo usar uma pasta existente ou criar uma nova pasta dedicada ao conteúdo do CSE 232. Essa pasta pode estar em qualquer lugar.

Abra o VSCode, e você deverá ver uma página de boas-vindas. Perto do canto superior esquerdo da janela, você deverá ver um ícone de arquivos empilhados uns sobre os outros. Clique neste ícone para abrir o explorador de arquivos integrado, conforme mostrado aqui:

<img src="https://cse232-msu.github.io/CSE232/assets/images/vscode_installation_macos/1.png">


Clique no botão “Abrir pasta” e navegue no explorador até a pasta CSE 232 que você criou anteriormente.

O topo da barra lateral agora deve exibir o nome da pasta que você abriu, que provavelmente está vazia (a menos que você tenha arquivos lá). Você pode clicar com o botão direito dentro do painel para muitas das opções que você normalmente teria no Finder:

<img src="https://cse232-msu.github.io/CSE232/assets/images/vscode_installation_macos/2.png">


Clique no ícone de quatro quadrados na barra lateral esquerda para abrir o Extensions Marketplace. Procure por “C/C++” e você deverá encontrar uma extensão de mesmo nome, desenvolvida pela Microsoft:

<img src="https://cse232-msu.github.io/CSE232/assets/images/vscode_installation_macos/3.png">


Vá em frente e instale a extensão assim que encontrá-la.

Volte para o explorador de arquivos integrado após instalar a extensão e crie um arquivo chamado `“helloworld.cpp”`. Digite/copie e cole o seguinte código no seu arquivo `helloworld.cpp`:
```c
#include <iostream>

int main()
{
    std::cout << "Hello world" << std::endl;
}
```

No seu teclado, use a combinação de teclas: CTRL + ` (este é o caractere backtick, ele deve estar à esquerda da tecla 1 na maioria dos teclados). Isso alterna o terminal integrado do VSCode:

<img src="https://cse232-msu.github.io/CSE232/assets/images/vscode_installation_macos/4.png">


O terminal é onde você compila seu código-fonte C++. A maioria dos laboratórios terá seções curtas dedicadas a aprender mais sobre o terminal, pois você precisará estar familiarizado com ele para navegação geral e cursos futuros. Salve seu arquivo helloworld.cpp se ainda não o fez (CMD + S) e, para compilar nosso adorável programa, digite o seguinte comando no terminal:

```bash
g++ helloworld.cpp -Wall -std=c++20
```

Isso produz um arquivo chamado “a.out” – você deve vê-lo aparecer no explorador de arquivos. Para executar seu programa compilado, digite no terminal:
```bash
./a.out
```

E então você deverá ver “Olá, mundo” exibido no console!

<img src="https://cse232-msu.github.io/CSE232/assets/images/vscode_installation_macos/5.png">


Parabéns! Você acabou de fazer seu primeiro programa em C++.

É importante notar que você deve compilar seu programa e executar a.out toda vez que quiser testar seu código . Você digitará esses dois comandos centenas de vezes neste curso. Mantenha-os em suas anotações ou memorize-os (você provavelmente os memorizará em poucos dias de prática).

Se você configurar o depurador (a seção abaixo), você pode compilar e executar com um único clique do mouse. Falaremos mais sobre o comando de compilação e o que você pode fazer com ele, então é melhor estar familiarizado com ambos.

> Nota : Eu recomendo fortemente que você configure o depurador agora e o use a seu favor durante todo o curso. Ele é incrivelmente útil quando você pega o jeito.

## Depuração de C++ no VSCode

Você deve estar familiarizado com um depurador IDE da sua aula de programação anterior (CSE 231 ou um pré-requisito equivalente). Se não estiver, leia este tutorial (ele é em Python, mas os mesmos princípios básicos se aplicam).

Volte para o Extensions Marketplace para encontrar e instalar a extensão “CodeLLDB” feita por Vadim Chugunov. Deve ser a única extensão que aparece.

Para depurar o código C++, precisamos dar ao VSCode algumas informações extras sobre como queremos depurar. Fornecemos algumas configurações de depuração para você que podem ser instaladas pelo terminal.

Execute os seguintes comandos um por um para instalar nossos arquivos de configuração recomendados:
``` bash
mkdir .vscode
cd .vscode
curl --remote-name-all https://raw.githubusercontent.com/CSE232-MSU/CSE232-VSCCONF/main/macos/{launch.json,tasks.json,c_cpp_properties.json}
cd ..
```

<img src="https://cse232-msu.github.io/CSE232/assets/images/vscode_installation_macos/6.png">

Agora você deve ter uma pasta chamada “.vscode” contendo três arquivos .json, se expandida no painel do explorador.

A pasta .vscode é uma pasta especial que o VSCode pesquisará ao executar determinadas tarefas. A pasta .vscode que você acabou de criar ao fazer esse processo é exclusiva do diretório em que você está atualmente, que é sua pasta CSE 232 no momento . Mover o VSCode para um novo diretório significa que você não terá mais as mesmas configurações. Você pode consultar o processo que acabamos de executar para instalar esses arquivos de configuração aqui , se quiser mover seu espaço de trabalho para uma pasta diferente (isso também está na página inicial de configuração). Você também pode simplesmente copiar essa pasta .vscode com você, se mover seu espaço de trabalho para outro lugar.

Substitua o conteúdo do arquivo helloworld.cpp por esta versão mais complexa:
```c
#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<std::string> msg{"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (std::string const &word : msg)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}
```
Você deve ver um ícone na barra lateral esquerda que parece um botão de play com um bug nele – este é o menu do depurador, vá em frente e abra-o. Como a maioria dos depuradores IDE, ele tem um menu mostrando suas variáveis ​​atualmente ativas, variáveis ​​monitoradas, pilha de chamadas e pontos de interrupção atualmente ativos.

<img src="https://cse232-msu.github.io/CSE232/assets/images/vscode_installation_macos/7.png">


Defina um ponto de interrupção na primeira linha da main()função clicando levemente à esquerda do número da linha; você deve ver um ponto vermelho aparecer. Então, execute o depurador pressionando o botão verde play no canto superior esquerdo.

<img src="https://cse232-msu.github.io/CSE232/assets/images/vscode_installation_macos/8.png">


Seu terminal deve ser preenchido com comandos que foram executados automaticamente pela configuração .vscode que eu fiz você instalar. Se sua interface VSCode se parece com a minha na captura de tela acima, então tudo está funcionando corretamente. Parabéns!

A linha destacada em amarelo mostra a próxima linha a ser executada, como você provavelmente pode imaginar.

No topo está o Painel de Controle do Depurador:

<img src="https://cse232-msu.github.io/CSE232/assets/images/debugger_controls.png">

Inclui suas opções de depuração padrão. Em ordem da esquerda para a direita:

* _Continuar_ - Executar o programa até o próximo ponto de interrupção
* _Step Over_ - Execute a linha destacada sem entrar na chamada de função (se presente)
* _Entrar_ - Execute a linha destacada e entre na chamada de função (se houver)
* _Sair_ - Sair de uma chamada de função (se estiver dentro de um corpo de função)
* _Reiniciar_ - Reexecutar o programa com o depurador ativo
* _Parar_ - Sair do depurador
  
O retângulo de pontos no lado esquerdo do painel é um ponto de arrasto, onde você pode clicar e segurar para arrastar o painel para outro lugar na janela.

Depois de definir a msgvariável por etapas, você pode clicar no menu suspenso dentro do menu do depurador para ver seu conteúdo indicado pelo índice.

<img src="https://cse232-msu.github.io/CSE232/assets/images/vscode_installation_macos/9.png">

As classes `std::vector`e `std::string` são coisas que você aprenderá mais tarde.

Seu depurador agora está pronto para uso! Incluídas com a pasta .vscode estão duas configurações de depuração: arquivo único e arquivo múltiplo. Você pode escolher a configuração clicando no menu suspenso ao lado do botão verde de reprodução. Você não precisará se preocupar com a compilação de vários arquivos por algumas semanas, ainda.

Incluído com a configuração que demos a você também está um arquivo c_cpp_properties.json, que usuários do Windows não terão por padrão. Por alguma razão, o VSCode usará uma versão desatualizada do C++ para lint seu código (ou seja, tentar detectar problemas antes da compilação) em sistemas MacOS. O arquivo `c_cpp_properties.json` fornecido forçará o linter a usar C++ 17.

## Escrevendo as primeiras linhas do makefile

O cerne do makefile consiste em regras definidas da seguinte maneira:

```bash
target : prerequisites
<TAB>recipe
```

O `target` é o nome da ação que você deseja executar ou usualmente o nome do arquivo que se queira produzir. Os `prerequisites` são arquivos que são usados como input para criar o `target`.

A `recipe` é a ação que o comando make realiza. A receita pode ter mais de um comando, na mesma linha ou várias. 
> ATENÇÃO: Você precisa usar o caractere `<TAB>` no começo de cada receita. O make interpreta como indicação de começo de comando a ser executado.

### Praticaremos com um exemplo: 
vamos supor que temos uma pasta com os seguintes arquivos: 
- `main.c`
- `helloWorld.h`
- `helloWorld.c`
- `makefile` 
  
  O GNU reconhece os seguintes nomes para makefile: `GNUmakefile`, `makefile` e `Makefile`. 
  > A ferramenta make é sensível a maiúsculas e minúsculas. 
  
  Você quer criar um binário chamado `printy`. Abaixo estão descritos os conteúdos dos arquivos respectivos, e iremos depois analisar o arquivo `makefile`.

Arquivo `main.c`
``` c
#include <stdio.h>
#include <stdlib.h>
#include "helloWorld.h"
 
int main(){
    helloWorld();
    return (0);
}
```

Arquivo `helloWorld.h`
```c
#ifndef _H_TESTE
#define _H_TESTE
 
void helloWorld(void);
 
#endif
```

Arquivo `helloWorld.c`

```c
#include <stdio.h>
#include <stdlib.h>
 
void helloWorld(void){
    printf("Hello World!\n");
}
```

Arquivo `makefile`

``` bash
# My first makefile
 
all: printy
 
printy: main.o helloWorld.o
    gcc -o printy main.o helloWorld.o
 
main.o: main.c helloWorld.h
    gcc -o main.o main.c -c -W -Wall -ansi -pedantic
 
helloWorld.o: helloWorld.c helloWorld.h
    gcc -o helloWorld.o helloWorld.c -c -W -Wall -ansi -pedantic
 
clean:
    rm -rf *.o *~ printy
```

No terminal, ao digitar “make all”, o utilitário make vai executar o target all que se encontra na linha 3 do arquivo makefile. O seu pré-requisito é o arquivo binário printy, porém sem receita para all. Ele vai para a linha 5 para construir printy, e acha os pré-requisitos main.o e helloWorld.o. Antes de partir para a linha 6, o make vai produzir os respectivos objetos.

Na linha 8, o make vê que o pré-requisito para main.o é a existência dos arquivos main.c e helloWorld.h no diretório atual. O make executa então a receita da linha 9. Primeiro invoca o compilador gcc. A parte -o main.o indica que o output, ou seja, o arquivo produzido será main.o. Para isso vai usar o arquivo main.c, que é o pré-requisito indicado na linha anterior. Os flags seguintes são configurações a serem passados ao compilador. O -Wall e o -pedantic são importantes para achar erro em seu código, mais detalhes você pode ler nesta página . Terminando de produzir o arquivo-objeto main.o, o make vai para as linhas 11 e 12 para produzir o arquivo-objeto helloWorld.o.

Tendo os dois arquivos-objetos em mãos, o make volta para a linha 6 para cumprir a receita do binário printy. O make invoca agora o linker do gcc, e avisa utilizando -o printy que o output será um binário no diretório atual chamado printy. E indica ao linker os dois arquivos objetos main.o e helloWorld.o. Uma vez produzido o binário printy, o make cumpre o pré-requisito do comando all da linha 3.

O comando clean da linha 14 somente será executado se você escrever no terminal make clean. Ele não possui pré-requisitos, e a receita manda excluir todos os arquivos com extensão .o, os de backup *~ e o arquivo binário printy no diretório atual.

Se você produziu o binário em seu computador, obviamente somente rodará em sua máquina. Se colocar o binário em um microcontrolador ou em uma raspberry não vai funcionar pois não foi um cross-compiling. Para executar o arquivo, basta digitar “./printy” em seu terminal.

Se você editar o arquivo helloWorld.c para imprimir outra mensagem e depois digitar o comando “make all”, somente este arquivo será recompilado e religado para formar o binário final.

1
2
3
4
5
6
$ make all
gcc -o main.o main.c -c -W -Wall -ansi -pedantic
gcc -o helloWorld.o helloWorld.c -c -W -Wall -ansi -pedantic
gcc -o printy main.o helloWorld.o
$ ./printy
Hello World!
Após editar o arquivo helloWorld.c:

1
2
3
4
5
$ make all
gcc -o helloWorld.o helloWorld.c -c -W -Wall -ansi -pedantic
gcc -o printy main.o helloWorld.o
$ ./printy
Embarcados' Article!
Makefile: Macros e variáveis automáticas

Você deve ter percebido que seria enfadonho cada vez que você tivesse que adicionar um novo arquivo. E somando a isso, não daria para reaproveitar o makefile para outros projetos, já que dificilmente teriam os mesmos nomes de arquivo.

Para resolver isso, utiliza-se de variáveis para facilitar as alterações e deixar o arquivo mais claro.

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
# My second makefile
 
# Name of the project
PROJ_NAME=printy
 
# .c files
C_SOURCE=$(wildcard *.c)
 
# .h files
H_SOURCE=$(wildcard *.h)
 
# Object files
OBJ=$(C_SOURCE:.c=.o)
 
# Compiler
CC=gcc
 
# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic
 
#
# Compilation and linking
#
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
    $(CC) -o $@ $^
 
%.o: %.c %.h
    $(CC) -o $@ $< $(CC_FLAGS)
 
main.o: main.c $(H_SOURCE)
    $(CC) -o $@ $< $(CC_FLAGS)
 
clean:
    rm -rf *.o $(PROJ_NAME) *~
Vemos, da linha 3 a 23, as variáveis para facilitar a customização do arquivo. Algumas vezes as variáveis são chamadas de macros. O uso das variáveis é igual a do shell script, e escreve-se $(VARIAVEL) ou ${VARIAVEL}, ambas formas estão corretas.

Nas linhas 7 e 10 utilizamos a função wildcard para pegar o nome de todos os arquivos com extensões .c e .h no diretório em que o makefile se encontra. Na variável C_SOURCE o nome de cada arquivo estará separado um do outro por um espaço. Na linha 10 copiamos todos os nomes da variável C_SOURCE para OBJ, mas com a substituição da extensão .c para .o. As funções patsubst e subst fazem funções parecidas, confiram a documentação oficial. Fazemos isso pois inicialmente os arquivos-objeto não existem, então a função wildcard seria ineficiente nesse caso.

Das linhas 19 a 22 utilizamos backlash ‘\’ para quebrar uma linha em várias, para tornar a leitura mais fácil. E atenção, para identar aqui, não utilize a tecla <TAB>, utilize espaços para que o make não confunda com comando de receita.

Das linhas 28 a 40, num primeiro momento, pode causar uma sensação de “Cruz credo! ”, mas dê uma pausa, vá beber agua, sente-se na cadeira, respire fundo e vamos analisar cada linha com calma.

O resultado das linhas 28 e 30 deste segundo exemplo é igual às linhas 3 e 5 do primeiro exemplo. Vamos pular por ora para a linha 33. Nessa linha interpreta-se que “o target com extensão .o terá um pré-requisito com extensões .c e .h com mesmo nome”. O símbolo ‘%’ pega o stem (tronco) do nome, que é utilizado de referência no pré-requisito. Por exemplo, se o target é helloWorld.o, o stem será helloWorld, consequentemente o pré-requisito será helloWorld.c e helloWorld.h. Perceba aqui que não usamos $(OBJ) como target, pois na expansão da macros surgiria os objetos main.o e helloWorld.o antes dos dois pontos, o que não seria correto.

A linha 34 desse segundo exemplo é relativo às linhas 9 e 12 do primeiro exemplo. Aqui a variável automática $@ pega o nome do target e $< pega o nome do primeiro pré-requisito. Então, $@ está para helloWorld.o e $< está para helloWorld.c. Perceba que as linhas 33 e 34 vão ser executadas para tantos outros arquivos .c e .h que existirem. Já as linhas 36 e 37 foi escrita para o caso especial do main.o, que não possui arquivo main.h e que depende de outros arquivos headers.

Voltando a linha 31, esta é referente à linha 6 do primeiro exemplo, e aqui utilizamos a variável automática $^ para listar todos os pré-requisitos do target. Neste caso, será expandido para todos os nomes que a variável OBJ contém.

Deixando organizado e elegante

Saber organizar, além de aumentar a produtividade, gera sincronia com a equipe com a qual você está trabalhando. Se você usa GitHub como seu cartão de visita, não seria interessante destacar a sua organização?

No seguinte exemplo, quis organizar da seguinte forma: na pasta do projeto, quero colocar um makefile e duas pastas, um para os códigos-fonte e outra para os objetos criados, cuja pasta vai ser criada pelo makefile. O binário deve ser criado na pasta do projeto. Entenda como fica a organização da pasta antes e depois da compilação:

Organização do projeto PrintyProject antes (a) e depois (b).
Figura 2 –  Organização do projeto PrintyProject antes (a) e depois (b).
O makefile seria escrito da seguinte maneira:

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
# My third makefile
 
# Name of the project
PROJ_NAME=printy
 
# .c files
C_SOURCE=$(wildcard ./source/*.c)
 
# .h files
H_SOURCE=$(wildcard ./source/*.h)
 
# Object files
OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))
 
# Compiler and linker
CC=gcc
 
# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic
 
# Command used at clean target
RM = rm -rf
 
#
# Compilation and linking
#
all: objFolder $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
    @ echo 'Building binary using GCC linker: $@'
    $(CC) $^ -o $@
    @ echo 'Finished building binary: $@'
    @ echo ' '
 
./objects/%.o: ./source/%.c ./source/%.h
    @ echo 'Building target using GCC compiler: $<'
    $(CC) $< $(CC_FLAGS) -o $@
    @ echo ' '
 
./objects/main.o: ./source/main.c $(H_SOURCE)
    @ echo 'Building target using GCC compiler: $<'
    $(CC) $< $(CC_FLAGS) -o $@
    @ echo ' '
 
objFolder:
    @ mkdir -p objects
 
clean:
    @ $(RM) ./objects/*.o $(PROJ_NAME) *~
    @ rmdir objects
 
.PHONY: all clean
Normalmente a ferramenta make imprime na tela do terminal cada linha da receita a ser executada. Para não poluir visualmente o terminal, colocamos no começo da linha o caractere ‘@’ para suprimir essas impressões. Em conjunto com o comando echo podemos deixar mensagens do que está sendo feito e colocar espaço entre uma compilação e outra na tela do terminal.

1
2
3
4
5
6
7
8
9
10
$ make all
Building target using GCC compiler: source/helloWorld.c
gcc source/helloWorld.c -c -W -Wall -ansi -pedantic -o objects/helloWorld.o
 
Building file using GCC compiler: source/main.c
gcc source/main.c -c -W -Wall -ansi -pedantic -o objects/main.o
 
Building binary using GCC linker: printy
gcc objects/helloWorld.o objects/main.o -o printy
Finished building binary: printy
Na linha 56 do arquivo makefile vemos o target .PHONY (“alvo falso”). Nela colocamos como pré-requisito os targets que não possuem arquivos de mesmo nome. Uma das razões para usar phony target é para não dar conflito com arquivos que sejam criados com mesmo nome (por exemplo, se existisse um arquivo chamado all.c ou clean.c).

Makefile: Considerações finais

Para escrever um makefile voltado para microcontroladores ARM, por exemplo, é necessário baixar o pacote GNU ARM Embedded Toolchain. Dentro do pacote você irá encontrar as ferramentas arm-none-eabi-gcc (compilador) e arm-none-eabi-ld (linker) e você pode indicar o caminho das ferramentas no makefile ou editar as variáveis de ambiente da sua máquina.

Se você não sabe exatamente como configurar para o seu microcontrolador, você pode conferir o arquivo makefile ou makedefs que vem junto à biblioteca que o fabricante te fornece. Aliás, toda documentação que o fabricante te fornece deve ser lido o máximo possível.

Outra possibilidade inusitada é conferir o terminal de sua IDE na hora da compilação. O IDE Eclipse produz automaticamente o makefile (na verdade são vários makefiles) e você também pode aprender fuçando esses arquivos.

Com a prática você pode automatizar e personalizar vários processos que você executa no dia a dia, e ainda repassar o arquivo aos seus colegas de trabalho através de repositórios git, criando um fluxo de trabalho mais dinâmico.

Confira também os documentos oficiais para saber quais outros potenciais o makefile possui. Lembre-se que não há fonte melhor que a documentação oficial!

