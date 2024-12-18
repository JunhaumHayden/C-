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
```c
clang --version
```

Se o retorno for algo semelhante a:
```c
zsh: command not found: clang
```

então use o seguinte comando para instalar as ferramentas de linha de comando do Xcode (aprove quaisquer solicitações que ele fizer, a instalação completa pode demorar um pouco):
```c
xcode-select --install
```
Caso contrário, se você viu uma mensagem semelhante:
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