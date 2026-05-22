# 🔄 Condição de Corrida (Race Condition)
> **Demo:** `make run1` | **Teoria:** este arquivo

---
## 📖 O que é?
Condição de corrida ocorre quando dois ou mais processos/threads acessam um **recurso compartilhado concorrentemente** e o resultado depende da **ordem não-determinística** de execução. O dado fica corrompido e o bug muda a cada execução.

---
## 📚 Por que `contador++` não é seguro?
Parece atômica, mas internamente são **3 passos de CPU**:
```
1. LOAD:  registrador ← contador      (lê da RAM)
2. ADD:   registrador ← registrador+1
3. STORE: contador    ← registrador   (escreve na RAM)
```
Se duas threads fazem isso "ao mesmo tempo":
```
Thread A: LOAD  (lê 100)
Thread B: LOAD  (lê 100 também!)
Thread A: ADD→STORE (grava 101)
Thread B: ADD→STORE (grava 101)  ← sobrescreveu! Perdemos 1 incremento
```
Com 10 threads × 100.000 incrementos, podem-se perder **dezenas de milhares** de incrementos.

## 📚 Solução: Mutex
**Zona Crítica** = trecho que acessa o recurso compartilhado. O mutex garante que apenas 1 thread executa por vez.
```cpp
std::mutex mtx;
// apenas UMA thread executa o bloco por vez:
std::lock_guard<std::mutex> lock(mtx); // RAII: libera automaticamente
contador++;
```

---
## 🌍 Analogia
Você e um amigo acessam a mesma conta bancária simultaneamente: ambos leem R$1000, ambos sacam R$500 e ambos gravam R$500. O banco perdeu R$500. Isso é race condition — bancos usam **locks de transação** para evitar isso.

---
## 💻 Na Prática
| Contexto | Exemplo |
|---|---|
| E-commerce | Dois clientes compram o último produto em estoque |
| Banco de dados | Duas transações editam o mesmo registro |
| Linux Kernel | Acesso a estruturas sem spinlock |
| React/frontend | Estado mutado por múltiplos handlers |

**Heisenbug:** o bug some quando você adiciona `printf()` de debug, pois isso muda o timing das threads.

---
## 🎯 Pontos para o Exame
| Pergunta | Resposta |
|---|---|
| O que é race condition? | Resultado não-determinístico por acesso concorrente sem sincronização |
| O que é zona crítica? | Trecho de código que acessa recurso compartilhado |
| O que é mutex? | Lock binário que garante exclusão mútua |
| Condição de Coffman relacionada? | **Exclusão Mútua** |
