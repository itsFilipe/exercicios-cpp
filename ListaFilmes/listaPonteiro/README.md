# C++ — Estudo Completo: Gerenciamento de Memória, Construtores, Destrutores e Rule of Five

> Documento de revisão técnica baseado no projeto `Movies/Movie` com alocação dinâmica de memória.

---

## 📁 Estrutura do Projeto

```
main.cpp      → Ponto de entrada, demonstra todos os conceitos
movie.h       → Declaração da classe Movie (objeto simples)
movie.cpp     → Implementação da classe Movie
movies.h      → Declaração da classe Movies (gerencia array dinâmico)
movies.cpp    → Implementação completa com Rule of Five
```

---

## 1. Classes e Responsabilidades

### `Movie` — Objeto de Valor Simples

```cpp
class Movie {
private:
    std::string name;
    std::string rating;
    int watched;
public:
    Movie();
    Movie(std::string name, std::string rating, int watched);
    std::string get_name() const;
    void increment_watched();
};
```

`Movie` é uma classe **simples** — ela não aloca memória dinâmica. Seus membros (`std::string`, `int`) são gerenciados automaticamente pelo compilador. Por isso, ela **não precisa** implementar a Rule of Five manualmente.

---

### `Movies` — Classe com Recurso Dinâmico

```cpp
class Movies {
private:
    Movie* movies;   // Ponteiro para array dinâmico no heap
    int size;        // Quantidade de filmes armazenados
    int capacity;    // Capacidade total alocada
    void resize();
public:
    Movies(int capacity = 10);
    ~Movies();
    Movies(const Movies& other);
    Movies& operator=(const Movies& other);
    Movies(Movies&& other) noexcept;
    Movies& operator=(Movies&& other) noexcept;
    bool add_movie(std::string name, std::string rating, int watched);
};
```

`Movies` possui um **ponteiro bruto** (`Movie* movies`) para um array alocado no heap. Isso exige gerenciamento manual de memória — e é exatamente isso que motiva a **Rule of Five**.

---

## 2. Memória: Stack vs. Heap

### Stack (Pilha)
- Memória automática, gerenciada pelo compilador.
- Criada ao entrar em um escopo `{}`, destruída ao sair.
- Rápida, mas limitada em tamanho.
- Exemplos: variáveis locais, parâmetros de funções.

### Heap (Monte)
- Memória dinâmica, gerenciada **manualmente** pelo programador.
- Alocada com `new`, liberada com `delete`.
- Persiste além do escopo onde foi criada.
- Se não for liberada → **memory leak** (vazamento de memória).

```
Stack                          Heap
┌──────────────────┐          ┌─────────────────────────────────┐
│ Movies a         │          │                                 │
│  movies ─────────┼─────────►│  [Movie][Movie][Movie]...       │
│  size = 1        │          │   (array de 10 posições)        │
│  capacity = 10   │          │                                 │
└──────────────────┘          └─────────────────────────────────┘
```

---

## 3. Ponteiros

Um **ponteiro** armazena um **endereço de memória** — não o valor em si.

```cpp
Movie* movies;         // Declara um ponteiro para Movie
movies = new Movie[10]; // Aponta para um array de 10 Movies no heap
```

### Operadores de ponteiros

| Operador | Significado |
|----------|-------------|
| `*ptr`   | Acessa o valor apontado (derreferência) |
| `ptr->membro` | Acessa membro via ponteiro (equivale a `(*ptr).membro`) |
| `ptr[i]` | Acessa o i-ésimo elemento do array apontado |
| `&var`   | Obtém o endereço de uma variável |

### `new` e `delete`

```cpp
// Aloca UM objeto
Movie* m = new Movie();
delete m;

// Aloca um ARRAY
Movie* arr = new Movie[10];
delete[] arr;   // SEMPRE usar delete[] para arrays!
```

> ⚠️ **Usar `delete` no lugar de `delete[]` em arrays é comportamento indefinido (undefined behavior).**

---

## 4. O Construtor Padrão

```cpp
// movies.h
Movies(int capacity = 10);

// movies.cpp
Movies::Movies(int capacity)
    : size(0), capacity(capacity) {
    movies = new Movie[capacity];
    std::cout << "Construtor\n";
}
```

### O que acontece passo a passo:

