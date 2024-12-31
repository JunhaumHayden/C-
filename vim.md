# Usando o vim
## Modos do Vim
O Vim tem alguns modos:

- Normal mode: para se movimentar pelo texto
- Insert mode: para escrever no texto
- Visual mode: para selecionar parte do texto
- Command mode: para dar algum comando ao Vim
### Comandos básicos no modo normal
- `esc`: sair do modo atual e ir para o modo de comando
- `j`: mover o cursor para baixo
- `k`: mover o cursor para cima
- `h`: mover o cursor para a esquerda
- `l`: mover o cursor para a direita
- `ctrl i`: entrar no modo de edição no caracter em que está
- `shift a`: entrar no modo de edição no final da linha
- `shift o`: entra no modo de edição em uma nova linha abaixo da atual
- `gg`: (2gg para ir para a linha numero 2)ir para o início do arquivo
- `shift g`: ir para o final do arquivo
- `w`: pular uma palavra para frente
- `b`: pular uma palavra para trás
- `ctrl ]`: pular um bloco de código para baixo
- `ctrl [`: pular um bloco de código para cima
- `y`: copiar código
- `c`: recortar código
- `p`: colar código um caractere depois do atual
- `x`: deletar caractere
- `dd`: deletar linha
- `ctrl u`: desfazer
- `ctrl r`: refazer

### Comandos no modo de comando
Entramos nesse modo depois de dar um `esc`. Perceba que aqui nós precisamos digitar dois pontos para dar o comando e dar enter no final. Aqui os comandos aparecem sendo digitados no canto inferior da tela (lá no finzinho).

- `:q`: sair do arquivo atual
- `:q!`: saída forçada do arquivo atual
- `:w`: salvar
- `:wq`: salvar e sair
### Comandos no modo visual
Com o `v` entramos no visual mode, e com os comandos do modo normal movemos o cursor para que selecione o texto que queremos. Ficará um VISUAL no canto inferior.

`x:` deleta o que está selecionado
`y`: copia o que está selecionado
`s`: entra no modo de edição substituindo o que tinha antes
`c`: recorta o código selecionado
Para copiar o código selecionado em algum lugar, dê um `esc` para voltar ao modo normal e depois um p (paste) no local desejado.

# Configurando o VIM

O arquivo `.vimrc` é usado para configurar e personalizar o editor de texto Vim, permitindo ajustar o comportamento, a aparência e a usabilidade do editor para atender às suas preferências. Abaixo, explico como configurá-lo para tornar o Vim mais amigável e com uma interface mais moderna.

## 1. Localizar ou Criar o Arquivo .vimrc
No macOS, o arquivo `.vimrc` deve ser criado no diretório home do usuário, que é o local padrão onde o Vim procura por suas configurações pessoais. O caminho completo seria:
```bash
~/.vimrc
```
Aqui está um passo a passo para criar ou editar o arquivo `.vimrc`:

- 1. Localizar o Diretório Home
O diretório home do usuário no macOS é geralmente `/Users/seu_nome`, mas você pode usar o atalho `~` para se referir a ele diretamente. Para verificar, digite no terminal:
```bash
echo $HOME
```

- 2. Criar ou Editar o Arquivo `.vimrc`
Verificar se o arquivo já existe:
```bash
ls -a ~ | grep .vimrc
```
Criar o arquivo, se ele não existir:
```bash
touch ~/.vimrc
```
Abrir o arquivo para edição: Você pode usar o próprio Vim para editar:
```bash
vim ~/.vimrc
```
Ou, se preferir um editor gráfico, como o Visual Studio Code:
```bash
code ~/.vimrc
```
- 3. Adicionar Configurações ao `.vimrc`
No arquivo aberto, adicione as configurações que desejar. Por exemplo:
```bash
set number              " Exibe números nas linhas
syntax on               " Habilita o destaque de sintaxe
set tabstop=4           " Define o tamanho de uma tabulação
set expandtab           " Converte tabs em espaços
set background=dark     " Fundo escuro
colorscheme desert      " Define um tema de cores
```

Salve e feche o arquivo após editar.

- 4. Testar o `.vimrc`
Para verificar se as configurações foram aplicadas, abra qualquer arquivo com o Vim:
```bash
vim arquivo.txt

```
Se tudo estiver correto, você verá as configurações aplicadas (como números de linha ou o tema).

### Dica Extra
> Caso precise usar configurações diferentes para projetos específicos, você pode criar arquivos `.vimrc` locais nos diretórios de projeto e carregar essas configurações com:
> set exrc
> Isso permite que o Vim leia arquivos `.vimrc` no diretório atual.

## 2. Configurações Básicas para Melhorar a Usabilidade
Adicione as seguintes linhas ao arquivo `.vimrc` usando um editor de texto (como o próprio Vim ou outro editor):
```bash
" === Geral ===
set number              " Exibe números das linhas
set relativenumber      " Exibe números relativos
set cursorline          " Destaca a linha atual
set mouse=a             " Habilita o uso do mouse
set clipboard=unnamed   " Permite copiar/colar com o sistema

" === Aparência ===
set background=dark     " Define o fundo como escuro (ou light para claro)
syntax on               " Habilita o destaque de sintaxe
set termguicolors       " Ativa suporte a cores no terminal

" === Indentação ===
set autoindent          " Indentação automática
set tabstop=4           " Define o tamanho de uma tabulação
set shiftwidth=4        " Controla a indentação automática
set expandtab           " Converte tabs em espaços

" === Pesquisa ===
set hlsearch            " Destaca resultados da busca
set incsearch           " Mostra resultados enquanto você digita
set ignorecase          " Pesquisa sem diferenciar maiúsculas/minúsculas
set smartcase           " Diferencia caso uma letra maiúscula seja usada

" === Melhorias de Navegação ===
set scrolloff=5         " Mantém 5 linhas acima/abaixo ao rolar
set wildmenu            " Torna a busca de comandos mais amigável
set showcmd             " Mostra comandos parciais na barra inferior
set splitbelow          " Abre novos splits horizontalmente abaixo
set splitright          " Abre novos splits verticalmente à direita
```

