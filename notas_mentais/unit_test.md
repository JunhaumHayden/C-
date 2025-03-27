# Testes Unitário em C/C++
A opção é o cmocka, que é mais moderno.
## Exemplo de uso
Ver o [arquivo](../c/firstSteps/UntiTest/withCMocka.c)
## Instalaçao do cmocka

```bash
(base) hayden@cliente-150-162-230-48 UntiTest % brew install cmocka
==> Downloading https://formulae.brew.sh/api/formula.jws.json
==> Downloading https://formulae.brew.sh/api/cask.jws.json
==> Downloading https://ghcr.io/v2/homebrew/core/cmocka/manifests/1.1.7
######################################################################################################################################################################### 100.0%
==> Fetching cmocka
==> Downloading https://ghcr.io/v2/homebrew/core/cmocka/blobs/sha256:f59c0f3dcb57570a55bc13e96ac8d5b7710dd61289c9b75d1bf038d0866648ed
-=#=- #     #      #                                                                                                       ######################################################################################################################################################################### 100.0%
==> Pouring cmocka--1.1.7.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/cmocka/1.1.7: 18 files, 197.5KB
==> Running `brew cleanup cmocka`...
Disable this behaviour by setting HOMEBREW_NO_INSTALL_CLEANUP.
Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
(base) hayden@cliente-150-162-230-48 UntiTest % gcc -o test withCmoka.c -lcmocka && ./test

withCmoka.c:4:10: fatal error: 'cmocka.h' file not found
    4 | #include <cmocka.h>
      |          ^~~~~~~~~~
1 error generated.
(base) hayden@cliente-150-162-230-48 UntiTest % ls /opt/homebrew/Cellar/cmocka/1.1.7/include
cmocka.h        cmocka_pbc.h    cmockery
(base) hayden@cliente-150-162-230-48 UntiTest %                            
ls /opt/homebrew/Cellar/cmocka/1.1.7/lib

cmake                   libcmocka.0.dylib       pkgconfig
libcmocka.0.8.0.dylib   libcmocka.dylib
(base) hayden@cliente-150-162-230-48 UntiTest % gcc -o test withCmoka.c -I/opt/homebrew/include -L/opt/homebrew/lib -lcmocka && ./test

[==========] tests: Running 1 test(s).
[ RUN      ] test_soma
[       OK ] test_soma
[==========] tests: 1 test(s) run.
[  PASSED  ] 1 test(s).
(base) hayden@cliente-150-162-230-48 UntiTest % gcc -o test withCmoka.c -I/opt/homebrew/Cellar/cmocka/1.1.7/include -L/opt/homebrew/Cellar/cmocka/1.1.7/lib -lcmocka && ./test

[==========] tests: Running 1 test(s).
[ RUN      ] test_soma
[       OK ] test_soma
[==========] tests: 1 test(s) run.
[  PASSED  ] 1 test(s).
```

## Flags
- Explicação das opções:

- `-o test` → Define o nome do arquivo de saída como test. O executável gerado será chamado test em vez de a.out (padrão do GCC).
- `withCmoka.c` → Arquivo-fonte que contém o código C a ser compilado.
- `-I/opt/homebrew/include` → Diz ao compilador onde encontrar arquivos de cabeçalho (.h), no caso, os do **CMocka**.
O diretório /opt/homebrew/include contém os headers necessários, como cmocka.h.
- `-L/opt/homebrew/lib` → Diz ao compilador onde encontrar as bibliotecas (`.dylib` ou `.a`).
O diretório /opt/homebrew/lib contém a biblioteca **CMocka** (`libcmocka.dylib` ou `libcmocka.a`).
- `-lcmocka` → Linka (conecta) o código ao arquivo de biblioteca `libcmocka.dylib`.
- `-l` (minúsculo) adiciona automaticamente o prefixo lib e a extensão .dylib ou .a.

Se tudo estiver correto, o compilador não exibirá erros e criará um arquivo executável chamado test.

## 📌 Passo a Passo para configurar o VS Code

- 1️⃣ Abra as configurações do IntelliSense
1. No VS Code, abra a Command Palette (⇧⌘P no macOS ou Ctrl+Shift+P no Windows/Linux).
2. Digite e selecione: "C/C++: Edit Configurations (UI)".
3. Isso abrirá o arquivo c_cpp_properties.json.

- 2️⃣ Adicione os caminhos das bibliotecas
No arquivo c_cpp_properties.json, modifique ou adicione a configuração da seguinte forma:
```json
{
    "configurations": [
        {
            "name": "Mac",
            "includePath": [
                "${workspaceFolder}/**",
                "/opt/homebrew/include"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "macos-clang-arm64"
        }
    ],
    "version": 4
}
```

- 🔍 O que foi alterado?