1. `Movies a;` → O compilador chama `Movies::Movies(10)` (valor default).
2. A **lista de inicialização** (`: size(0), capacity(capacity)`) inicializa os membros **antes** do corpo do construtor executar.
3. `movies = new Movie[capacity]` → Aloca 10 objetos `Movie` no **heap** e armazena o endereço no ponteiro `movies`.
4. O objeto `a` existe na **stack** e aponta para o array no **heap**.

### Por que usar lista de inicialização e não atribuição no corpo?

```cpp
// Forma com lista de inicialização (preferida)
Movies::Movies(int capacity)
    : size(0), capacity(capacity) { }

// Forma com atribuição no corpo (menos eficiente)
Movies::Movies(int capacity) {
    size = 0;
    this->capacity = capacity; // Precisa de this-> para desambiguar
}
```

Com lista de inicialização, o membro é **inicializado diretamente**. Com atribuição no corpo, o membro é **inicializado com valor padrão e depois reatribuído** — ineficiente para tipos complexos.

---

## 5. O Destrutor

```cpp
Movies::~Movies() {
    delete[] movies;
    std::cout << "Destrutor\n";
}
```

O destrutor é chamado **automaticamente** quando o objeto sai de escopo. Sua responsabilidade é liberar qualquer recurso que o objeto possua.

### Fluxo de destruição:

```
{ // início do escopo (ex: main)
    Movies a;   // Construtor chamado → heap alocado
    // ...
} // fim do escopo
// Destrutor chamado automaticamente → delete[] movies → heap liberado
```

> ⚠️ **Sem o destrutor (ou com destrutor errado), o array no heap nunca seria liberado → memory leak.**

### O Problema do Destrutor Padrão (sem Rule of Five)

Se você **não** implementar o destrutor e as outras funções especiais, o compilador gera versões padrão que fazem **cópia rasa (shallow copy)**:

```
Original (a):   movies ──────────────────► [Batman]
                                               ↑
Cópia (b):      movies ──────────────────────┘  (mesmo endereço!)
```

Quando `b` for destruído: `delete[] movies` → libera o array.  
Quando `a` for destruído: `delete[] movies` → **double free** → crash ou comportamento indefinido!

---

## 6. Rule of Five

> Se uma classe precisa implementar **qualquer um** dos seguintes, provavelmente precisa implementar **todos os cinco**:
> 1. Destrutor
> 2. Construtor de Cópia
> 3. Operador de Atribuição por Cópia
> 4. Construtor de Movimento
> 5. Operador de Atribuição por Movimento

---

### 6.1 Construtor de Cópia

```cpp
Movies::Movies(const Movies& other)
    : size(other.size), capacity(other.capacity) {

    movies = new Movie[capacity];           // Nova alocação no heap!

    for (int i = 0; i < size; i++)
        movies[i] = other.movies[i];       // Copia elemento por elemento

    std::cout << "Copy constructor\n";
}
```

**Quando é chamado:**
```cpp
Movies b = a;   // Inicialização a partir de outro objeto → Copy Constructor
```

**O que faz:**
- Aloca um **novo** bloco de memória no heap (tamanho igual ao original).
- Copia cada elemento individualmente → **deep copy (cópia profunda)**.

**Resultado:**
```
a: movies ──► [Batman]   (heap bloco 1)
b: movies ──► [Batman]   (heap bloco 2 — independente!)
```

**Parâmetro `const Movies& other`:**
- `&` → passagem por referência (evita cópia recursiva infinita!).
- `const` → garante que o original não será modificado.

---

### 6.2 Operador de Atribuição por Cópia

```cpp
Movies& Movies::operator=(const Movies& other) {
    std::cout << "Copy assignment\n";

    if (this == &other)       // Autoatribuição: a = a; → retorna sem fazer nada
        return *this;

    delete[] movies;          // Libera memória antiga!

    size = other.size;
    capacity = other.capacity;

    movies = new Movie[capacity];

    for (int i = 0; i < size; i++)
        movies[i] = other.movies[i];

    return *this;
}
```

**Quando é chamado:**
```cpp
Movies c;    // Construtor padrão
c = a;       // Objeto JÁ EXISTENTE recebe novo valor → Copy Assignment
```

