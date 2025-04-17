# Enunciado:

### Escreva uma função para:
* Dado um texto de entrada (na forma de string), adicione a uma fila caracter por caracter, exceto se for um `<` ou `>`.

Ao ler o caracter `<` na entrada:
- **remover** um elemento (caracter) da fila.
  
Ao ler o caracter `>`: 
- **reinserir** o último elemento (caracter) da fila.

O retorno da função é a fila resultante, contendo o texto editado.

## Protótipo da função:
```c
structures::ArrayQueue<char> editaTexto(std::string texto);
```
Exemplo de execução:
```bash
std::string texto = "2024< Universidade <<Federal ->> Santa<< Catarina";
structures::ArrayQueue<char> fila = editaTexto(texto);
```
Saída:
```bash
Universidade Federal --- Santa Catarina
```