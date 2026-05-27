# ⏱️ Escalonamento de Processos (CPU Scheduling)
> **Demo:** `make run3` | **Teoria:** este arquivo

---
## 📖 O que é?
O **escalonador (scheduler)** decide **qual processo usa a CPU e por quanto tempo**. É o "maestro" do SO — sem ele, um processo poderia monopolizar a CPU para sempre.

## 📚 Os 3 Tipos de Escalonadores
| Tipo | Função |
|---|---|
| **Longo Prazo** | Decide quais jobs saem do disco e entram na RAM |
| **Curto Prazo** | Decide qual processo READY ganha a CPU *agora* (age centenas de vezes/segundo) |
| **Médio Prazo** | Remove processos da RAM → disco (swap) se faltar memória |

---
## 📚 Algoritmos
### FIFO / FCFS
Atende na **ordem de chegada**. Sem preempção.
- ✅ Simples, sem starvation
- ❌ **Convoy Effect:** processo longo bloqueia todos os curtos atrás dele

### SJF (Shortest Job First)
Escolhe o processo com **menor burst** entre os prontos.
- ✅ **Mínimo tempo médio de espera** (ótimo teórico)
- ❌ **Starvation:** processos longos nunca rodam se curtos chegam continuamente

### Round-Robin
Cada processo recebe um **quantum** fixo. Se não terminar, volta ao final da fila.
```
Quantum=2, P1(6), P2(4), P3(2):
|P1|P2|P3|P1|P2|P1|
0  2  4  6  8  10 12
```
- ✅ **Justo** — todo processo progride
- ✅ **Preemptivo** — nenhum monopoliza a CPU
- ✅ Ideal para sistemas interativos (Linux usa uma variante: CFS)
- ❌ Muita troca de contexto se quantum for pequeno

---
## 🌍 Analogia
- **FIFO** → Fila do banco: quem chegou primeiro é atendido. Uma pessoa com mil papéis trava todos.
- **SJF** → Caixa expressa (≤10 itens): ótimo pra maioria, mas quem tem carrinho cheio espera para sempre.
- **Round-Robin** → Rodízio de pizza: todos recebem uma fatia por rodada. Ninguém fica sem comer.

---
## 💻 Na Prática
| SO | Algoritmo usado |
|---|---|
| Linux | CFS — Completely Fair Scheduler |
| Windows | Prioridade multinível com quantum variável |
| Android | Baseado no Linux CFS |
| RTOS | Prioridade estrita (processo crítico sempre primeiro) |

---
## 🎯 Pontos para o Exame
| Pergunta | Resposta |
|---|---|
| O que é o escalonador de curto prazo? | Decide qual processo READY ganha a CPU agora |
| O que é quantum? | Fatia de tempo máxima no Round-Robin |
| Qual algoritmo tem menor espera média? | **SJF** |
| Qual é mais justo? | **Round-Robin** |
| O que é preempção? | SO pode tirar a CPU de um processo no meio da execução |
| Problema do SJF? | **Starvation** |