**Diferença do Construtor de Cópia:**
- O Construtor de Cópia cria um objeto **novo** a partir de outro.
- O Operador de Atribuição modifica um objeto **já existente** — por isso precisa liberar a memória antiga primeiro (`delete[] movies`).

**Por que verificar autoatribuição?**
```cpp
c = c; // Sem verificação: delete[] movies libera o próprio array,
       // depois tenta copiar de memória inválida → crash!
```

**Retorno `Movies&`:**
- Retornar por referência permite encadeamento: `a = b = c;`
- `return *this` retorna o próprio objeto (derreferência do ponteiro `this`).

---

### 6.3 Construtor de Movimento

```cpp
Movies::Movies(Movies&& other) noexcept
    : movies(other.movies),
      size(other.size),
      capacity(other.capacity) {

    other.movies = nullptr;   // "Rouba" o recurso e invalida o original
    other.size = 0;
    other.capacity = 0;

    std::cout << "Move constructor\n";
}
```

**Quando é chamado:**
```cpp
Movies d = createCollection(); // Retorno de função → rvalue → Move Constructor
```

**O que é um rvalue?**
- **lvalue**: tem nome, tem endereço, pode aparecer à esquerda de `=`. Ex: `a`, `b`.
- **rvalue**: temporário, sem nome persistente, não pode aparecer à esquerda de `=`. Ex: o retorno de `createCollection()`.

**`&&` — Referência de rvalue:**
- `const Movies& other` aceita qualquer coisa (lvalue ou rvalue).
- `Movies&& other` aceita **apenas** rvalues (temporários).

**O que o Move Constructor faz:**
1. **"Rouba"** o ponteiro do objeto temporário — sem alocar nova memória!
2. **Invalida** o objeto original (`nullptr`, `0`) para evitar que seu destrutor libere o recurso roubado.

**Por que é mais eficiente que a cópia?**
```
Copy Constructor:  aloca novo heap (lento) + copia cada elemento (lento)
Move Constructor:  apenas copia o ponteiro (rapidíssimo) — O(1) vs O(n)
```

**`noexcept`:**
- Indica que a função não lança exceções.
- Essencial para que `std::vector` e outros containers usem o Move em vez da cópia ao redimensionar.

---

### 6.4 Operador de Atribuição por Movimento

```cpp
Movies& Movies::operator=(Movies&& other) noexcept {
    std::cout << "Move assignment\n";

    if (this == &other)
        return *this;

    delete[] movies;          // Libera o recurso atual

    movies = other.movies;    // Rouba o ponteiro
    size = other.size;
    capacity = other.capacity;

    other.movies = nullptr;   // Invalida o original
    other.size = 0;
    other.capacity = 0;

    return *this;
}
```

**Quando é chamado:**
```cpp
Movies e;
e = createCollection(); // e já existe, recebe um temporário → Move Assignment
```

**Diferença do Move Constructor:**
- Move Constructor: cria um objeto **novo** movendo de outro.
- Move Assignment: objeto **já existe**, precisa liberar o recurso atual antes de roubar o novo.

---

## 7. Método `resize()` — Expansão Dinâmica

```cpp
void Movies::resize() {
    capacity *= 2;

    Movie* newArray = new Movie[capacity];

    for (int i = 0; i < size; i++)
        newArray[i] = movies[i];

    delete[] movies;
    movies = newArray;
}
```

**Estratégia de dobrar a capacidade:**
- Dobrar a capacidade a cada resize resulta em complexidade **amortizada O(1)** para inserções — a mesma usada por `std::vector`.
- Se aumentasse de 1 em 1, cada inserção poderia exigir realocação → O(n²) no total.

**Passo a passo:**
```
1. capacity = 10 → capacity = 20
2. Aloca novo array de 20 no heap
3. Copia os 10 elementos existentes
4. delete[] movies → libera o array antigo
5. movies = newArray → aponta para o novo array
```

---

## 8. Método `add_movie()`

```cpp
bool Movies::add_movie(std::string name, std::string rating, int watched) {
    for (int i = 0; i < size; i++) {
        if (movies[i].get_name() == name)
            return false;             // Duplicata encontrada
    }

    if (size == capacity)
        resize();                     // Expande se necessário

    movies[size] = Movie(name, rating, watched);  // Cria e armazena
    size++;

    return true;
}
```

