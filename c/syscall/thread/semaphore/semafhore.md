# Function Deprecated

### sem_init, sem_destroy, sem_wait, sem_post

Em sistemas macOS, os avisos de "Function 'sem_init' is deprecated" e "Function 'sem_destroy' is deprecated" por conta das mudanças nas APIs do sistema operacional, não necessariamente da linguagem C em si.

## ⚠️ Por que isso acontece?
No macOS, a implementação de semáforos POSIX com `sem_init`, `sem_wait`, `sem_post`, etc., foi marcada como deprecated (obsoleta) nas versões mais recentes do Xcode/macOS SDK, especialmente em ambientes que não dão suporte total à semáforos anônimos (sem_init com pshared = 0, em memória não compartilhada entre processos).

Isso quer dizer: a Apple recomenda que você não use `sem_init` e similares em novos projetos, por questões de segurança e portabilidade.

✅ Alternativas modernas
1. Use `dispatch_semaphore_t` (GCD) – Apple way

No macOS/iOS, é recomendado usar os **Grand Central Dispatch** (GCD) semaphores, mais seguros e otimizados para o sistema.

## 🚨 Dica final:
Se o seu projeto for cross-platform (Linux + macOS), a abordagem com pthread_mutex_t ou usando bibliotecas portáveis como C++ <thread> e <mutex> (em caso de C++) pode ser mais adequada a longo prazo.