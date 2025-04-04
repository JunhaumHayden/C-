## posicionamento
### Expressão:
> usa e incrementa
```c++
storage[last++] = element;
```
#### Explicação:

- O valor atual de last é usado antes do incremento.
- O elemento é armazenado na posição storage[last].
- Depois disso, last é incrementado.

#### Equivalente a:
```c
storage[last] = element;
last = last + 1;
```
### Expressão:
> Incrementa e usa
```c
storage[++last] = element;
```
#### ✅ Explicação:

- last é incrementado primeiro.
- O valor incrementado de last é usado como índice.
- O elemento é armazenado na posição storage[last] depois do incremento.
#### 🔹 Equivalente a:
```c
last = last + 1;
storage[last] = element;
```