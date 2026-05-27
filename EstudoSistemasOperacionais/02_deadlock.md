# 💀 Deadlock
> **Demo:** `make run2` | **Teoria:** este arquivo

---
## 📖 O que é?
Deadlock é quando **dois ou mais processos ficam bloqueados para sempre**, cada um esperando que o outro libere um recurso — o que nunca acontece. Sem intervenção externa, o sistema trava naquele grupo de processos indefinidamente.

---
## 📚 As 4 Condições de Coffman (todas necessárias)
| # | Condição | Definição |
|---|---|---|
| 1 | **Exclusão Mútua** | Recurso pertence a apenas 1 processo por vez |
| 2 | **Manter e Esperar** | Processo segura 1 recurso e pede outro |
| 3 | **Não-Preempção** | SO não pode tirar o recurso à força |
| 4 | **Espera Circular** | P1→P2→P3→P1: cadeia fechada de espera |

> Eliminar **qualquer uma** das 4 previne o deadlock.

## 📚 Exemplo Clássico
```
P1: LOCK(tabela_clientes) → espera LOCK(tabela_pedidos)
P2: LOCK(tabela_pedidos)  → espera LOCK(tabela_clientes)
```
Ambos bloqueados. Nenhum avança. Para sempre.

## 📚 Soluções
**Fix 1 — Ordenação de Locks:** sempre adquirir A antes de B.
```cpp
// Todos seguem: A primeiro, depois B. Sem espera circular.
recurso_A.lock(); recurso_B.lock(); /* ... */ recurso_B.unlock(); recurso_A.unlock();
```
**Fix 2 — `std::scoped_lock` (C++17):** adquire múltiplos mutexes atomicamente.
```cpp
std::scoped_lock lock(recurso_A, recurso_B); // nunca causa deadlock
```
**Fix 3 — Algoritmo do Banqueiro:** SO verifica se a alocação leva a estado seguro.

---
## 🌍 Analogia
**Cruzamento sem semáforo:** Carro A bloqueia B, B bloqueia C, C bloqueia A. Ninguém avança. A polícia (SO) precisa remover um carro à força para resolver.

---
## 💻 Na Prática
| Contexto | Exemplo |
|---|---|
| MySQL/PostgreSQL | Duas transações bloqueando tabelas em ordem inversa |
| Java | `synchronized` em ordem diferente em duas threads |
| Microserviços | Serviço A espera B responder; B espera A responder |

---
## 🎯 Pontos para o Exame
| Pergunta | Resposta |
|---|---|
| O que é deadlock? | Processos bloqueados mutuamente para sempre |
| Quantas condições? | **4** (todas simultâneas) |
| Condição mais fácil de eliminar? | **Espera Circular** (ordenação de locks) |
| Fix moderno em C++? | `std::scoped_lock(A, B)` |
