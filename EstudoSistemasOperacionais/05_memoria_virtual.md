# 🗂️ Memória Virtual, Paginação e Page Fault
> **Demo:** `make run5` | **Teoria:** este arquivo

---
## 📖 O que é Memória Virtual?
Técnica que dá a cada processo a **ilusão de que possui um espaço de endereçamento enorme e exclusivo**, mesmo que a RAM física seja menor. O SO usa o disco (swap) como extensão transparente da RAM.

**Dependência técnica:** requer a **MMU (Memory Management Unit)** — hardware integrado ao processador que traduz endereços virtuais → físicos em tempo de execução.

---
## 📚 Paginação
Divide tudo em blocos de **tamanho fixo**:
- **Páginas:** blocos do espaço virtual do processo
- **Frames:** blocos da RAM física
- Mesmo tamanho (ex: 4KB no Linux)

```
Tabela de Páginas do Processo:
Página 0 → Frame 2 (na RAM)
Página 1 → Frame 5 (na RAM)
Página 2 → DISCO   (não está na RAM!)
Página 3 → Frame 1 (na RAM)
```

### Tradução de Endereço (MMU):
```
Virtual: [nº da página | offset]
              ↓ tabela de páginas
Físico:  [nº do frame  | offset]
```
**TLB (Translation Lookaside Buffer):** cache de hardware para a tabela de páginas. Evita consultar a RAM a cada acesso.

---
## 📚 Page Fault e Page Replacement
**Page Fault:** processo acessa uma página que não está na RAM.
1. Hardware gera exceção → SO assume o controle
2. SO localiza a página no disco
3. Escolhe um frame para liberar (**substituição**)
4. **Page Out:** frame antigo → disco (se modificado)
5. **Page In:** página nova → frame liberado
6. Retoma o processo

### Algoritmos de Substituição:
| Algoritmo | Regra | Problema |
|---|---|---|
| **FIFO** | Remove a mais antiga | Anomalia de Belady (+ frames → + faults!) |
| **LRU** | Remove a menos recentemente usada | Mais inteligente, Linux usa variante |
| **OPT** | Remove a usada mais tarde no futuro | Impossível de implementar (teórico) |

### Paginação vs Swap Clássico:
| | Paginação | Swap Clássico |
|---|---|---|
| Unidade | Página (4KB) | Processo inteiro |
| Granularidade | Fina | Grossa |
| Uso moderno | Sim (padrão) | Ocasional (emergência) |

---
## 🌍 Analogia
Sua **mesa de trabalho** (RAM, 3 livros) e uma **estante** (disco). Quando precisa de um livro na estante → page fault (busca). Para pegar, precisa guardar um da mesa:
- **FIFO:** guarda o livro mais antigo na mesa
- **LRU:** guarda o que você não abre há mais tempo

---
## 💻 Na Prática
```bash
free -h                    # RAM + swap em uso
vmstat 1                   # page faults por segundo (si/so)
cat /proc/<pid>/status     # VmRSS=RAM real | VmSize=virtual
```
- Loading screens de jogos = pages sendo carregadas do disco
- Android mata apps em background para liberar frames

---
## 🎯 Pontos para o Exame
| Pergunta | Resposta |
|---|---|
| O que é memória virtual? | Ilusão de RAM maior que a física usando disco |
| Dependência técnica? | **MMU** |
| O que é page fault? | Acesso a página ausente na RAM → SO busca no disco |
| Page In / Page Out? | Disco→RAM / RAM→Disco |
| Como SO enxerga blocos? | Como **páginas** de tamanho fixo |
| Onde fica o mapeamento virtual→físico? | **Tabela de páginas**, traduzida pela **MMU** |
