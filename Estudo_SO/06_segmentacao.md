# 🔐 Segmentação de Memória
> **Demo:** `make run6` | **Teoria:** este arquivo

---
## 📖 O que é?
Técnica que divide o espaço de endereçamento em **segmentos de tamanho variável**, cada um com significado lógico: código, dados, pilha, heap. Diferente da paginação (físico, fixo), segmentação reflete a **estrutura lógica do programa**.

---
## 📚 Como Funciona
**Endereço virtual:** `(número_do_segmento, offset)`

**Tabela de Segmentos** (um por processo):
```
Seg | Nome  | Base   | Limite | Permissão
 0  | CODE  | 0x1000 |  500B  | R      ← só leitura!
 1  | DATA  | 0x2000 |  300B  | R/W
 2  | STACK | 0x5000 |  200B  | R/W
```

**Tradução:** `físico = base[seg] + offset`
```
Virtual: (seg=1, off=50) → 0x2000 + 50 = 0x2032
```

**A MMU verifica:**
1. `número_segmento` válido na tabela
2. `offset < limite` (sem estouro)
3. Permissão R/W (sem escrita em código)

Violação → **SIGSEGV (Segmentation Fault)**

---
## 📚 Segmentação vs Paginação
| Característica | Segmentação | Paginação |
|---|---|---|
| Tamanho | **Variável** (lógico) | **Fixo** (ex: 4KB) |
| Fragmentação | **Externa** | Interna |
| Significado | Sim (CODE, DATA...) | Não (físico) |
| Hardware | MMU base+limite | MMU tabela de páginas |
| Linux atual | Não usa (plana) | **Sim** (padrão) |

---
## 🌍 Analogia
**Apartamento dividido em cômodos:**
- **Quarto (CODE):** você pode entrar e ver, mas não pode reformar (R)
- **Cozinha (DATA):** pode usar e modificar (R/W)
- **Banheiro (STACK):** uso controlado

Cada cômodo tem **tamanho diferente** (≠ paginação, onde todos os quartos são iguais). A planta do apartamento = tabela de segmentos.

---
## 💻 Na Prática
```bash
readelf -S ./programa    # lista seções: .text(code), .data, .bss, .stack
```
- **Buffer Overflow:** estouro do STACK sobrescreve endereço de retorno (ataque clássico)
- **Linux moderno:** usa paginação pura; segmentação existe mas é "plana" (base=0, limite=4GB)
- **x86:** registradores CS(code), DS(data), SS(stack) são relíquias da segmentação

---
## 🎯 Pontos para o Exame
| Pergunta | Resposta |
|---|---|
| O que é segmentação? | Blocos de tamanho **variável** com significado lógico |
| Formato do endereço virtual? | **(num_segmento, offset)** |
| Hardware necessário? | **MMU** com registradores de **base + limite** |
| Tipo de fragmentação? | **Externa** |
| O que é SIGSEGV? | Sinal enviado pelo SO ao violar segmento |
