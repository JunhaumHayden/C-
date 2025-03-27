# Usando C

## 1. Criar um arquivo com o codigo fonte
Usando o `vim` por exemplo:
```bash
 vim hello.c
```
Irá abrir o editor e criar um arquivo chamado `hello.c` no diretorio atual

> verificar comando do vim
> 
> [link 1](https://codamos.com.br/vim-basico/)

Entre com o seguinte codigo:

``` c
#include <stdio.h> 
int main () {
	printf("Hello World!\n");
	return 0;
}
```
Salve e feche o vim.

## 2. Compile o Arquivo
Use o compilador clang (disponível por padrão no macOS) ou gcc (se estiver instalado via Homebrew). O comando é:
```bash
clang hello.c -o hello
```
ou
```bash
gcc hello.c -o hello
```
Explicação:
* `hello.c`: O arquivo-fonte que você quer compilar.
* `-o hello`: Define o nome do arquivo executável gerado. Aqui será chamado hello.
Se a compilação for bem-sucedida, um arquivo chamado hello será criado no mesmo diretório.

## 3. Execute o Arquivo
Agora, você pode executar o programa compilado com:
``` bash
./hello
```
A saída será:
``` bash
Hello Word!
```

# Analisando em Baixo Nível
O comando `xxd` é usado para exibir o conteúdo binário de um arquivo em formato legível por humanos, representando cada byte em formato binário. Vamos detalhar:

### 1. O Comando `xxd`
- O `xxd` é uma ferramenta que converte arquivos ou entrada padrão (stdin) em representação hexadecimal ou binária. Também pode reverter uma representação hexadecimal/binária para o formato original.
### 2. Opção `-b`
- `-b`: Especifica que a saída deve ser exibida em formato binário (bits), em vez do padrão hexadecimal.
### 3. O Arquivo `hello.c`
Ao aplicar o comando `xxd -b hello.c`, você verá cada byte do arquivo de texto convertido em sua forma binária.

Por exemplo, supondo que o arquivo hello.c a saída de `xxd -b hello.c` será algo assim (apenas uma parte, para simplificar):
``` bash
00000000: 00100011 01101001 01101110 01100011 01101100 01110101  #include
00000006: 01100100 01100101 00100000 00111100 01110011 01110100  de <st
0000000c: 01100100 01101001 01101111 00101110 01101000 01110100  dio.ht
00000012: 01101101 00101110 01101000 00100000 01101001 01101110  m.in
...
```
### Explicando a Saída
- Coluna da Esquerda (00000000): Mostra o deslocamento (offset) em relação ao início do arquivo, em formato hexadecimal.
- Bytes em Binário: Cada byte do arquivo é representado em 8 bits.
- Texto Original: Dependendo do terminal, pode aparecer como texto legível à direita (não mostrado no exemplo acima).
### Uso Prático
O comando é útil para:
1. Depuração de arquivos: Inspecionar a representação binária de arquivos de texto ou binários.
2. Análise de baixo nível: Ver exatamente como os dados estão armazenados.
3. Manipulação de bits: Para engenharia reversa ou aprendizado sobre como os dados são estruturados.
> Nota
> Para arquivos maiores, a saída pode ser muito extensa. Você pode usar | less para visualizar:
> `xxd -b hello.c | less`
> Para converter a saída binária de volta ao arquivo original, você pode usar o comando xxd -r (desde que a formatação da saída não tenha sido alterada).
## objdump
O comando `objdump` é usado para inspecionar um arquivo binário e exibir seu código de máquina (instruções em assembly) junto com o código-fonte correspondente, caso esteja disponível. Aqui está uma explicação detalhada:

### Componentes do Comando: `objdump -S --disassemble hello`
- `objdump`: É uma ferramenta usada para examinar arquivos binários (como executáveis, bibliotecas ou arquivos objeto). Ele permite ver as seções, os símbolos, o código de máquina e outras informações sobre o arquivo.
- `-S`: Este parâmetro exibe o código-fonte junto com o código assembly, se o binário foi compilado com símbolos de depuração (usando a flag -g durante a compilação). Assim, você pode ver como o código-fonte se traduz em instruções de máquina.
- `--disassemble`: Diz ao objdump para desmontar (disassemble) o código executável no binário e exibir as instruções em assembly. Ele traduz o código de máquina para uma forma legível.
- `hello`: É o arquivo executável que você está inspecionando. Esse arquivo deve ser gerado previamente por um compilador (como gcc ou clang).
### Quando Usar Este Comando
1. Depuração Avançada: Para entender como o compilador traduziu seu código-fonte para assembly.
2. Análise de Performance: Para verificar como as instruções de máquina podem ser otimizadas.
3. Exploração de Binários: Para aprendizado ou engenharia reversa (desde que você tenha permissão legal para isso).
4. Verificação de Segurança: Inspecionar o binário para identificar possíveis vulnerabilidades.
### Exemplo Prático
Código Fonte (hello.c):
```c
#include <stdio.h>
int main() {
    printf("Hello, World!\n");
    return 0;
}
```
Compile o Arquivo com Informações de Depuração:
``` bash
gcc -g -o hello hello.c
```
Execute o Comando objdump:
```bash
objdump -S --disassemble hello
```
Saída Esperada: A saída exibirá o código assembly do programa, junto com o código-fonte intercalado (se disponível). Algo como:
``` bash
hello:	file format mach-o arm64

Disassembly of section __TEXT,__text:

0000000100003f58 <_main>:
100003f58: d10083ff    	sub	sp, sp, #0x20
; int main () {
100003f5c: a9017bfd    	stp	x29, x30, [sp, #0x10]
100003f60: 910043fd    	add	x29, sp, #0x10
100003f64: 52800008    	mov	w8, #0x0                ; =0
100003f68: b9000be8    	str	w8, [sp, #0x8]
100003f6c: b81fc3bf    	stur	wzr, [x29, #-0x4]
100003f70: 90000000    	adrp	x0, 0x100003000 <_printf+0x100003000>
; 	printf("Hello World!\n");
100003f74: 913e6000    	add	x0, x0, #0xf98
100003f78: 94000005    	bl	0x100003f8c <_printf+0x100003f8c>
100003f7c: b9400be0    	ldr	w0, [sp, #0x8]
100003f80: a9417bfd    	ldp	x29, x30, [sp, #0x10]
; 	return 0;
100003f84: 910083ff    	add	sp, sp, #0x20
100003f88: d65f03c0    	ret

Disassembly of section __TEXT,__stubs:

0000000100003f8c <__stubs>:
100003f8c: b0000010    	adrp	x16, 0x100004000 <_printf+0x100004000>
100003f90: f9400210    	ldr	x16, [x16]
100003f94: d61f0200    	br	x16
```
### **Explicação da Saída**
1. **Endereços:** Cada instrução assembly tem um endereço de memória associado (exemplo: `1139`, `1144`, etc.).
2. **Instruções Assembly:** São as instruções reais que o processador executa, como `push`, `mov`, `callq`, etc.
3. **Código-Fonte:** Se o binário contém informações de depuração, você verá as linhas do código C associadas às instruções assembly.

---

### **Notas Importantes**
- Se o binário **não** for compilado com a flag `-g`, o código-fonte não será mostrado, e você verá apenas o assembly.
- Para binários grandes, a saída pode ser extensa. Use um pager como `less` para navegar:
```bash
objdump -S --disassemble hello | less
```
### Comparação: Mach-O vs ELF

| Aspecto                | Mach-O (macOS)                     | ELF (Linux)                        |
|------------------------|-------------------------------------|-------------------------------------|
| Formato               | Mach Object                        | Executable and Linkable Format     |
| Arquitetura           | ARM64 (Apple Silicon) e x86_64 (Intel Macs) | ARM (ARMv7/ARM64), x86, x86_64, etc. |
| Sistema Operacional   | macOS e iOS                        | Linux e sistemas Unix-like         |
| Portabilidade         | Exclusivo para macOS/iOS           | Usado em diversos sistemas e plataformas |
| Binários Universais   | Suporte para múltiplas arquiteturas | Não há suporte nativo              |
| Carregador de Binários | Kernel XNU                         | Kernel Linux                       |
| Ferramentas de Inspeção | otool, file, objdump               | readelf, file, objdump, gdb        |

