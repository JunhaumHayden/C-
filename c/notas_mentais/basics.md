# A função printf()
A função `printf()` tem a seguinte forma geral:
`printf(string_de_controle, lista_de_argumentos)`

Teremos, na string de controle, uma descrição de tudo que a
função vai colocar na tela.
Isto é feito usando-se os códigos de controle (especificador de formato - format specifies type), veja alguns
exemplos:

| Código | Significado       |
|--------|-------------------|
| %d     | Inteiro          |
| %f     | Float            |
| %c     | Caractere        |
| %s     | String           |
| %p     | pointer addresses   |
| %x     | unsigned int     |
| %%     | Coloca um % na tela |

# Struct
> ver arquivo /struct/hellostruct.c
estrutura de dados imutavel com elementos de tipos diferentes que vão concatenando. Pode nomear essa nova estrutura dentro da linguagem, serve como um molde que quebra os valores passados como argumentos para dentro do espaço de elemento.
# Tuple != Array
Tuple é como um Struct anomino, sem nomes ou etiquetas
- Tuple: estrutura de dados (conjunto) imutavel com elementos de tipos diferentes.
- Array: estrutura de dados (conjunto) imutavel com elementos de mesmo tipo.
- Struct: estrutura de dados 