# 🖥️ Sistemas Operacionais — Guia de Estudos Completo
### Filipe de Castro dos Santos | Maio 2026

---

## 📋 Índice

1. [O que é um Sistema Operacional?](#o-que-é-um-sistema-operacional)
2. [O que o SO faz?](#o-que-o-so-faz)
3. [Tipos de Sistemas Operacionais](#tipos-de-sistemas-operacionais)
4. [Como Usar Este Repositório](#como-usar-este-repositório)
5. [Mapa dos Programas e Guias](#mapa-dos-programas-e-guias)
6. [Ordem de Estudo Recomendada](#ordem-de-estudo-recomendada)

---

## 🤔 O que é um Sistema Operacional?

Um **Sistema Operacional (SO)** é o software fundamental que atua como **intermediário entre o hardware do computador e os programas do usuário**. Sem ele, você precisaria programar diretamente em linguagem de máquina para usar qualquer recurso do computador.

> Pense no SO como o **gerente de um hotel**: os hóspedes (programas) fazem pedidos (CPU, memória, disco), e o gerente distribui os recursos do hotel (hardware) de forma justa e eficiente, sem deixar que um hóspede bagunce o quarto do outro.

### Definição técnica:
O SO é uma camada de software que:
1. **Abstrai** o hardware complexo em interfaces simples (APIs/System Calls)
2. **Gerencia** recursos escassos (CPU, RAM, disco, rede) entre múltiplos processos
3. **Protege** processos uns dos outros e protege o hardware de acessos indevidos

```
  ┌─────────────────────────────────┐
  │   Aplicações do Usuário         │  <- Chrome, VS Code, jogos...
  ├─────────────────────────────────┤
  │   Sistema Operacional           │  <- Linux, Windows, macOS
  │   (Kernel + System Calls)       │
  ├─────────────────────────────────┤
  │   Hardware                      │  <- CPU, RAM, SSD, GPU...
  └─────────────────────────────────┘
```

---

## ⚙️ O que o SO Faz?

### 1. 🔄 Gerenciamento de Processos
Controla a **criação, execução e encerramento** de processos. Decide qual processo usa a CPU e quando (**escalonamento**). Gerencia os 5 estados de cada processo.

### 2. 🧠 Gerenciamento de Memória
Aloca e desaloca memória para processos. Implementa **memória virtual** (dá ilusão de RAM infinita). Protege o espaço de memória de cada processo.

### 3. 📁 Sistema de Arquivos
Organiza dados em arquivos e diretórios. Controla quem pode ler, escrever ou executar cada arquivo. Exemplos: ext4 (Linux), NTFS (Windows), APFS (macOS).

### 4. ⌨️ Gerenciamento de Entrada e Saída (E/S)
Controla a comunicação com dispositivos: teclado, mouse, disco, rede, USB. Usa **drivers** para abstrair o hardware específico de cada dispositivo.

### 5. 🔒 Segurança e Permissões
Controla quem pode acessar quais recursos. Implementa usuários, grupos e permissões. Protege processos com isolamento de memória.

### 6. 🌐 Interface com o Usuário
- **CLI** (Command Line Interface): terminal, bash, PowerShell
- **GUI** (Graphical User Interface): janelas, ícones, mouse
- **API** (Application Programming Interface): System Calls para programadores

---

## 🗂️ Tipos de Sistemas Operacionais

### Por Número de Programas Simultâneos

| Tipo | Descrição | Exemplo |
|---|---|---|
| **Monoprogramação** | Um único programa roda por vez. CPU fica ociosa durante E/S | MS-DOS |
| **Multiprogramação** | Vários programas na memória. CPU nunca fica ociosa | Linux, Windows |
| **Multitarefa (Time-Sharing)** | Variante de multiprogramação com troca rápida (ilusão de simultaneidade) | Todos os modernos |

### Por Número de CPUs

| Tipo | Descrição | Exemplo |
|---|---|---|
| **Monoprocessado** | Uma única CPU. Paralelismo é *aparente* (escalonamento rápido) | PCs antigos |
| **Multiprocessado** | Múltiplas CPUs/núcleos. Paralelismo *real* | PCs modernos (4, 8, 16 núcleos) |
| **Distribuído** | Múltiplas máquinas conectadas em rede agindo como um sistema | Google, Amazon AWS |

> ⚠️ **Cuidado com a inversão!** Mono = um, Multi = muitos.
> - **Mono**processado = **uma** CPU
> - **Multi**processado = **muitas** CPUs

### Por Tipo de Uso

| Tipo | Características | Exemplos |
|---|---|---|
| **Desktop** | Interface gráfica, multitarefa, interativo | Windows 11, Ubuntu, macOS |
| **Servidor** | Estabilidade, múltiplos usuários, sem GUI necessária | Ubuntu Server, Windows Server |
| **Mobile** | Economia de energia, touch, GPS, apps isolados | Android, iOS |
| **Embarcado** | Recursos limitados, hardware específico, sem disco | Firmware de geladeira, carro |
| **Tempo Real (RTOS)** | Resposta garantida em tempo máximo fixo | FreeRTOS, VxWorks (aviões, robôs) |
| **Batch** | Processa lotes de jobs sem interação humana | Mainframes, processamento bancário |

### Por Modo de Operação

| Modo | Descrição |
|---|---|
| **Preemptivo** | SO pode tirar a CPU à força de qualquer processo. Mais justo. |
| **Cooperativo** | Processo libera a CPU voluntariamente. Processo mau pode travar tudo. (macOS antigo, Windows 3.1) |

---

## 🏗️ Estrutura Interna do SO

```
  ┌───────────────────────────────────────────────┐
  │                KERNEL                         │
  │  ┌──────────┐ ┌──────────┐ ┌──────────────┐  │
  │  │Gerenc.   │ │Gerenc.   │ │Gerenc.       │  │
  │  │Processos │ │Memória   │ │E/S e Drivers │  │
  │  └──────────┘ └──────────┘ └──────────────┘  │
  │  ┌──────────┐ ┌──────────────────────────┐   │
  │  │Sistema   │ │  Sistema de Arquivos     │   │
  │  │de Rede   │ │  (VFS)                   │   │
  │  └──────────┘ └──────────────────────────┘   │
  └───────────────────────────────────────────────┘
              ↑ System Calls (interface)
  ┌───────────────────────────────────────────────┐
  │         Espaço do Usuário                     │
  │  bash  Chrome  Python  seu_programa.cpp       │
  └───────────────────────────────────────────────┘
```

### Tipos de Kernel:
- **Monolítico** (Linux): tudo no kernel — rápido, mas grande
- **Microkernel** (QNX, Minix): kernel mínimo, serviços em userspace — mais seguro, mais lento
- **Híbrido** (Windows, macOS): mistura dos dois

---

## 💻 Como Usar Este Repositório

### Estrutura dos Arquivos

```
estudo_so/
├── README.md                          <- Este arquivo
├── Makefile                           <- Compila todos os programas
│
├── 01_condicao_de_corrida.cpp         <- Demo: Race Condition e Mutex
├── 01_condicao_de_corrida.md          <- Guia teórico: Race Condition
│
├── 02_deadlock.cpp                    <- Demo: Deadlock e soluções
├── 02_deadlock.md                     <- Guia teórico: Deadlock + Coffman
│
├── 03_escalonamento.cpp               <- Demo: FIFO, SJF, Round-Robin
├── 03_escalonamento.md                <- Guia teórico: CPU Scheduling
│
├── 04_alocacao_memoria.cpp            <- Demo: First/Best/Worst/Next-fit
├── 04_alocacao_memoria.md             <- Guia teórico: Alocação + Fragmentação
│
├── 05_memoria_virtual.cpp             <- Demo: Page fault, FIFO vs LRU
├── 05_memoria_virtual.md              <- Guia teórico: Memória Virtual + MMU
│
├── 06_segmentacao.cpp                 <- Demo: Tabela de segmentos + SIGSEGV
├── 06_segmentacao.md                  <- Guia teórico: Segmentação vs Paginação
│
├── 07_semaforo_produtor_consumidor.cpp <- Demo: Semáforo + buffer limitado
├── 07_semaforo_produtor_consumidor.md  <- Guia teórico: Semáforos
│
├── 08_estados_processo.cpp            <- Demo: NEW→RUNNING→TERMINATED
├── 08_estados_processo.md             <- Guia teórico: Estados + Context Switch
│
└── 09_starvation_prioridade.cpp       <- Demo: Starvation vs Aging
    09_starvation_prioridade.md        <- Guia teórico: Starvation + Preempção
```

### Compilar e Rodar

```bash
# Compilar tudo de uma vez
make all

# Rodar um programa específico
make run1    # Race Condition
make run2    # Deadlock
make run3    # Escalonamento
make run4    # Alocação de Memória
make run5    # Memória Virtual
make run6    # Segmentação
make run7    # Semáforo / Produtor-Consumidor
make run8    # Estados de Processo
make run9    # Starvation e Aging

# Rodar todos em sequência
make runall

# Apagar executáveis
make clean
```

---

## 🗺️ Mapa dos Programas e Guias

| # | Programa | Guia Teórico | Conceitos do Exame Cobertos |
|---|---|---|---|
| 1 | `01_...cpp` | `01_...md` | Condição de corrida, mutex, zona crítica, RAII |
| 2 | `02_...cpp` | `02_...md` | Deadlock, 4 condições de Coffman, scoped_lock |
| 3 | `03_...cpp` | `03_...md` | FIFO, SJF, Round-Robin, quantum, métricas |
| 4 | `04_...cpp` | `04_...md` | First/Best/Worst/Next-fit, fragmentação interna/externa |
| 5 | `05_...cpp` | `05_...md` | Memória virtual, MMU, page fault, Page In/Out, LRU |
| 6 | `06_...cpp` | `06_...md` | Segmentação, base+limite, SIGSEGV, vs paginação |
| 7 | `07_...cpp` | `07_...md` | Semáforo, wait/signal, produtor-consumidor |
| 8 | `08_...cpp` | `08_...md` | 5 estados, PCB, mudança de contexto, CPU/IO-bound |
| 9 | `09_...cpp` | `09_...md` | Starvation, prioridade, aging, preempção, CFS Linux |

---

## 📚 Ordem de Estudo Recomendada

### Nível 1 — Fundamentos (comece aqui)
1. **Demo 8** — Estados de Processo: entenda o ciclo de vida de um processo
2. **Demo 3** — Escalonamento: FIFO, SJF e Round-Robin com Gantt chart visual

### Nível 2 — Sincronização (o mais importante!)
3. **Demo 1** — Condição de Corrida: veja dados sendo corrompidos em tempo real
4. **Demo 7** — Semáforo: Produtor-Consumidor com buffer compartilhado
5. **Demo 2** — Deadlock: as 4 condições e como evitar

### Nível 3 — Memória (tópico do exame)
6. **Demo 4** — Alocação: veja a memória fragmentando na tela
7. **Demo 5** — Memória Virtual: page faults passo a passo
8. **Demo 6** — Segmentação: proteção de código vs dados

### Nível 4 — Avançado
9. **Demo 9** — Starvation: veja um processo nunca rodar, depois o fix com aging

---

## 🎯 Resumo para o Exame

### Deadlock
- **4 condições (todas necessárias):** Exclusão Mútua + Manter e Esperar + Não-Preempção + Espera Circular
- **Prevenir:** eliminar qualquer uma das 4 condições

### Memória
| Conceito | Definição rápida |
|---|---|
| Fragmentação Interna | Espaço desperdiçado **dentro** do bloco alocado |
| Fragmentação Externa | Memória livre total suficiente, mas **não contígua** |
| Page Fault | Acesso a página ausente na RAM → SO busca no disco |
| Page In | Disco → RAM |
| Page Out | RAM → Disco |
| MMU | Hardware que traduz endereço virtual → físico |
| Segmentação | Blocos **variáveis** (lógicos: CODE, DATA, STACK) |
| Paginação | Blocos **fixos** (4KB), sem fragmentação externa |

### Escalonamento
| Algoritmo | Característica | Problema |
|---|---|---|
| FIFO | Na ordem de chegada | Convoy effect |
| SJF | Menor burst primeiro | Starvation |
| Round-Robin | Quantum de tempo | Troca de contexto frequente |

### Estratégias de Alocação
| Estratégia | Como funciona | Desvantagem |
|---|---|---|
| First-fit | 1º bloco que cabe | Fragmenta o início |
| Best-fit | Menor bloco que cabe | Fragmentos minúsculos |
| Worst-fit | Maior bloco | Consome blocos grandes |
| Next-fit | Continua de onde parou | Fragmenta mais o final |
| Quick-fit | Listas por tamanho O(1) | Overhead de memória |

---

> 💡 **Dica:** Para cada conceito teórico, rode o programa correspondente e observe a saída. Ver o código executando solidifica muito mais o conhecimento do que apenas ler slides!
