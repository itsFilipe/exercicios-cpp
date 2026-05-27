# 🚦 Semáforo e Problema Produtor-Consumidor
> **Demo:** `make run7` | **Teoria:** este arquivo

---
## 📖 O que é Semáforo?
Proposto por Dijkstra (1965). Um semáforo é um **contador inteiro** com duas operações atômicas:
- **`wait()` / `P()` / `down()`:** decrementa. Se resultado < 0, **bloqueia** a thread.
- **`signal()` / `V()` / `up()`:** incrementa. Se há threads bloqueadas, **acorda** uma.

| Tipo | Valor inicial | Uso |
|---|---|---|
| **Binário (Mutex)** | 1 | Exclusão mútua |
| **Contável** | N | Controla acesso a N recursos |

---
## 📚 Problema Produtor-Consumidor (Bounded Buffer)
**Cenário:** buffer de capacidade N. Produtores inserem; Consumidores retiram.

**Solução com 3 semáforos:**
```
sem_vagas = N  ← quantas vagas livres no buffer
sem_itens = 0  ← quantos itens prontos para consumir
mutex     = 1  ← protege o acesso ao buffer

PRODUTOR:               CONSUMIDOR:
wait(sem_vagas)         wait(sem_itens)
wait(mutex)             wait(mutex)
  buffer.push(item)       item = buffer.pop()
signal(mutex)           signal(mutex)
signal(sem_itens)       signal(sem_vagas)
```
> ⚠️ A ordem importa! `wait(mutex)` antes de `wait(sem_vagas)` → **deadlock**.

---
## 🌍 Analogia
**Restaurante com balcão:**
- **Cozinheiros (produtores):** preparam pratos e colocam no balcão
- **Garçons (consumidores):** pegam pratos e entregam nas mesas
- **sem_vagas:** cozinheiro espera se balcão cheio
- **sem_itens:** garçom espera se balcão vazio
- **mutex:** só um por vez acessa o balcão

---
## 💻 Na Prática
| Contexto | Exemplo |
|---|---|
| Linux | `pipe()` — produtor escreve, consumidor lê |
| Java | `BlockingQueue` (ArrayBlockingQueue) |
| Python | `queue.Queue` com `put()` e `get()` |
| Kafka/RabbitMQ | Mensageria em escala: producers e consumers |
| Banco de dados | Pool de conexões (N conexões = semáforo contável com N) |

**Semáforo vs Mutex:**
- Mutex tem "dono": quem deu `lock()` deve dar `unlock()`
- Semáforo não tem dono: qualquer thread pode dar `signal()`

---
## 🎯 Pontos para o Exame
| Pergunta | Resposta |
|---|---|
| O que é semáforo? | Contador atômico com `wait()` e `signal()` |
| O que faz `wait()`? | Decrementa; se < 0, **bloqueia** |
| O que faz `signal()`? | Incrementa; **acorda** uma thread bloqueada |
| Mutex é semáforo? | Sim! Semáforo **binário** com valor 1 |
| Quantos semáforos usa a solução clássica? | **3** (vagas, itens, mutex) |
