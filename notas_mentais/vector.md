# O método .size()

Ver [arquivo](../c++/leetcode/1672/solution.cpp)
O método `.size()` pertence à classe `std::vector` da STL (Standard Template Library) do C++ e retorna o número de elementos armazenados no vetor.

No caso de `accounts.size()`, ele retorna quantos arrays internos (clientes) existem no vetor accounts.

Exemplo:
```cpp
vector<int> numeros = {10, 20, 30, 40};
cout << numeros.size(); // Saída: 4
```
Para uma matriz (vetor de vetores), podemos usar `accounts[i].size()` para saber quantos bancos diferentes um cliente possui.

## Outros métodos da classe `std::vector`
Aqui estão alguns métodos úteis da classe std::vector:

`.push_back(elemento)` → Adiciona um elemento ao final do vetor.
`.pop_back()` → Remove o último elemento do vetor.
`.empty()` → Retorna true se o vetor estiver vazio, caso contrário, false.
`.clear()` → Remove todos os elementos do vetor.
`.insert(posicao, elemento)` → Insere um elemento em uma posição específica.
`.erase(posicao)` → Remove um elemento em uma posição específica.
`.front()` → Retorna o primeiro elemento do vetor.
`.back()` → Retorna o último elemento do vetor.
`.resize(n)` → Redimensiona o vetor para n elementos.
`.at(posicao)` → Retorna o elemento na posição especificada (com checagem de limites).