# Exercício 1
Utilize um `pthread_mutex_t` para proteger a região crítica do código do Exercício 1 
da atividade prática anterior, em que um contador era acessado concorrentemente por 
várias threads, resultando em um valor inconsistente. 

O mutex deve ser utilizado de modo a controlar a concorrência entre as threads, fazendo 
com que o programa apresente o resultado esperado.

Você precisará das seguintes funções:

- `pthread_mutex_lock()`
- `pthread_mutex_unlock()`
- `pthread_mutex_init()`
- `pthread_mutex_destroy()`

## O que vamos fazer:
1. Declarar um mutex global.
2. Inicializar o mutex no `main()` com `pthread_mutex_init()`.
3. Usar `pthread_mutex_lock()` e `pthread_mutex_unlock()` dentro da função `incrementor()`, 
ao redor do trecho crítico **(contador_global += 1;)**.
4. Destruir o mutex no final com `pthread_mutex_destroy()`.