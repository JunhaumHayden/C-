# Arvores Binárias
São estrutura de dados multidimensional, que consiste de nós e arcos, onde cada nó pode ter no máximo dois filhos, sendo um filho à esquerda e outro à direita.
**Raiz** é um nó que não tem ancestrais; só pode ter nós filhos
**Folha** é um nó que não tem filhos; só pode ter nós ancestrais (Seus filhos são estruturas vazias).

Uma árvore pode ser definida recursivamente como:
- Uma estrutura vazia é uma árvore vazia.
- Se t1,...,tn são arvores disjuntas, então a estrutura cuja raiz tem como suas filhas as raizes de t1,...,tn também é uma árvore.
- Somente estruturas geradas pelas regras 1 e 2 são árvores.

## Exemplificando:

Uma árvore disjunta significa que duas ou mais árvores não compartilham nenhum nó entre si — ou seja, seus conjuntos de nós são mutuamente exclusivos.

#### No contexto da definição:
Quando dizemos que t1, t2, ..., tn são árvores disjuntas, estamos dizendo que:

- Nenhum nó da árvore t1 aparece em t2, t3, ..., tn e assim por diante.
- Elas são árvores separadas, sem sobreposição de nós.

#### Exemplo:
Imagine três árvores distintas:
```bash
t1:      1
        / \
       2   3

t2:      4 
          \
           5

t3:      6
        / \
       7   8
```

Essas três são disjuntas, porque:

- `t1` tem os nós {1, 2, 3}
- `t2` tem os nós {4, 5}
- `t3` tem os nós {6, 7, 8}

Nenhum nó é repetido entre as árvores.

Se agora criamos uma nova árvore `T` cuja raiz é, por exemplo, o nó `0`, e cujos filhos são as raízes de `t1`, `t2` e `t3`, então:
```bash
  T:        0
          / | \
         t1 t2 t3

```
Essa nova estrutura também é uma árvore, pois é formada com base em árvores disjuntas.

### Resumindo:
**Árvores disjuntas** são árvores que não compartilham nós entre si. Essa condição é importante para garantir que, ao montar uma nova árvore com várias subárvores, a estrutura continue **sendo válida**, sem ciclos ou múltiplas referências ao mesmo nó.

## Definições:

1. **Caminho**: é uma sequência única de arcos. 
> Cada nó tem que ser atingível a partir da raiz por essa sequência única.

2. **Comprimento**: É o número de arcos que compõem o caminho.
3. **Nível** de um nó: É o comprimento do caminho da raiz até o nó mais 1 (+1).
4. **Altura** de uma árvore não vázia: É o nível máximo de um nó na árvore
5. **Árvore vazia**: É uma arvore legitima de altura 0 (por definição).
6. **Árvore de altura 1**: É uma árvore com apenas um nó (a raiz).
>OBS:
> 
> Este é o único caso em que um nó é raiz e folha.
>O nível de um nó precisa estar dentro do intervalo [1, altura da árvore].

**Árvore Binária Completa**: É uma arvore que satifaz a condição 2ˆi nós no nível i + 1.
> Se todos os nós em todos os níveis, exceto o ultimo, tivessem dois filhos, então haveria:
> 1 = 2ˆ0 nós no nível 1, 
> 2 = 2ˆ1 nós no nível 2, 
> 4 = 2ˆ2 nós no nível 3 
> e assim por diante.