# ☠️ Starvation, Prioridade e Aging
> **Demo:** `make run9` | **Teoria:** este arquivo

---
## 📖 O que é Starvation?
**Starvation (Inanição):** processo espera indefinidamente por um recurso (CPU) porque processos de maior prioridade chegam continuamente. O processo "morre de fome".

---
## 📚 Como Acontece
```
t=0: [P_alta1(prio=1), P_baixa(prio=5)] → CPU para P_alta1
t=3: P_alta2 chega (prio=1)             → CPU para P_alta2
t=6: P_alta3 chega (prio=1)             → CPU para P_alta3
t=9: P_baixa esperando há 9u... e continua esperando! → STARVATION
```

**Algoritmos que causam starvation:**
- Prioridade estática (mais comum)
- SJF (processos longos nunca rodam se curtos chegam sempre)
- LIFO

---
## 📚 Solução: Aging (Envelhecimento)
Aumenta gradualmente a prioridade de um processo à medida que ele espera:
```
Regra: a cada 2u de espera, prioridade melhora em 1

P_baixa t=0:  prio=5 (ruim)
P_baixa t=4:  prio=3 (melhorou)
P_baixa t=8:  prio=1 (igual aos de alta!)
→ P_baixa eventualmente roda!
```

---
## 📚 Preempção vs Não-Preempção
| | Preemptivo | Não-Preemptivo |
|---|---|---|
| Definição | SO tira CPU à força | Processo libera voluntariamente |
| Exemplo | Round-Robin, Linux CFS | FIFO clássico |
| Starvation | Menos provável | Mais provável |
| Latência | Menor | Maior |
| Uso | Sistemas interativos | Batch |

---
## 🌍 Analogia
**Fila VIP em uma festa:**
- VIPs (alta prioridade) entram na frente sempre
- Pessoa sem VIP fica na fila geral para sempre → **starvation**
- **Aging:** a cada 30 min esperando, o segurança sobe o nível de prioridade. Após 2h vira "VIP honorário".

---
## 💻 Na Prática
| Contexto | Mecanismo anti-starvation |
|---|---|
| Linux CFS | `vruntime`: quem rodou menos tem prioridade automática |
| Windows | Priority Boost para threads que esperam por E/S |
| Linux `nice` | `renice` ajusta prioridade manualmente |

```bash
ps -eo pid,ni,pri,cmd    # ni=nice, pri=prioridade atual
renice +5 -p 1234        # diminui prioridade do processo 1234
```

---
## 🎯 Pontos para o Exame
| Pergunta | Resposta |
|---|---|
| O que é starvation? | Processo espera indefinidamente por CPU |
| Qual algoritmo causa mais starvation? | **SJF** e **Prioridade estática** |
| O que é aging? | Aumentar prioridade gradualmente com o tempo de espera |
| O que é preempção? | SO pode tirar a CPU sem cooperação do processo |
| Round-Robin é preemptivo? | **Sim** (interrompe ao fim do quantum) |
| Como Linux evita starvation? | **CFS** usa `vruntime` — aging automático |
