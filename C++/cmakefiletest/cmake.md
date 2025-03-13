# O que é o CMake?

O `CMake` é uma ferramenta de automação de compilação multi-plataforma que gera arquivos de configuração para diferentes sistemas de compilação, como Makefiles (Linux/macOS), Ninja, Visual Studio e outros. Ele não é um compilador, mas um gerador de scripts de build que facilita a criação, organização e portabilidade de projetos C/C++.

## Por que usar o CMake?

- `Independência de plataforma` → Funciona no Windows, macOS e Linux.
- `Suporte a vários compiladores` → Pode usar GCC, Clang, MSVC, etc.
- `Facilita projetos grandes` → Organiza dependências e módulos.
- `Integração com IDEs` → Compatível com VS Code, CLion, Qt Creator, etc.

## Principais Componentes do CMake

1. `CMakeLists.txt`
O arquivo `CMakeLists.txt` é onde você define o projeto, os arquivos-fonte, bibliotecas e configurações. Ele é o coração do CMake.

### Exemplo básico:
```txt
cmake_minimum_required(VERSION 3.10)  # Define a versão mínima do CMake
project(MeuProjeto)                   # Nome do projeto

add_executable(meu_programa main.cpp)  # Gera um executável a partir do main.cpp
```

2. Comandos Básicos do CMake
Configurar o projeto (gera arquivos de build)
```bash
cmake -S . -B build
```
> `-S .` → Fonte no diretório atual
> `-B build` → Salva os arquivos de build na pasta build

Compilar o projeto (gera o binário)
```bsah
cmake --build build
```
Executar o programa gerado
```bsah
./build/meu_programa
```
Exemplo Completo

Estrutura do Projeto
``` bash
MeuProjeto/
│── src/
│   ├── main.cpp
│── CMakeLists.txt
│── build/  (gerado pelo CMake)
``` 
Código (main.cpp)

```c
#include <iostream>
int main() {
    std::cout << "Olá, CMake!" << std::endl;
    return 0;
}
```

Arquivo CMakeLists.txt
```txt
cmake_minimum_required(VERSION 3.10)
project(MeuProjeto)

add_executable(meu_programa src/main.cpp)
```

### Passos para Compilar e Executar
```bash
mkdir build && cd build
cmake ..
make
./meu_programa
```
Saída esperada:
```bash
Olá, CMake!
```
## Resumo

O `CMake` simplifica a compilação de projetos C/C++ em múltiplos sistemas.
O CMakeLists.txt define o projeto e suas configurações.
Usamos cmake para gerar os arquivos de build e make (ou ninja) para compilar.
Funciona bem com VS Code, CLion e outras IDEs.
