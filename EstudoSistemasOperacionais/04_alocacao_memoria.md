# 🧩 Alocação de Memória e Fragmentação
> **Demo:** `make run4` | **Teoria:** este arquivo

---
## 📖 Objetivos do Gerenciamento de Memória
1. **Alocação/Desalocação:** distribuir RAM e recuperá-la quando processos terminam
2. **Proteção:** processo A não acessa memória de B
3. **Compartilhamento:** processos cooperativos podem compartilhar regiões
4. **Realocação:** processo pode ser carregado em qualquer posição livre
5. **Abstração:** memória virtual — ilusão de RAM maior

---
## 📚 Fragmentação Interna
O bloco alocado é **maior que o necessário**. Espaço desperdiçado *dentro* do bloco.
```
Processo precisa de 4.100 bytes | Página = 4.096 bytes
→ ocupa 2 páginas (8.192 bytes) | desperdiça 4.092 bytes
```

## 📚 Fragmentação Externa
Memória livre total **suficiente**, mas em **pedaços não-contíguos**.
```
RAM: [P1:20MB][LIVRE:10MB][P2:30MB][LIVRE:15MB]
Total livre: 25MB. Processo pede 20MB contíguos → FALHA!
Maior bloco livre = 15MB < 20MB pedidos.
```

---
## 📚 Estratégias de Alocação
| Estratégia | Regra | Vantagem | Desvantagem |
|---|---|---|---|
| **First-fit** | 1º bloco suficiente | Mais rápido | Fragmenta início |
| **Best-fit** | Menor bloco suficiente | Menos desperdício interno | Fragmentos minúsculos inúteis |
| **Worst-fit** | Maior bloco disponível | Sobra ainda é grande | Consome blocos grandes |
| **Next-fit** | Continua de onde parou | Distribuição uniforme | Mais frag. no final |
| **Quick-fit** | Listas separadas por tamanho | **O(1)**, melhor desempenho | Overhead de memória |

---
## 🌍 Analogia
**Estacionamento com vagas de tamanhos variados:**
- **First-fit:** manobrista coloca no 1º lugar que couber (rápido)
- **Best-fit:** vaga que deixa menor espaço sobrando (mas cheio de espaçinhos inúteis)
- **Worst-fit:** vaga maior (o resto ainda serve pra outro carro)
- **Quick-fit:** fileiras específicas por tipo de veículo (ultrarrápido)

---
## 💻 Na Prática
- **malloc() no C/C++:** usa variante de first-fit com listas de free blocks
- **Linux kernel:** usa Slab Allocator (variante de quick-fit por tamanho de objeto)
- **Windows:** usa Lookaside Lists (similar ao quick-fit)

---
## 🎯 Pontos para o Exame
| Pergunta | Resposta |
|---|---|
| O que é frag. interna? | Desperdício **dentro** do bloco alocado |
| O que é frag. externa? | Memória livre suficiente no total mas **não contígua** |
| Qual elimina frag. externa? | **Paginação** (blocos fixos, qualquer frame serve) |
| Qual tem melhor desempenho? | **Quick-fit** |
| Desvantagem do Best-fit? | Gera fragmentos minúsculos inutilizáveis |
| Desvantagem do Worst-fit? | Vantagem: fragmento restante ainda é útil |