## 3. Plugins para Tornar o Vim Mais Moderno
Instalar um Gerenciador de Plugins (como vim-plug):

- 1. Baixe e instale o vim-plug:
```bash
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```
- 2. Adicione o seguinte bloco ao início do `.vimrc` para gerenciar plugins:
```bash
call plug#begin('~/.vim/plugged')

" Exemplos de plugins úteis:
Plug 'preservim/nerdtree'          " Navegador de arquivos
Plug 'vim-airline/vim-airline'    " Barra de status moderna
Plug 'scrooloose/syntastic'       " Verificador de sintaxe
Plug 'junegunn/fzf', { 'do': './install --all' } " Busca avançada
Plug 'morhetz/gruvbox'            " Tema popular

call plug#end()
```
- 3. Salve o arquivo e abra o Vim. Execute o comando para instalar os plugins:
```bash
:PlugInstall

```
### 4. Usando os Plugins
`NERDTree`: Use :NERDTreeToggle para abrir/fechar o navegador de arquivos.
`vim-airline`: Exibe uma barra de status estilizada.
`Syntastic`: Mostra erros de sintaxe enquanto você edita.
`fzf`: Permite buscar arquivos de forma interativa com :Files.
### 5. Aplicando um Tema Personalizado
Se você instalou o plugin gruvbox, adicione o seguinte ao seu `.vimrc` para ativá-lo:
```bash
colorscheme gruvbox
set background=dark
```
### 6. Dica Extra: Ativar Auto-Save
Para salvar automaticamente o arquivo ao sair do modo de edição, adicione:
```bash
autocmd BufLeave * silent! w
```
### 7. Testar as Configurações
Depois de configurar o `.vimrc`, reinicie o Vim para aplicar as mudanças:
```bash
vim arquivo.c
```
Agora o Vim estará mais intuitivo e com uma aparência moderna. 


## O erro E492: Not an editor command: PlugInstall 
Ocorre porque o Vim ainda não está configurado para usar o gerenciador de plugins vim-plug ou ele não foi instalado corretamente. Vamos resolver isso passo a passo:

- 1. Certifique-se de que o vim-plug está instalado
O comando :PlugInstall faz parte do vim-plug, então ele precisa estar instalado antes de ser usado.

### Instale o vim-plug

Execute este comando no terminal para baixar o script do vim-plug e colocá-lo no local correto:
```bash
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```
Este comando:

1. Cria o diretório `~/.vim/autoload` se ele não existir.
Baixa o script plug.vim (o gerenciador de plugins) e o coloca no diretório `~/.vim/autoload`.
2. Verifique o arquivo `.vimrc`
Certifique-se de que o conteúdo do seu `.vimrc` inclua a configuração do vim-plug. Deve haver um bloco como este no início do arquivo:
```bash
call plug#begin('~/.vim/plugged')

" Aqui você adiciona os plugins que deseja instalar
Plug 'preservim/nerdtree'          " Navegador de arquivos
Plug 'vim-airline/vim-airline'    " Barra de status estilizada
Plug 'morhetz/gruvbox'            " Tema de cores Gruvbox

call plug#end()
```
3. Execute o comando `:PlugInstall` novamente
Após salvar o arquivo `.vimrc`, abra o Vim e execute:
```bash
:PlugInstall
```
Isso deve iniciar o processo de download e instalação dos plugins listados no bloco Plug do arquivo `.vimrc`.

4. Verifique se você está usando o Vim, e não o Vi
No macOS, o comando vim pode, por padrão, estar apontando para o Vi, uma versão mais básica do editor que não suporta recursos modernos como o vim-plug. Para garantir que você está usando o Vim, digite:
```bash
vim --version
```
Verifique se aparece algo como VIM - Vi IMproved.
Se não, você pode instalar uma versão completa do Vim usando o Homebrew:
```bash
brew install vim
```
Certifique-se de usar o Vim recém-instalado em vez da versão padrão do sistema.

5. Problemas Comuns
O vim-plug não está sendo carregado: Certifique-se de que o arquivo `~/.vim/autoload/plug.vim` existe.
```bash
ls ~/.vim/autoload/plug.vim
```
Se ele não existir, repita o comando de instalação do vim-plug.
Erro ao baixar plugins: Isso pode ocorrer devido a problemas de conexão. Certifique-se de que sua internet está funcionando corretamente.

## Comandos do Vundle e do plugin NERDTree
Para instalar os plugins que você definiu no seu `.vimrc` entre no Vim e, no modo de comando, digite:


```bash
:PluginInstall
```

É só dar `esc`, depois `:q` e `enter` para sair. Para desinstalar um plugin delete a linha no `.vimrc` e depois faça o mesmo esquema só que com `:PluginClean`.

Para acessar a árvore de comandos que eu instalei, vá para o modo de comando e digite:
```bash
:NERDTree
```

Você pode navegar na NERDTree como no normal mode. Para abrir uma pasta pressione `o`, para fechá-la, pressione novamente.

Para abrir um arquivo do lado pressione o no arquivo. Para abrir outro arquivo na vertical, dividindo a tela com um arquivo já aberto, pressione `i`.

Para rodar entre os arquivos abertos e a árvore de arquivos pressione `ctrl w` e mais uma das teclas principais de navegação (`h`, `j`, `k`, `l`).