`includePath` → Adicionamos "/opt/homebrew/include" para que o VS Code encontre o arquivo cmocka.h.
`compilerPath` → Define o compilador correto (clang no macOS).
`intelliSenseMode` → Ajustado para "macos-clang-arm64" (para M1/M2/M3).
- 3️⃣ Salve e reinicie o VS Code
Após editar o arquivo, salve (⌘S) e reinicie o VS Code.
O erro deve desaparecer e o IntelliSense reconhecerá o #include <cmocka.h> corretamente. ✅

## Para c++
### Google Test (gtest) - Mais Usado

O Google Test (ou gtest) é o framework mais popular para testes em C++. Ele é poderoso e fácil de usar.

##Exemplo de uso
ver o [arquivo](../c++/unitTest/withGoogleTest.cpp)
### ✅ Como Instalar

```bash
(base) hayden@jMac unitTest % brew install googletest
Warning: googletest 1.16.0 is already installed and up-to-date.
To reinstall 1.16.0, run:
  brew reinstall googletest
(base) hayden@jMac unitTest % g++ -o test withGoogleTest.cpp -lgtest -lgtest_main -pthread && ./test

ld: library 'gtest' not found
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
(base) hayden@jMac unitTest % brew info googletest

==> googletest: stable 1.16.0 (bottled), HEAD
Google Testing and Mocking Framework
https://google.github.io/googletest/
Installed
/opt/homebrew/Cellar/googletest/1.16.0 (76 files, 2.3MB) *
  Poured from bottle using the formulae.brew.sh API on 2025-03-18 at 19:27:09
From: https://github.com/Homebrew/homebrew-core/blob/HEAD/Formula/g/googletest.rb
License: BSD-3-Clause
==> Dependencies
Build: cmake ✔
==> Options
--HEAD
        Install HEAD version
==> Analytics
install: 4,668 (30 days), 13,407 (90 days), 40,987 (365 days)
install-on-request: 2,298 (30 days), 6,639 (90 days), 18,346 (365 days)
build-error: 5 (30 days)
(base) hayden@jMac unitTest % g++ -o test withGoogleTest.cpp \
    -I/opt/homebrew/Cellar/googletest/1.16.0/include \
    -L/opt/homebrew/Cellar/googletest/1.16.0/lib \
    -lgtest -lgtest_main -pthread

(base) hayden@jMac unitTest % ./test
Running main() from /tmp/googletest-20250207-4735-e28tfc/googletest-1.16.0/googletest/src/gtest_main.cc
[==========] Running 0 tests from 0 test suites.
[==========] 0 tests from 0 test suites ran. (0 ms total)
[  PASSED  ] 0 tests.
```

- 1️⃣ Verificar onde o GoogleTest foi instalado
Execute o seguinte comando para encontrar o local de instalação:
```bash
brew info googletest
```
A saída deve mostrar algo como:
```bash
/opt/homebrew/Cellar/googletest/1.16.0
```
Isso significa que os arquivos de cabeçalho (.h) estão em:
```bash
/opt/homebrew/Cellar/googletest/1.16.0/include
```
E as bibliotecas compiladas (.a) estão em:
```bash
/opt/homebrew/Cellar/googletest/1.16.0/lib
```
- 2️⃣ Compilar o código incluindo os caminhos corretos
Agora, altere o comando de compilação para incluir esses caminhos explicitamente:
```bash
g++ -o test withGoogleTest.cpp \
    -I/opt/homebrew/Cellar/googletest/1.16.0/include \
    -L/opt/homebrew/Cellar/googletest/1.16.0/lib \
    -lgtest -lgtest_main -pthread
🔹 -I adiciona o caminho dos arquivos de cabeçalho.
🔹 -L adiciona o caminho das bibliotecas compiladas.
🔹 -lgtest -lgtest_main indica que estamos vinculando com GoogleTest.
🔹 -pthread é necessário porque GoogleTest usa threads internamente.
```
Se a compilação for bem-sucedida, rode:
```bash
./test
```
ou
```bash
g++ -o test withGoogleTest.cpp \
    -I/opt/homebrew/Cellar/googletest/1.16.0/include \
    -L/opt/homebrew/Cellar/googletest/1.16.0/lib \
    -lgtest -lgtest_main -pthread && ./test
```
- 3️⃣ Criar um Makefile (Opcional, mas recomendado)
Para evitar repetir comandos longos, crie um Makefile no diretório do projeto:
```makefile
CC=g++
CFLAGS=-I/opt/homebrew/Cellar/googletest/1.16.0/include
LDFLAGS=-L/opt/homebrew/Cellar/googletest/1.16.0/lib -lgtest -lgtest_main -pthread
SRC=withGoogleTest.cpp

all: test

test: $(SRC)
	$(CC) $(CFLAGS) -o test $(SRC) $(LDFLAGS)

clean:
	rm -f test
```
Agora, basta rodar:
```bash
make    # Compila o teste
./test  # Executa o teste
make clean  # Limpa os arquivos gerados
````
Isso facilita a compilação e evita erros de digitação nos comandos! 🚀
