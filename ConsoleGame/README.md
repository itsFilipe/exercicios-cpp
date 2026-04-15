# RPG Terminal — C++ Study Project

A turn-based console RPG built to practice and consolidate core C++ concepts. This document explains every significant language feature used in the project, *why* it exists, and *why it matters* in real C++ code.

---

## Table of Contents

1. [Project Overview](#1-project-overview)
2. [Classes and Encapsulation](#2-classes-and-encapsulation)
3. [Inheritance](#3-inheritance)
4. [Polymorphism and Virtual Functions](#4-polymorphism-and-virtual-functions)
5. [Abstract Classes and Pure Virtual Functions](#5-abstract-classes-and-pure-virtual-functions)
6. [The Virtual Destructor Rule](#6-the-virtual-destructor-rule)
7. [The `override` Keyword](#7-the-override-keyword)
8. [Smart Pointers and RAII](#8-smart-pointers-and-raii)
9. [Move Semantics](#9-move-semantics)
10. [`dynamic_cast` and Runtime Type Information](#10-dynamic_cast-and-runtime-type-information)
11. [`static_cast`](#11-static_cast)
12. [Lambdas and `std::function`](#12-lambdas-and-stdfunction)
13. [Namespaces](#13-namespaces)
14. [`enum class`](#14-enum-class)
15. [Const Correctness](#15-const-correctness)
16. [STL Containers](#16-stl-containers)
17. [File I/O with fstream](#17-file-io-with-fstream)
18. [Header Guards](#18-header-guards)
19. [Forward Declarations](#19-forward-declarations)
20. [The `inline` Keyword in Headers](#20-the-inline-keyword-in-headers)
21. [`static_cast` vs C-style Cast](#21-static_cast-vs-c-style-cast)

---

## 1. Project Overview

```
build/program        — compiled executable
src/                 — all .cpp implementation files
include/             — all .h header files
savegame.txt         — plain-text save file (created in build/)
```

**Build:**
```bash
cmake -S . -B build
cmake --build build
./build/program
```

The project is built with `-fsanitize=address` (AddressSanitizer) and `-g` (debug symbols), which catches memory errors like use-after-free and buffer overflows at runtime during development.

---

## 2. Classes and Encapsulation

**File:** `include/Personagem.h`, `src/Personagem.cpp`

A **class** bundles data (attributes) and behavior (methods) into a single unit. **Encapsulation** means controlling which parts of that bundle are visible to the outside world.

```cpp
class Personagem {
protected:        // accessible to this class AND derived classes
    std::string nome;
    int vida;
    int vidaMaxima;
    int danoBase;

public:           // accessible to everyone
    void atacar(Personagem& alvo);
    bool estaVivo() const;
};
```

The three access levels and why they matter:

| Specifier | Who can access | Used for |
|-----------|---------------|----------|
| `private` | Only this class | Internal state that nothing should touch directly |
| `protected` | This class + subclasses | State that child classes need to read/modify (e.g., `vida`, `danoBase`) |
| `public` | Everyone | The interface — what callers are allowed to do |

**Why it matters:** If `vida` were `public`, any code anywhere in the program could set `heroi.vida = 999999` with no validation. Encapsulation forces all mutations to go through methods (`receberDano`, `receberCura`) where invariants can be checked.

---

## 3. Inheritance

**Files:** `Heroi`, `Inimigo`, `Vampiro`, `Orc`, `Goblin`

Inheritance lets a new class (derived/child) reuse and extend the code of an existing class (base/parent).

```cpp
// Heroi IS-A Personagem, with extra attributes (mana, ouro, inventario)
class Heroi : public Personagem {
private:
    int mana;
    int manaMaxima;
    int ouro;
    std::vector<std::unique_ptr<Item>> inventario;
};

// Inimigo IS-A Personagem — thin wrapper, just a different name for now
class Inimigo : public Personagem {};

// Orc IS-A Inimigo IS-A Personagem — multi-level inheritance
class Orc : public Inimigo {};
```

**The IS-A rule:** Use `public` inheritance only when the derived class genuinely *is a* specialization of the base. A `Heroi` is always a `Personagem`. An `Orc` is always an `Inimigo`. This is what makes polymorphism (Section 4) work correctly.

**Constructor chaining** — derived class constructors must initialize their base:

```cpp
Heroi::Heroi(std::string n, int v, int d, int m)
    : Personagem(n, v, d),   // calls Personagem's constructor first
      mana(m), manaMaxima(m), ouro(0) {}
```

The member initializer list (`: Personagem(n,v,d), mana(m)...`) runs *before* the constructor body. This is the correct and efficient way to initialize members — assigning inside the body would default-construct them first and then overwrite.

---

## 4. Polymorphism and Virtual Functions

**Files:** `Personagem.h`, `Vampiro.cpp`, `Orc.cpp`, `Goblin.cpp`

Polymorphism allows code to call a method on a base-class pointer/reference and get the behavior of the *actual* derived type at runtime.

```cpp
// In main.cpp — vilao is a base-class pointer to any enemy type
std::unique_ptr<Inimigo> vilao;
vilao = std::make_unique<Vampiro>(round);  // or Orc, or Goblin

// This calls the right atacar() for whichever enemy is stored
vilao->atacar(heroi);
```

Without `virtual`, C++ uses **static dispatch** — it looks at the declared type (`Inimigo`) and calls `Inimigo::atacar` regardless of what object is actually there. With `virtual`, C++ uses **dynamic dispatch** — it looks at the actual runtime type and calls the right override.

```cpp
// In Personagem.h — marking the method as virtual enables dynamic dispatch
virtual void atacar(Personagem& alvo);

// In Vampiro.cpp — this override runs when vilao is a Vampiro
void Vampiro::atacar(Personagem& alvo) {
    int dano = ...;
    alvo.receberDano(dano);
    vida += dano / 3;  // life-steal — unique behavior!
}
```

**How it works under the hood (vtable):** When a class has at least one `virtual` method, the compiler creates a **virtual table (vtable)** — a table of function pointers, one per virtual method. Each object carries a hidden pointer (`vptr`) to its class's vtable. When you call `vilao->atacar(heroi)`, C++ follows the `vptr` to the vtable and calls whatever function pointer is there. `Vampiro` objects point to `Vampiro::atacar`; `Orc` objects point to `Orc::atacar`.

**Why it matters:** Without polymorphism, the game loop would need a chain of `if (isVampiro) ... else if (isOrc) ...` for every enemy type. With virtual functions, you just call `vilao->atacar(heroi)` and the right behavior happens automatically, regardless of how many enemy types you add.

---

## 5. Abstract Classes and Pure Virtual Functions

**File:** `include/Item.h`

A **pure virtual function** is declared with `= 0`. A class that has at least one pure virtual function is **abstract** — it cannot be instantiated directly.

```cpp
class Item {
public:
    virtual void aplicar(Personagem* alvo) = 0;  // pure virtual
    virtual bool esOfensivo() const { return false; }  // regular virtual with default
};
```

`Item` is abstract because every item must define *how* it applies itself, but the base class has no idea what "applying an item" means in the abstract. `PocaoVida` restores HP; `PocaoMana` restores MP; `VenenoFrasco` poisons the target. Each subclass provides its own `aplicar`.

```cpp
// This would be a compile error — you cannot create an abstract object
Item item(...);  // ERROR: Item::aplicar is pure virtual

// This works — PocaoVida provides a concrete aplicar()
std::unique_ptr<Item> item = std::make_unique<PocaoVida>(...);
```

**Why it matters:** Abstract classes define a **contract** (an interface). Any class that inherits from `Item` is *forced* by the compiler to implement `aplicar`. You cannot accidentally forget it. This is one of the most important patterns in C++ for building extensible systems.

---

## 6. The Virtual Destructor Rule

**File:** `include/Personagem.h`, `include/Item.h`

```cpp
class Personagem {
public:
    virtual ~Personagem() {}  // virtual destructor — MANDATORY
};
```

**Why this rule exists:** When you delete an object through a base-class pointer, C++ needs to know which destructor to call. Without `virtual`, it always calls the base destructor — leaking any resources the derived class owns.

```cpp
std::unique_ptr<Inimigo> vilao = std::make_unique<Vampiro>(round);
// When vilao goes out of scope, ~Inimigo() would be called — NOT ~Vampiro()
// If Vampiro had its own heap allocations, they would leak
// With virtual ~Inimigo(), C++ finds and calls ~Vampiro() first, then ~Inimigo()
```

**The rule:** *If a class has any virtual functions, it must have a virtual destructor.*

This is true even if the destructor body is empty — the `virtual` keyword is what matters. `unique_ptr<Inimigo>` stores a `Vampiro`, and when it cleans up, it must reach `Vampiro`'s destructor through the vtable.

---

## 7. The `override` Keyword

**Files:** `Vampiro.h`, `Orc.h`, `Goblin.h`, `Heroi.h`

```cpp
class Vampiro : public Inimigo {
public:
    void atacar(Personagem& alvo) override;  // <--- override keyword
};
```

`override` tells the compiler: "I intend this to override a virtual function in the base class. If it doesn't match any base virtual function exactly, it is an error."

**Why it matters — without `override`:**
```cpp
// Suppose you make a typo
void Vampiro::Atacar(Personagem& alvo) { ... }  // capital A — typo!
// Without override: compiles silently. Vampiro just adds a new unrelated method.
// The base class atacar() still runs. Your life-steal never happens.

// With override:
void Vampiro::Atacar(Personagem& alvo) override { ... }  // COMPILE ERROR
// "Atacar does not override a base class virtual function"
```

`override` turns a silent logical bug into a compile-time error. Always use it when overriding.

---

## 8. Smart Pointers and RAII

**Files:** `Heroi.h`, `main.cpp`, all item creation sites

**RAII (Resource Acquisition Is Initialization)** is the principle that resource lifetime should be tied to object lifetime. You acquire a resource in the constructor; you release it in the destructor. When the object goes out of scope, the destructor runs automatically.

`std::unique_ptr<T>` is the RAII wrapper for heap-allocated objects:

```cpp
// Raw pointer — manual, error-prone
Item* item = new PocaoVida(...);
heroi.usarItem(item);
delete item;  // easy to forget, easy to double-delete, fails on exceptions

// unique_ptr — automatic
std::unique_ptr<Item> item = std::make_unique<PocaoVida>(...);
heroi.adicionarItem(std::move(item));
// No delete needed — the destructor runs automatically when the pointer goes out of scope
```

**Ownership model:** `unique_ptr` means *exactly one owner*. The pointer cannot be copied, only moved. This makes ownership explicit in the type system:

```cpp
// Heroi owns all items in its inventory
std::vector<std::unique_ptr<Item>> inventario;

// When Heroi is destroyed, its destructor runs,
// which destroys the vector, which destroys each unique_ptr,
// which calls delete on each Item — all automatically, with zero manual cleanup.
```

**Why it matters:** `unique_ptr` eliminates entire categories of bugs: memory leaks, use-after-free, double-free. In modern C++, you should almost never write `new`/`delete` manually.

---

## 9. Move Semantics

**Files:** `src/Heroi.cpp` (`adicionarItem`, `usarItem`), `main.cpp`

`unique_ptr` cannot be *copied* (that would give two owners, breaking the unique-ownership guarantee). It can only be *moved*. Moving transfers ownership from one pointer to another, leaving the source as `nullptr`.

```cpp
void Heroi::adicionarItem(std::unique_ptr<Item> novoItem) {
    // Read the name BEFORE moving — after the move, novoItem is nullptr
    std::string nome = novoItem->getNome();

    // std::move casts novoItem to an rvalue reference, enabling the move constructor
    inventario.push_back(std::move(novoItem));

    std::cout << "Você pegou: " << nome << "\n";
}
```

When using an item:
```cpp
void Heroi::usarItem(int indice, Personagem* alvo) {
    // Move the unique_ptr out of the vector — we now own it locally
    std::unique_ptr<Item> item = std::move(inventario[indice]);
    inventario.erase(inventario.begin() + indice);
    item->aplicar(alvo);
    // item goes out of scope here — destructor runs, memory freed
}
```

**Why it matters:** Move semantics allow expensive resources (heap-allocated objects, file handles, etc.) to be transferred between scopes with zero cost. `std::move` does not actually move data — it just changes the *type* of the expression to an rvalue reference, which enables the move constructor or move assignment to be selected over the copy constructor.

---

## 10. `dynamic_cast` and Runtime Type Information

**File:** `include/PocaoMana.h`

```cpp
void PocaoMana::aplicar(Personagem* alvo) override {
    Heroi* h = dynamic_cast<Heroi*>(alvo);  // try to downcast
    if (h) {
        h->restaurarMana(recarga);  // only Heroes have mana
    } else {
        std::cout << "Apenas herois podem usar isso!\n";
    }
}
```

`dynamic_cast` performs a **safe downcast** at runtime. If `alvo` really is a `Heroi` (or a class that derives from `Heroi`), the cast succeeds and returns a valid pointer. If not, it returns `nullptr`. The `if (h)` check handles both cases safely.

**Why `dynamic_cast` and not a C-style cast?** A C-style cast `(Heroi*)alvo` always "succeeds" — it just reinterprets the bits, which is undefined behavior if the object is not actually a `Heroi`. `dynamic_cast` is safe because it checks the vtable at runtime.

**Why it matters:** `dynamic_cast` is the tool for situations where you genuinely need to know the runtime type. However, needing it often is a design smell — it usually means the base class interface is missing something. Here it is justified because mana is a Hero-specific concept that the `Personagem` base has no reason to know about.

---

## 11. `static_cast`

**File:** `src/main.cpp`

```cpp
Personagem* alvo = itemPtr->esOfensivo()
    ? static_cast<Personagem*>(vilao.get())   // Inimigo* → Personagem*
    : static_cast<Personagem*>(&heroi);        // Heroi*   → Personagem*
```

`static_cast` performs compile-time type conversions. Here it is used to explicitly convert two different derived-class pointers (`Inimigo*` and `Heroi*`) to the same base-class type (`Personagem*`), satisfying the ternary operator's requirement that both branches have the same type.

This is an **upcast** (derived → base), which is always safe. `static_cast` makes the intent explicit and visible in code review, unlike the implicit conversion that would happen if the types matched already.

---

## 12. Lambdas and `std::function`

**File:** `src/main.cpp` (loot chest system)

A **lambda** is an anonymous function defined inline, right where it is used.

```cpp
struct LootBau {
    std::string nome;
    std::function<void()> acao;  // holds any callable that takes no args and returns void
};

std::vector<LootBau> possiveisItens = {
    {"Pocao Grande", [&]() {
        // [&] — capture everything in scope by reference
        // heroi is captured here — this lambda "remembers" the local heroi variable
        heroi.adicionarItem(criarItem(2));
    }},
    {"Frasco de Veneno", [&]() {
        heroi.adicionarItem(criarItem(4));
    }},
};

// Later, picking a random loot entry and executing it:
possiveisItens[sorteio].acao();
```

**Capture modes:**
- `[&]` — capture all local variables by reference (the lambda holds a reference, not a copy)
- `[=]` — capture all by value (a copy is made at lambda creation time)
- `[&heroi]` — capture only `heroi` by reference

**`std::function<void()>`** is a type-erased wrapper that can hold *any* callable — a lambda, a regular function pointer, a functor — as long as the signature matches. This is what allows the `LootBau` struct to store different lambdas that each do different things, even though they all have the same type from the struct's perspective.

**Why it matters:** Lambdas replace the old pattern of writing a separate named function for every small callback. `std::function` makes callables first-class values that can be stored in containers, passed as arguments, and called later — enabling powerful patterns like the loot chest system here.

---

## 13. Namespaces

**File:** `include/SaveManager.h`, `src/SaveManager.cpp`

```cpp
namespace SaveManager {
    void salvar(const Heroi& h, int round);
    bool carregar(Heroi& h, int& round);
}

// Usage in main.cpp:
SaveManager::salvar(heroi, round);
SaveManager::carregar(heroi, round);
```

A **namespace** groups related names and prevents collisions. `salvar` is a very generic name — if another library also defines a `salvar` function, they would conflict without namespaces. `SaveManager::salvar` is unambiguous.

In this project, `SaveManager` is used instead of a class with `static` methods because there is no state to encapsulate — it is a pure set of functions that operate on `Heroi`. A namespace communicates that intent more clearly.

---

## 14. `enum class`

**File:** `include/StatusEffect.h`

```cpp
struct StatusEffect {
    enum class Tipo { VENENO, ATORDOADO };
    Tipo tipo;
    int duracao;
    int valor;
};
```

`enum class` (a **scoped enum**) is the modern C++ replacement for plain `enum`.

**Plain `enum` problems:**
```cpp
enum Tipo { VENENO, ATORDOADO };
enum Cor  { VERMELHO, VERDE };

// This compiles — comparing completely unrelated enums!
if (VENENO == VERMELHO) { ... }

// Enumerators leak into the surrounding scope:
int x = VENENO;  // works, even outside any struct
```

**`enum class` fixes both:**
```cpp
enum class Tipo { VENENO, ATORDOADO };
enum class Cor  { VERMELHO, VERDE };

if (Tipo::VENENO == Cor::VERMELHO) { ... }  // COMPILE ERROR — different types
int x = Tipo::VENENO;                        // COMPILE ERROR — no implicit int conversion
int x = static_cast<int>(Tipo::VENENO);     // OK — explicit cast required
```

**Why it matters:** `enum class` prevents accidental comparisons between unrelated enum types and prevents enumerators from polluting the enclosing scope. Always prefer `enum class` over plain `enum` in modern C++.

---

## 15. Const Correctness

**Files:** throughout, especially `Personagem.h`, `Heroi.h`

`const` on a method means the method promises not to modify the object:

```cpp
// These methods do not change the Personagem — they just read
std::string getNome() const;
int getVida() const;
bool estaVivo() const;
bool estaAtordoado() const;
```

`const` on a parameter means the function will not modify what was passed:
```cpp
void SaveManager::salvar(const Heroi& h, int round);
std::string Heroi::serializarStats() const;
```

**Why it matters:**

1. **Correctness:** The compiler enforces the promise. If a `const` method accidentally tries to modify a member, it is a compile error — not a silent bug.

2. **`const` references:** Passing `const Heroi& h` instead of `Heroi h` avoids copying the entire object (which includes its inventory vector) while also preventing the callee from modifying it. This is the standard idiom for passing objects that are large or expensive to copy.

3. **Const propagation:** A `const Heroi` object can only call `const` methods. If you forget `const` on a getter, you cannot call it on a const object. This forces you to think carefully about what "reading" vs "modifying" means for every method.

---

## 16. STL Containers

**Files:** `Heroi.h` (vector), `Personagem.h` (vector), `main.cpp` (vector)

The Standard Template Library provides generic, reusable containers:

```cpp
// Dynamic array — random access in O(1), append in amortized O(1)
std::vector<std::unique_ptr<Item>> inventario;
std::vector<StatusEffect> efeitos;
std::vector<LootBau> possiveisItens;
```

**`std::vector` key operations used here:**
```cpp
inventario.push_back(std::move(item));          // append
inventario.erase(inventario.begin() + indice);  // remove at index
inventario.clear();                             // remove all
inventario.size();                              // number of elements
inventario[i]->getNome();                       // random access
inventario.empty();                             // is it empty?

// Range-based for — iterates without manual index management
for (const auto& ef : efeitos) { ... }
```

**`auto` in range-based for:** `auto& ef` asks the compiler to deduce the type of `ef` from the container's element type. `const auto&` means "a const reference to each element" — no copy, no modification.

**Why it matters:** `std::vector` manages its own heap memory, grows automatically, and frees its contents when it is destroyed. Combined with `unique_ptr`, the vector's destruction chain automatically frees every item in the inventory with no manual cleanup.

---

## 17. File I/O with fstream

**File:** `src/SaveManager.cpp`

```cpp
// Write to file
std::ofstream arquivo("savegame.txt");
if (arquivo.is_open()) {
    arquivo << h.getNome() << "\n";
    arquivo << h.serializarStats() << "\n";
}  // arquivo's destructor closes the file automatically (RAII)

// Read from file
std::ifstream arquivo("savegame.txt");
if (arquivo.is_open()) {
    std::string nome;
    std::getline(arquivo, nome);  // reads a whole line
    arquivo >> v >> vm >> d;      // reads space-separated values
}
```

`std::ofstream` and `std::ifstream` are RAII wrappers around file handles. The file is closed automatically when the object goes out of scope — even if an exception is thrown.

**`serializarStats()` uses `std::stringstream`:**
```cpp
std::string Heroi::serializarStats() const {
    std::stringstream ss;
    ss << vida << " " << vidaMaxima << " " << getDano() << " "
       << mana << " " << manaMaxima << " " << ouro;
    return ss.str();
}
```

`std::stringstream` lets you build strings with the familiar `<<` syntax, then extract the result with `.str()`. This is the standard way to convert numbers to strings (and back) in C++ before `std::to_string`.

---

## 18. Header Guards

**Every header file in this project**

```cpp
#ifndef PERSONAGEM_H
#define PERSONAGEM_H

// ... class definition ...

#endif
```

Header guards prevent the same header from being included more than once in a single translation unit. Without them, if `main.cpp` included both `Heroi.h` and `PocaoMana.h`, and both of those included `Personagem.h`, the class `Personagem` would be defined twice — a compile error.

The guard works like this:
1. First time `Personagem.h` is included: `PERSONAGEM_H` is not defined, so the `#ifndef` is true. The compiler processes the file and defines `PERSONAGEM_H`.
2. Second time: `PERSONAGEM_H` is already defined, so `#ifndef` is false — the entire file is skipped.

The name of the macro must be unique across the entire project. Convention: `FILENAME_H` in all caps.

---

## 19. Forward Declarations

**File:** `include/Heroi.h`

```cpp
// Forward declaration — tells the compiler "Item is a class, I'll define it later"
class Item;

class Heroi : public Personagem {
private:
    std::vector<std::unique_ptr<Item>> inventario;  // OK — pointer/reference only
public:
    void adicionarItem(std::unique_ptr<Item> novoItem);  // OK — pointer/reference only
};
```

A forward declaration lets you use a type name in a header without including the full definition. This breaks circular include dependencies and speeds up compilation.

**When a forward declaration is enough:**
- Declaring a pointer or reference to the type (`Item*`, `unique_ptr<Item>`, `Item&`)
- Declaring a function that takes or returns the type by pointer or reference

**When you need the full `#include`:**
- Creating an object of the type by value (the compiler needs to know its size)
- Calling methods on the object
- Inheriting from the type

In `Heroi.cpp`, the full `#include "Item.h"` is needed because `usarItem` calls `item->aplicar(...)`.

---

## 20. The `inline` Keyword in Headers

**File:** `include/ItemFactory.h`

```cpp
inline std::unique_ptr<Item> criarItem(int id) {
    switch (id) {
        case 1: return std::make_unique<PocaoVida>(...);
        // ...
    }
}
```

Normally, if a function is defined (not just declared) in a header, and that header is included in multiple `.cpp` files, the linker sees multiple definitions of the same function — a linker error (ODR violation).

`inline` tells the linker: "if you see multiple definitions of this function across translation units, they are all identical — keep only one." This allows function definitions to live in headers, which is the standard approach for template code and small utility functions.

Note: `inline` does *not* guarantee the function will be inlined by the optimizer (expanded at the call site). That is a separate optimization decision. The primary meaning of `inline` today is to relax the One Definition Rule.

---

## 21. `static_cast` vs C-style Cast

Throughout the project, casts are written as `static_cast<T>(x)` rather than `(T)x`. This is a deliberate style choice.

C++ provides four named cast operators, each with a specific purpose:

| Cast | Purpose |
|------|---------|
| `static_cast<T>` | Compile-time checked conversions (upcasts, downcasts with no RTTI, arithmetic) |
| `dynamic_cast<T>` | Runtime-checked downcast through inheritance hierarchy |
| `const_cast<T>` | Add or remove `const` qualifier |
| `reinterpret_cast<T>` | Reinterpret raw bit pattern as a different type (dangerous) |

The C-style cast `(T)x` tries each of these in order and applies the first one that works — including `reinterpret_cast`, which is almost never what you want. It also cannot be searched for with grep.

Named casts are:
- **Grep-able** — `git grep static_cast` finds every cast in the codebase instantly
- **Self-documenting** — the cast name communicates intent
- **Safer** — each named cast only does what it says; you cannot accidentally use `reinterpret_cast` when you meant `static_cast`

---

## Putting It All Together

This project demonstrates how C++ concepts compose:

- **Inheritance + virtual functions** → one `vilao->atacar(heroi)` call dispatches to `Vampiro`, `Orc`, or `Goblin` behavior automatically
- **Abstract class + pure virtual** → `Item` enforces a contract; any new item *must* implement `aplicar`
- **`unique_ptr` + move semantics** → items transfer ownership cleanly through `adicionarItem` → `usarItem` without any manual `delete`
- **RAII** → file handles (`fstream`), heap memory (`unique_ptr`), and containers (`vector`) all clean themselves up when they go out of scope
- **Lambdas + `std::function`** → loot chest entries carry their own behavior as data, stored in a vector and called later
- **`enum class`** → status effect types are type-safe; comparing `StatusEffect::Tipo::VENENO` to an unrelated enum is a compile error
- **`const` correctness** → `serializarStats() const`, `getNome() const`, `estaVivo() const` propagate read-only guarantees through the call stack
- **`ItemFactory`** → a single function centralizes item construction, so save/load and loot always stay in sync

Each concept solves a specific class of problem. Together, they make the code safer, more expressive, and easier to extend.
