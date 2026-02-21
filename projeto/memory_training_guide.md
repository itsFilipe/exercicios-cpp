# Projeto Movies: Implementação Manual de Gerenciamento de Memória

## 🎯 Objetivo

Transformar o projeto Movies para obrigar a implementação manual de:

- Construtor
- Destrutor
- Construtor de cópia
- Operador de cópia
- Construtor de movimento
- Operador de movimento
- Lista de inicialização
- Ponteiros
- Alocação dinâmica
- Deep copy
- Rule of Five

---

## 🔥 Etapa 1 — Remover `std::vector<Movie>`

### Substituição

**De:**
```cpp
std::vector<Movie> myMovies;
```

**Para:**
```cpp
Movie* movies;
int size;
int capacity;
```

### O que você deverá fazer:

- Controlar memória manualmente
- Fazer realocação manual
- Implementar destrutor
- Implementar deep copy
- Controlar tamanho e capacidade

---

## 🔥 Etapa 2 — Implementar Array Dinâmico Manual

### Implementações necessárias:

- **Construtor padrão**: define capacidade inicial (ex: 10)
- **Método privado `resize()`**: dobra a capacidade quando necessário

### Você será forçado a:

- Usar `new[]`
- Copiar elementos manualmente
- Usar `delete[]`
- Gerenciar memória antiga corretamente

---

## 🔥 Etapa 3 — Forçar Deep Copy na Classe Movies

### Implementar Construtor de Cópia

Você deve copiar:
- `size`
- `capacity`
- Alocar novo array
- Copiar cada `Movie` individualmente

⚠️ **Atenção**: Se fizer errado → shallow copy → double delete.

---

## 🔥 Etapa 4 — Implementar Move Constructor

```cpp
Movies(Movies&& other) noexcept;
```

### O que ele deve fazer:

- Roubar o ponteiro `movies`
- Copiar `size` e `capacity`
- Definir `other.movies = nullptr`
- Definir `other.size = 0`
- Definir `other.capacity = 0`

Aqui você pratica move semantics real.

---

## 🔥 Etapa 5 — Implementar Copy Assignment Operator

```cpp
Movies& operator=(const Movies& other);
```

### Cuidados:

- Verificar auto-atribuição
- Liberar memória atual
- Fazer deep copy
- Retornar `*this`

---

## 🔥 Etapa 6 — Implementar Move Assignment Operator

```cpp
Movies& operator=(Movies&& other) noexcept;
```

### Deve:

- Liberar memória atual
- Roubar recursos
- Invalidar `other`
- Retornar `*this`

---

## 🔥 Etapa 7 — Forçar Uso do Move

### Criar função:

```cpp
Movies create_temp_collection();
```

### No `main`:

```cpp
Movies m = create_temp_collection();
```

### Observar:

- Se o move constructor é chamado
- Como o objeto temporário é transferido

---

## 🔥 Etapa 8 — Modificar Classe Movie para Forçar Deep Copy Real

### Atual:

```cpp
std::string name;
```

### Trocar para:

```cpp
char* name;
```

### Agora você será obrigado a implementar:

- Construtor que aloca memória
- Destrutor
- Construtor de cópia (deep copy)
- Operador de cópia
- Construtor de movimento
- Operador de movimento

Agora você tem ponteiro dentro de objeto.

---

## 🧠 Diagrama Mental

```
Movies
 └── possui ponteiro dinâmico para array de Movie

Movie
 └── possui ponteiro dinâmico para char (nome)
```

### Agora você tem:

- Ponteiro dentro de objeto
- Objeto dentro de array dinâmico
- Array dinâmico dentro de outro objeto

Isso força você a entender:
- Ordem de destruição
- Double delete
- Deep vs shallow copy
- Move semantics real
- Rule of Five completa

---

## 🏆 Objetivo Final

Entender completamente:

- **Ownership**: Quem é responsável por liberar a memória
- **Lifetime de objetos**: Quando objetos são criados e destruídos
- **RAII**: Resource Acquisition Is Initialization
- **Transferência de recursos**: Move semantics
- **Modelo mental do C++**: Como C++ realmente funciona

Depois disso, `std::vector` nunca mais será "mágico".