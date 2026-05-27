# 🔄 Estados de Processo e Mudança de Contexto
> **Demo:** `make run8` | **Teoria:** este arquivo

---
## 📖 Os 5 Estados de um Processo
```
         admitido          CPU cedida
  NEW ──────────► READY ────────────► RUNNING ──► TERMINATED
                    ▲                     │
          E/S ok   │       pede E/S       │
                   └──── WAITING ◄────────┘
```

| Estado | Descrição |
|---|---|
| **NEW** | Processo sendo criado; PCB alocado |
| **READY** | Na fila, pronto para usar a CPU |
| **RUNNING** | Executando na CPU agora |
| **WAITING / BLOCKED** | Aguardando E/S, mutex, timer, socket... |
| **TERMINATED** | Terminou; SO libera recursos |

---
## 📚 Process Control Block (PCB)
O SO mantém um PCB para cada processo:
```
PCB = { PID, estado, Program Counter, registradores,
        tabela de páginas, arquivos abertos, prioridade, ... }
```

---
## 📚 Mudança de Contexto (Context Switch)
Quando o escalonador troca o processo na CPU:
```
1. Salva registradores de P1 → PCB[P1]
2. Salva Program Counter de P1 → PCB[P1]
3. Carrega registradores de P2 ← PCB[P2]
4. Carrega Program Counter de P2 ← PCB[P2]
5. CPU continua executando P2 de onde parou
```
**Custo:** 1 a 100 microsegundos. Durante a troca, **nenhum processo produz trabalho**.

### CPU-bound vs IO-bound:
- **CPU-bound:** fica RUNNING quase todo o tempo (renderização, cálculos)
- **IO-bound:** alterna RUNNING ↔ WAITING (banco de dados, download, teclado)

---
## 🌍 Analogia
**Professor atendendo alunos:**
- **NEW:** aluno se matriculou (fora da sala ainda)
- **READY:** aluno na fila do corredor esperando ser chamado
- **RUNNING:** sendo atendido pelo professor agora
- **WAITING:** foi ao laboratório buscar material
- **TERMINATED:** atendimento concluído, foi embora

**Mudança de contexto:** professor para de atender João, anota o ponto onde parou (PCB), pega a ficha do Pedro e continua.

---
## 💻 Na Prática
```bash
ps aux              # R=Running, S=Sleeping, D=Disk wait, Z=Zombie
htop                # visualização em tempo real
cat /proc/1234/status  # State: S (sleeping)
```
- **Zombie:** processo terminou mas pai não chamou `wait()` → PCB ainda existe
- Linux faz ~1000 trocas de contexto por segundo em sistema ocupado

---
## 🎯 Pontos para o Exame
| Pergunta | Resposta |
|---|---|
| Quantos estados? | **5:** NEW, READY, RUNNING, WAITING, TERMINATED |
| O que é mudança de contexto? | SO salva estado atual e carrega o do próximo processo |
| O que é salvo? | PC, registradores, info de memória (PCB) |
| CPU-bound vs IO-bound? | CPU-bound: RUNNING; IO-bound: alterna RUNNING↔WAITING |
| O que é zombie? | TERMINATED mas PCB ainda existe (pai não chamou `wait()`) |