- `Movie(name, rating, watched)` → chama o construtor parametrizado de `Movie`.
- `movies[size] = ...` → usa o operador de atribuição de `Movie` (gerado pelo compilador, pois `Movie` não gerencia heap).

---

## 9. Fluxo Completo do `main()`

```cpp
int main() {
    Movies a;                          // (1) Construtor
    a.add_movie("Batman", "PG", 3);

    Movies b = a;                      // (2) Copy Constructor

    Movies c;                          // (3) Construtor
    c = a;                             // (4) Copy Assignment

    Movies d = createCollection();     // (5) Construtor (dentro de createCollection)
                                       // (6) Move Constructor (retorno da função)
                                       // (7) Destrutor (do temporário — já invalidado)

    Movies e;                          // (8) Construtor
    e = createCollection();            // (9) Construtor (dentro de createCollection)
                                       // (10) Move Assignment
                                       // (11) Destrutor (do temporário)

    return 0;
    // Destrutores de e, d, c, b, a — nessa ordem (LIFO)
}
```

### Saída esperada no console:

```
Construtor           ← a
Construtor           ← b (interno do copy)... na verdade: Copy constructor
Copy constructor     ← b = a
Construtor           ← c
Copy assignment      ← c = a
Construtor           ← temp (dentro de createCollection)
Move constructor     ← d = createCollection()
Destrutor            ← temp (já nullptr, sem efeito real no heap)
Construtor           ← e
Construtor           ← temp (dentro de createCollection)
Move assignment      ← e = createCollection()
Destrutor            ← temp
Destrutor            ← e
Destrutor            ← d
Destrutor            ← c
Destrutor            ← b
Destrutor            ← a
```

> **Nota:** O compilador moderno pode aplicar **RVO (Return Value Optimization)** e eliminar o Move Constructor em alguns casos, construindo o objeto diretamente no destino. O comportamento exato depende do compilador e nível de otimização.

---

## 10. Tabela Resumo — Quando Cada Função Especial é Chamada

| Situação | Função Chamada |
|----------|---------------|
| `Movies a;` | Construtor padrão |
| `Movies b = a;` | Construtor de cópia |
| `Movies b(a);` | Construtor de cópia |
| `c = a;` (c já existe) | Operador de atribuição por cópia |
| `Movies d = funcao();` | Construtor de movimento (ou RVO) |
| `e = funcao();` (e já existe) | Operador de atribuição por movimento |
| Fim de escopo / `delete` | Destrutor |

---

## 11. Armadilhas Comuns

### Double Free
```cpp
// Sem Rule of Five: a e b apontam para o mesmo heap
Movies b = a;
// Ao fim do escopo: delete[] chamado duas vezes → crash
```

### Memory Leak
```cpp
// Sem destrutor: o heap nunca é liberado
// O SO recupera ao encerrar o processo, mas é má prática
```

### Dangling Pointer (Ponteiro Pendurado)
```cpp
Movie* ptr = &movies[0];
resize();           // delete[] movies interno → ptr aponta para memória inválida!
ptr->get_name();    // Undefined behavior!
```

### Self-Assignment sem Verificação
```cpp
c = c;
// Sem "if (this == &other)": delete[] movies libera o próprio array
// depois tenta copiar de memória já liberada → undefined behavior
```

---

## 12. Glossário Rápido

| Termo | Definição |
|-------|-----------|
| **Stack** | Memória automática, gerenciada pelo compilador |
| **Heap** | Memória dinâmica, gerenciada com `new`/`delete` |
| **Ponteiro** | Variável que armazena um endereço de memória |
| **Deep Copy** | Cópia que aloca novo recurso e duplica o conteúdo |
| **Shallow Copy** | Cópia que apenas copia o ponteiro (perigoso!) |
| **lvalue** | Expressão com identidade/endereço persistente |
| **rvalue** | Temporário, sem identidade persistente |
| **`&&`** | Referência de rvalue — vincula a temporários |
| **`noexcept`** | Garante que a função não lança exceções |
| **RVO** | Return Value Optimization — compilador elimina cópias desnecessárias |
| **Rule of Five** | Se implementar um dos 5 especiais, implemente todos |
| **`this`** | Ponteiro implícito para o objeto atual |
| **`*this`** | Derreferência de `this` — o próprio objeto |

---

*Documento gerado como material de estudo para revisão dos fundamentos de C++ com gerenciamento manual de memória.*