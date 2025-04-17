# 🧵 pthread_create(): O que é?

É uma função da biblioteca POSIX threads (pthreads), usada em C/C++ para criar uma nova thread de execução. Ela permite que seu programa execute funções em paralelo com o fluxo principal.

## 📌 Sintaxe básica
```c
int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),
                   void *arg);
``` 
## 🧩 Parâmetros explicados

|   Parâmetro	         |     Significado                         |
|------------------------|-----------------------------------------|
| `pthread_t *thread` |	Ponteiro para uma variável do tipo `pthread_t` que irá armazenar o ID da nova thread criada.  |
| `const pthread_attr_t *attr`|	Atributos da thread (normalmente `NULL` para usar os padrões). |
| `void *(*start_routine)(void *)` | Função que será executada pela thread. Deve aceitar `void*` como argumento e retornar `void*`. |
| `void *arg` |	Argumento que será passado para a função start_routine. Pode ser um ponteiro para qualquer tipo de dado. |

## ✅ Valor de retorno

- `0`: sucesso.
- diferente de 0: falha (por exemplo, falta de memória ou limite de threads atingido).
## 🧠 Exemplo completo
```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* minha_funcao(void* arg) {
    int loops = *(int*)arg;
    for (int i = 0; i < loops; ++i) {
        printf("Thread está executando... %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    int n_loops = 5;

    // Cria a thread
    if (pthread_create(&thread, NULL, minha_funcao, &n_loops) != 0) {
        perror("Erro ao criar thread");
        return 1;
    }

    // Espera a thread terminar
    pthread_join(thread, NULL);

    printf("Thread terminou!\n");
    return 0;
}
```
## 🧶 O que você precisa garantir:

1. A função passada para a thread deve ser do tipo: `void* func(void*)`.

2. O argumento (por exemplo n_loops) deve estar acessível durante toda a execução da thread.
3. Normalmente passamos o endereço de uma variável local ou de heap.

> Se precisar passar múltiplos argumentos, use uma struct.
## 🤯 Dica: Como passar vários parâmetros?
```c
typedef struct {
    int a;
    float b;
} Parametros;

void* func(void* arg) {
    Parametros* p = (Parametros*) arg;
    // agora posso usar p->a e p->b
}
```

## ✅ Exemplo: Criando múltiplas threads com argumentos distintos
```c 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estrutura para passar múltiplos argumentos para a thread
typedef struct {
    int id;
    int valor;
} ThreadArgs;

void* minha_thread(void* args) {
    ThreadArgs* dados = (ThreadArgs*)args;
    printf("Thread %d recebeu o valor %d\n", dados->id, dados->valor);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int n_threads = 5;
    pthread_t threads[n_threads];
    ThreadArgs argumentos[n_threads];

    for (int i = 0; i < n_threads; i++) {
        argumentos[i].id = i;
        argumentos[i].valor = (i + 1) * 10;

        if (pthread_create(&threads[i], NULL, minha_thread, &argumentos[i]) != 0) {
            perror("Erro ao criar thread");
            return 1;
        }
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Todas as threads terminaram.\n");

    return 0;
}
```
## ⚙️ Como compilar e executar no MacBook com chip M1

1. Salvar o código em um arquivo: por exemplo `threads_exemplo.c`.
2. Compilar com o clang (que já vem no macOS):
```bash
clang -pthread threads_exemplo.c -o threads_exemplo
//ou
gcc -pthread threads_exemplo.c -o threads_exemplo
```
Executar:
```c 
./threads_exemplo
```
## ✅ Saída esperada (exemplo):
```bash
Thread 0 recebeu o valor 10
Thread 1 recebeu o valor 20
Thread 2 recebeu o valor 30
Thread 3 recebeu o valor 40
Thread 4 recebeu o valor 50
Todas as threads terminaram.
````
> ⚠️ A ordem pode variar, pois as threads rodam de forma concorrente.