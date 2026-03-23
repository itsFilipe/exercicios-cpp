# Robô Navegador — Documentação de Estudo C++

> Documento de revisão técnica baseado no projeto `robo_navegador`.  
> Cobre: matrizes, structs, encapsulamento, BFS e reconstrução de caminho.

---

## Índice

1. [Estrutura do Projeto](#1-estrutura-do-projeto)
2. [Convenção de Coordenadas](#2-convenção-de-coordenadas)
3. [Struct vs Class / Struct Ponto](#3-struct-vs-class--struct-ponto)
4. [Sobrecarga de Operador](#4-sobrecarga-de-operador-operator)
5. [A Classe `robo`](#5-a-classe-robo)
6. [Matrizes com `vector<vector<int>>`](#6-matrizes-com-vectorvectorint)
7. [Referências Const (`const T&`)](#7-referências-const-const-t)
8. [O Algoritmo BFS](#8-o-algoritmo-bfs)
9. [Reconstrução do Caminho com `came_from`](#9-reconstrução-do-caminho-com-came_from)
10. [Vetores de Direção](#10-vetores-de-direção)
11. [Diretivas de Pré-processador](#11-diretivas-de-pré-processador)
12. [Fluxo Completo de Execução](#13-fluxo-completo-de-execução)
13. [Glossário](#14-glossário)


## 1. Estrutura do Projeto

```
robo.h       → Declaração da classe robo (interface pública)
robo.cpp     → Implementação da classe robo
main.cpp     → Loop do jogo, BFS, renderização, lógica de frutas
```

**Por que separar `.h` e `.cpp`?**

O `.h` é o **contrato**: declara o que existe.  
O `.cpp` é a **implementação**: define como funciona.

Quando outro arquivo faz `#include "robo.h"`, ele só enxerga a interface — não precisa saber os detalhes internos. Isso é **encapsulamento** no nível de arquivo.

---

## 2. Convenção de Coordenadas

Este é um dos pontos mais confusos do projeto. Entender bem evita bugs.

```
mapa[linha][coluna]  →  mapa[x][y]
```

| Variável | Significado | Cresce para |
|----------|-------------|-------------|
| `x`      | linha       | baixo (S)   |
| `y`      | coluna      | direita (D) |

```
         y=0  y=1  y=2  y=3
x=0  →  [ 1 ][ 0 ][ 1 ][ 0 ] ...
x=1  →  [ 1 ][ 0 ][ 1 ][ 0 ] ...
x=2  →  [ 1 ][ 0 ][ 0 ][ 0 ] ...
```

Portanto:
- `W` (subir na tela) → `x--` (linha menor)
- `S` (descer na tela) → `x++` (linha maior)
- `A` (esquerda) → `y--`
- `D` (direita) → `y++`

> ⚠️ **Bug clássico**: inverter `x` e `y` faz o robô aparecer na posição errada visualmente, mesmo que as validações passem. O projeto original tinha essa inversão em `renderizar_mapa` e `pegar_fruta`.

---

## 3. Struct vs Class / Struct `Ponto`

```cpp
struct Ponto {
    int x; // linha
    int y; // coluna

    bool operator==(const Ponto& outro) const {
        return x == outro.x && y == outro.y;
    }
};
```

### `struct` vs `class`

| Aspecto | `struct` | `class` |
|---------|----------|---------|
| Membros por padrão | `public` | `private` |
| Herança por padrão | `public` | `private` |
| Uso idiomático | Dados simples, POD | Entidades com comportamento |

`Ponto` é um dado simples (par de inteiros) sem lógica de negócio — `struct` é a escolha certa.

### `int` vs `size_t`

O projeto original usou `size_t x, y` em `Ponto`. O problema: `size_t` é **sem sinal**. Comparar com `int` gera warnings, e fazer `size_t - 1` quando o valor é `0` resulta em um número gigantesco (underflow), não em `-1`. Por isso o projeto usa `int`.

---

## 4. Sobrecarga de Operador (`operator==`)

```cpp
bool operator==(const Ponto& outro) const {
    return x == outro.x && y == outro.y;
}
```

Sem isso, `a == b` para structs não compila (o compilador não sabe o que "igual" significa para `Ponto`).

Com isso, podemos escrever:

```cpp
if (atual == alvo) { ... }          // limpo
if (cursor == Ponto{-1, -1}) { ... } // sentinel check
```

Em vez de:

```cpp
if (atual.x == alvo.x && atual.y == alvo.y) { ... } // verboso e repetitivo
```

**Assinatura completa:**

```
bool operator==(const Ponto& outro) const
│    │           │             │     │
│    │           │             │     └─ não modifica o objeto (this)
│    │           │             └─────── nome do parâmetro
│    │           └───────────────────── referência const (sem cópia)
│    └───────────────────────────────── nome do operador
└────────────────────────────────────── tipo de retorno
```

---

## 5. A Classe `robo`

### Declaração (robo.h)

```cpp
class robo {
    int x; // private (implícito)
    int y;
public:
    robo(int xi = 1, int yi = 1);       // construtor com default args
    int getX() const { return x; }      // getter — inline no .h
    int getY() const { return y; }
    bool tentar_mover(char cmd, const std::vector<std::vector<int>>& mapa);
};
```

### Argumento Padrão (Default Argument)

```cpp
robo(int xi = 1, int yi = 1);
```

Um único construtor cobre dois usos:

```cpp
robo r1;        // xi=1, yi=1 (usa defaults)
robo r2(3, 5);  // xi=3, yi=5 (sobrescreve)
```

Regra: argumentos com default devem vir **do final para o início**. Você não pode ter `void f(int a=0, int b)` — `b` não tem default mas vem depois de `a` que tem.

### Member Initializer List

```cpp
robo::robo(int xi, int yi)
    : x(xi), y(yi) {}  // ← lista de inicialização
```

Os membros são inicializados **antes** do corpo `{}` executar. Para `int` a diferença de performance é zero, mas o hábito é essencial para:
- `const` membros (só podem ser inicializados na lista)
- Membros do tipo de outra classe (evita chamada de construtor default + atribuição)

### `const` em Métodos

```cpp
int getX() const { return x; }
```

O `const` ao final significa: "este método não altera o estado do objeto". Consequência direta: você pode chamá-lo em uma referência `const robo& r`:

```cpp
void renderizar(const robo& r) {
    r.getX(); // OK — getX() é const
    r.tentar_mover(...); // ERRO — tentar_mover não é const
}
```

Sem o `const` em `getX()`, a função `renderizar` não compilaria com `const robo& r`.

### `tentar_mover` — Padrão Calcular → Validar → Confirmar

```cpp
bool robo::tentar_mover(char comando, const std::vector<std::vector<int>>& mapa) {
    int aux_x = x;  // 1. copia em auxiliares
    int aux_y = y;

    switch (comando) { /* 2. calcula intenção */ }

    if (/* fora dos limites */) return false;  // 3. valida
    if (mapa[aux_x][aux_y] == 1) return false;

    x = aux_x; y = aux_y;  // 4. commit (só aqui o estado muda)
    return true;
}
```

**Por que usar auxiliares?**

Se movêssemos `x` diretamente e depois a validação de `y` falhasse, precisaríamos desfazer `x`. Com auxiliares, o objeto **nunca fica em estado inconsistente**.

---

## 6. Matrizes com `vector<vector<int>>`

### Criação

```cpp
// Sintaxe de inicialização direta:
vector<vector<int>> mapa = {
    {1, 0, 1},
    {1, 0, 0},
    {1, 1, 0}
};

// Criação dinâmica com valor padrão:
int linhas = 5, colunas = 10;
vector<vector<bool>> passou(linhas, vector<bool>(colunas, false));
//                          └─ repete `linhas` vezes o valor inicial
//                                        └─ vetor de `colunas` bools, todos false
```

### Acesso

```cpp
mapa[i][j]        // linha i, coluna j
mapa.size()       // número de linhas
mapa[0].size()    // número de colunas (assume linhas de tamanho igual)
```

### Iteração

```cpp
for (int i = 0; i < (int)mapa.size(); i++)
    for (int j = 0; j < (int)mapa[i].size(); j++)
        // usa mapa[i][j]
```

**Por que `(int)mapa.size()`?**

`size()` retorna `size_t` (inteiro sem sinal). Se `i` é `int`, a comparação `i < mapa.size()` mistura tipos com sinal e sem sinal — o compilador emite warning. O cast `(int)` explicita a conversão e silencia o warning legitimamente.

---

## 7. Referências Const (`const T&`)

Ao passar objetos grandes para funções, temos três opções:

```cpp
void f1(vector<vector<int>>  mapa); // por VALOR    — copia toda a matriz (lento!)
void f2(vector<vector<int>>& mapa); // por REF      — acesso direto, pode modificar
void f3(const vector<vector<int>>& mapa); // por REF CONST — acesso direto, SÓ LEITURA
```

| Modo | Cópia? | Pode modificar original? | Aceita temporários? |
|------|--------|--------------------------|---------------------|
| Valor | Sim | Não (cópia) | Sim |
| Ref | Não | Sim | Não |
| Ref const | Não | Não | Sim |

**Regra prática:** se a função não precisa modificar o argumento, use `const &`. É sempre mais eficiente para objetos grandes.

---

## 8. O Algoritmo BFS

### O que é BFS?

BFS (Breadth-First Search / Busca em Largura) explora um grafo nível por nível, como ondas em uma piscina:

```
Nível 0: [início]
Nível 1: [vizinhos do início]
Nível 2: [vizinhos dos vizinhos]
...
```

**Propriedade fundamental:** o primeiro caminho encontrado até qualquer nó é o **mais curto** (em número de arestas/passos).

### Por que BFS garante o caminho mais curto?

Porque todos os nós a distância `d` são explorados **antes** de qualquer nó a distância `d+1`. Quando o alvo é encontrado pela primeira vez, ele foi alcançado pelo menor número de passos possível.

DFS (pilha) não tem essa garantia — pode encontrar um caminho longo antes do curto.

### Estrutura de dados: `std::queue` (Fila FIFO)

```
Fila: [A] → [B] → [C] → [D]
       ↑                  ↑
    front()             back()
   (próximo a sair)   (próximo a entrar)

push(E)  → [A][B][C][D][E]
front()  → A
pop()    → remove A → [B][C][D][E]
```

A fila é essencial para BFS: garante que processamos nós por ordem de descoberta (= ordem de distância).

### Implementação

```cpp
std::vector<std::vector<bool>> passou(linhas, std::vector<bool>(colunas, false));
std::vector<std::vector<Ponto>> came_from(linhas, std::vector<Ponto>(colunas, {-1,-1}));

std::queue<Ponto> fila;
fila.push(inicio);
passou[inicio.x][inicio.y] = true;

while (!fila.empty()) {
    Ponto atual = fila.front();
    fila.pop();

    if (atual == alvo) { encontrou = true; break; }

    for (int i = 0; i < 4; i++) {
        int nr = atual.x + dr[i];
        int nc = atual.y + dc[i];

        if (dentro_dos_limites && !passou[nr][nc] && nao_e_parede) {
            passou[nr][nc]    = true;
            came_from[nr][nc] = atual;  // ← grava predecessor
            fila.push({nr, nc});
        }
    }
}
```

**Por que marcar `passou` ANTES de inserir na fila?**

Se marcarmos só quando retiramos da fila, o mesmo nó pode ser inserido várias vezes antes de ser processado — o BFS explora em duplicata e fica incorreto. Marcamos ao inserir para garantir inserção única.

---

## 9. Reconstrução do Caminho com `came_from`

`came_from[x][y]` responde: *"de onde eu vim para chegar em (x, y)?"*

### Preenchimento durante BFS

```
Inicio: (1,1)    Alvo: (3,3)

Após BFS, came_from contém (exemplo):
  came_from[1][2] = {1,1}
  came_from[2][2] = {1,2}
  came_from[3][2] = {2,2}
  came_from[3][3] = {3,2}
```

### Reconstrução reversa

```cpp
Ponto cursor = alvo;  // começa no alvo
while (!(cursor == Ponto{-1, -1})) {
    caminho.push_back(cursor);       // adiciona ao vetor
    if (cursor == inicio) break;
    cursor = came_from[cursor.x][cursor.y]; // volta um passo
}
std::reverse(caminho.begin(), caminho.end()); // inverte: inicio→alvo
```

Visualização passo a passo:

```
cursor = (3,3) → came_from[3][3] = (3,2)
cursor = (3,2) → came_from[3][2] = (2,2)
cursor = (2,2) → came_from[2][2] = (1,2)
cursor = (1,2) → came_from[1][2] = (1,1) ← início
cursor = (1,1) → é o início, para

caminho antes do reverse: [(3,3), (3,2), (2,2), (1,2), (1,1)]
caminho após  o reverse:  [(1,1), (1,2), (2,2), (3,2), (3,3)]
                            início →                   → alvo
```

### Por que o sentinel `{-1, -1}`?

O ponto inicial não tem predecessor. Inicializamos `came_from` inteiro com `{-1, -1}`. Quando a reconstrução chega no início e tenta dar mais um passo, `came_from[inicio.x][inicio.y] = {-1,-1}`, o loop encerra pelo `break` antes de tentar acessar o sentinel — mas o sentinel garante segurança caso o `break` falhe.

### Aplicando o caminho ao robô

```cpp
// caminho[0] = posição atual do robô (pula)
for (size_t passo = 1; passo < caminho.size(); passo++) {
    Ponto proximo = caminho[passo];
    char  cmd     = 0;

    if      (proximo.x < meu_robo.getX()) cmd = 'W';
    else if (proximo.x > meu_robo.getX()) cmd = 'S';
    else if (proximo.y < meu_robo.getY()) cmd = 'A';
    else if (proximo.y > meu_robo.getY()) cmd = 'D';

    meu_robo.tentar_mover(cmd, mapa);
}
```

Não precisamos calcular `cmd` de forma absoluta — basta comparar a posição atual do robô com o próximo ponto no caminho.

---

## 10. Vetores de Direção

Padrão clássico para explorar vizinhos em matrizes:

```cpp
const int dr[] = {-1,  1,  0,  0}; // deslocamento de linha
const int dc[] = { 0,  0, -1,  1}; // deslocamento de coluna
```

Para o nó `(r, c)`, seus 4 vizinhos são:

| `i` | `dr[i]` | `dc[i]` | Vizinho       | Direção   |
|-----|---------|---------|---------------|-----------|
| 0   | -1      | 0       | `(r-1, c)`    | cima      |
| 1   | +1      | 0       | `(r+1, c)`    | baixo     |
| 2   | 0       | -1      | `(r, c-1)`    | esquerda  |
| 3   | 0       | +1      | `(r, c+1)`    | direita   |

```cpp
for (int i = 0; i < 4; i++) {
    int nr = atual.x + dr[i];
    int nc = atual.y + dc[i];
    // processa vizinho (nr, nc)
}
```

Essa técnica evita 4 blocos `if` repetidos e facilita adicionar diagonais (`dr[]` de 8 elementos).

---

## 11. Diretivas de Pré-processador

```cpp
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
```

O pré-processador roda **antes** da compilação. `#ifdef` inclui o bloco seguinte somente se a macro estiver definida. `_WIN32` é definida automaticamente em compiladores Windows (MSVC, MinGW). Em Linux/macOS, a macro não existe → cai no `#else`.

**Outros usos comuns:**

```cpp
// Include guard — evita inclusão dupla do mesmo .h
#ifndef ROBO_H
#define ROBO_H
// ... conteúdo do header
#endif

// Código de debug que some em Release
#ifdef DEBUG
    std::cout << "valor de x: " << x << "\n";
#endif
```

---

## 13. Fluxo Completo de Execução

```
main()
│
├── srand(time(0))          → inicializa semente aleatória
├── robo meu_robo           → construtor: x=1, y=1
├── mapa definido
│
└── while(rodando)
    │
    ├── encontrar_fruta()   → varre mapa, retorna {x,y} da fruta
    ├── encontra_caminho()  → BFS do robô até a fruta
    │     ├── cria passou[][], came_from[][]
    │     ├── loop BFS com fila
    │     └── reconstrói caminho com reverse()
    │
    ├── limpar_tela()
    ├── renderizar_mapa()   → desenha mapa + caminho (pontos '.')
    │
    ├── lê entrada do usuário
    │
    ├── [M] modo manual
    │     ├── tentar_mover()
    │     └── pegar_fruta() → se comeu: nova_fruta() ou fim
    │
    └── [B] modo automático
          ├── for passo in caminho[1..]
          │     ├── calcula cmd (W/A/S/D) comparando posições
          │     ├── tentar_mover(cmd)
          │     ├── renderizar_mapa(caminho restante)
          │     └── pegar_fruta() → se comeu: nova_fruta() ou fim
          └── break ao chegar na fruta
```

---

## 14. Glossário

| Termo | Definição |
|-------|-----------|
| **BFS** | Busca em largura; explora grafo nível a nível; garante caminho mais curto |
| **came_from** | Mapa de predecessores usado para reconstruir o caminho após BFS |
| **Bounds check** | Verificação de que um índice está dentro dos limites válidos do array |
| **`const&`** | Referência constante: acessa o original sem copiar, sem modificar |
| **Default argument** | Valor padrão para parâmetro; permite chamar função sem fornecer aquele argumento |
| **Encapsulamento** | Dados privados acessíveis apenas por métodos controlados da própria classe |
| **Forward declaration** | Protótipo de função antes da implementação; permite que `main` chame funções definidas abaixo |
| **FIFO** | First In, First Out — política da fila: primeiro a entrar é o primeiro a sair |
| **Include guard** | `#ifndef / #define / #endif` — evita que um `.h` seja incluído múltiplas vezes |
| **Member Initializer List** | `: membro(valor)` — inicializa membros antes do corpo do construtor |
| **Off-by-one** | Erro clássico: usar `<=` onde deveria ser `<` (ou vice-versa) em loops/bounds |
| **`operator==`** | Sobrecarga do operador de igualdade; define o que "igual" significa para um tipo |
| **Sentinel** | Valor especial (`{-1,-1}`) usado para marcar ausência ou fim de dados |
| **`size_t`** | Inteiro sem sinal retornado por `.size()`; cuidado ao comparar com `int` |
| **`std::queue`** | Container FIFO da STL; `push`, `front`, `pop` |
| **`std::reverse`** | Inverte um vetor in-place em O(n); requer `<algorithm>` |

---

*Documento gerado como material de estudo — projeto `robo_navegador` (C++17).*