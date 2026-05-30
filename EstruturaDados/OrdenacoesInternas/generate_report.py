"""
generate_report.py
==================
Gera o relatório técnico em PDF para o Benchmark de Ordenações Internas.

Conteúdo:
  1. Capa
  2. Introdução e objetivos
  3. Fundamentos teóricos (complexidade e casos de uso embarcado por algoritmo)
  4. Tabela comparativa completa dos dados coletados
  5. Análise dos gráficos (com imagens embutidas)
  6. Análise crítica (pior caso, Quick Sort vs ordenados, O(n²) → O(n log n))
  7. Conclusão

Uso:
  python3 generate_report.py

Saída:
  results/relatorio_ordenacoes_internas.pdf
"""

import os
import csv
import math

# ── ReportLab ────────────────────────────────────────────────────────────────
from reportlab.lib.pagesizes import A4
from reportlab.lib import colors
from reportlab.lib.units import cm, mm
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.enums import TA_CENTER, TA_LEFT, TA_JUSTIFY
from reportlab.platypus import (
    SimpleDocTemplate, Paragraph, Spacer, Image, Table, TableStyle,
    PageBreak, HRFlowable, KeepTogether
)
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont

# ── Configuração ─────────────────────────────────────────────────────────────
OUTPUT_DIR  = "results"
OUTPUT_PDF  = os.path.join(OUTPUT_DIR, "relatorio_ordenacoes_internas.pdf")
CSV_PATH    = os.path.join(OUTPUT_DIR, "benchmark_results.csv")

# Paleta de cores
C_DARK      = colors.HexColor("#0d1117")
C_PRIMARY   = colors.HexColor("#1f6feb")
C_ACCENT    = colors.HexColor("#388bfd")
C_GREEN     = colors.HexColor("#2ea043")
C_RED       = colors.HexColor("#da3633")
C_ORANGE    = colors.HexColor("#d29922")
C_HEADER_BG = colors.HexColor("#161b22")
C_ROW_ALT   = colors.HexColor("#f6f8fa")
C_BORDER    = colors.HexColor("#d0d7de")
C_TEXT      = colors.HexColor("#24292f")
C_MUTED     = colors.HexColor("#656d76")
C_WHITE     = colors.white

PAGE_W, PAGE_H = A4
MARGIN = 2.2 * cm

# ── Estilos ───────────────────────────────────────────────────────────────────
styles = getSampleStyleSheet()

def make_style(name, **kwargs):
    return ParagraphStyle(name, **kwargs)

S_TITLE = make_style("S_TITLE",
    fontSize=26, fontName="Helvetica-Bold",
    textColor=C_DARK, alignment=TA_CENTER,
    spaceAfter=6)

S_SUBTITLE = make_style("S_SUBTITLE",
    fontSize=13, fontName="Helvetica",
    textColor=C_MUTED, alignment=TA_CENTER,
    spaceAfter=4)

S_SECTION = make_style("S_SECTION",
    fontSize=15, fontName="Helvetica-Bold",
    textColor=C_PRIMARY, spaceBefore=18, spaceAfter=8,
    borderPad=4)

S_SUBSECTION = make_style("S_SUBSECTION",
    fontSize=12, fontName="Helvetica-Bold",
    textColor=C_DARK, spaceBefore=12, spaceAfter=5)

S_BODY = make_style("S_BODY",
    fontSize=10, fontName="Helvetica",
    textColor=C_TEXT, alignment=TA_JUSTIFY,
    leading=15, spaceAfter=6)

S_CAPTION = make_style("S_CAPTION",
    fontSize=8.5, fontName="Helvetica-Oblique",
    textColor=C_MUTED, alignment=TA_CENTER,
    spaceAfter=10)

S_CODE = make_style("S_CODE",
    fontSize=9, fontName="Courier",
    textColor=colors.HexColor("#0550ae"),
    backColor=colors.HexColor("#f6f8fa"),
    borderPad=6, spaceAfter=8)

S_BULLET = make_style("S_BULLET",
    fontSize=10, fontName="Helvetica",
    textColor=C_TEXT, alignment=TA_LEFT,
    leading=15, spaceAfter=3, leftIndent=16)

S_TABLE_HDR = make_style("S_TABLE_HDR",
    fontSize=9, fontName="Helvetica-Bold",
    textColor=C_WHITE, alignment=TA_CENTER)

S_TABLE_CELL = make_style("S_TABLE_CELL",
    fontSize=8.5, fontName="Helvetica",
    textColor=C_TEXT, alignment=TA_CENTER)

S_TABLE_CELL_L = make_style("S_TABLE_CELL_L",
    fontSize=8.5, fontName="Helvetica",
    textColor=C_TEXT, alignment=TA_LEFT)

# ── Helpers ───────────────────────────────────────────────────────────────────
def p(text, style=S_BODY):
    return Paragraph(text, style)

def section(text):
    return p(text, S_SECTION)

def subsection(text):
    return p(text, S_SUBSECTION)

def bullet(text):
    return p(f"• {text}", S_BULLET)

def sp(h=0.3):
    return Spacer(1, h * cm)

def hr():
    return HRFlowable(width="100%", thickness=1, color=C_BORDER, spaceAfter=10)

def img(path, width=None, height=None, caption=None):
    items = []
    if os.path.exists(path):
        # Largura máxima disponível dentro das margens
        max_w = PAGE_W - 2 * MARGIN          # ~458 pt
        w = min(width or max_w, max_w)

        if height:
            h = height
        else:
            # Lê dimensões reais da imagem para manter proporção
            from reportlab.lib.utils import ImageReader
            try:
                ir = ImageReader(path)
                iw, ih = ir.getSize()
                h = w * ih / iw
            except Exception:
                h = w * 0.6   # fallback 5:3

            # Garante que cabe na página (altura máxima = página - margens - rodapé)
            max_h = PAGE_H - 2 * MARGIN - 2.5 * cm
            if h > max_h:
                scale = max_h / h
                h = max_h
                w = w * scale

        i = Image(path, width=w, height=h)
        i.hAlign = "CENTER"
        items.append(i)
        if caption:
            items.append(p(caption, S_CAPTION))
    else:
        items.append(p(f"[Imagem não encontrada: {path}]", S_CAPTION))
    return items

def fmt_time(ms):
    if ms >= 1000:
        return f"{ms/1000:.2f}s"
    return f"{ms:.2f}ms"

def fmt_num(n):
    if n >= 1_000_000_000:
        return f"{n/1e9:.2f}B"
    if n >= 1_000_000:
        return f"{n/1e6:.1f}M"
    if n >= 1_000:
        return f"{n/1e3:.0f}k"
    return str(n)

# ── Carregamento de dados ─────────────────────────────────────────────────────
def load_csv():
    rows = []
    with open(CSV_PATH, newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            row["Tamanho"]     = int(row["Tamanho"])
            row["Tempo_ms"]    = float(row["Tempo_ms"])
            row["Comparacoes"] = int(row["Comparacoes"])
            row["Swaps"]       = int(row["Swaps"])
            rows.append(row)
    return rows

def get(data, algo, scenario, size):
    for r in data:
        if r["Algoritmo"] == algo and r["Cenario"] == scenario and r["Tamanho"] == size:
            return r
    return None

# ── Cabeçalho e rodapé ────────────────────────────────────────────────────────
def on_page(canvas, doc):
    canvas.saveState()
    # Rodapé
    canvas.setFont("Helvetica", 8)
    canvas.setFillColor(C_MUTED)
    canvas.drawString(MARGIN, 1.2 * cm, "Benchmark de Ordenações Internas — Análise Comparativa de Algoritmos")
    canvas.drawRightString(PAGE_W - MARGIN, 1.2 * cm, f"Página {doc.page}")
    # Linha do rodapé
    canvas.setStrokeColor(C_BORDER)
    canvas.setLineWidth(0.5)
    canvas.line(MARGIN, 1.5 * cm, PAGE_W - MARGIN, 1.5 * cm)
    canvas.restoreState()

def on_first_page(canvas, doc):
    # Fundo azul escuro da capa
    canvas.saveState()
    canvas.setFillColor(C_DARK)
    canvas.rect(0, 0, PAGE_W, PAGE_H, fill=True, stroke=False)
    # Faixa colorida no topo
    canvas.setFillColor(C_PRIMARY)
    canvas.rect(0, PAGE_H - 3.5*cm, PAGE_W, 3.5*cm, fill=True, stroke=False)
    canvas.restoreState()

# ── MONTAGEM DO RELATÓRIO ─────────────────────────────────────────────────────
def build_report():
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    data = load_csv()

    doc = SimpleDocTemplate(
        OUTPUT_PDF,
        pagesize=A4,
        rightMargin=MARGIN, leftMargin=MARGIN,
        topMargin=MARGIN, bottomMargin=2.2*cm,
        title="Benchmark de Ordenações Internas",
        author="Análise Comparativa de Algoritmos",
    )

    story = []

    # ══════════════════════════════════════════════════════════════════════════
    # CAPA
    # ══════════════════════════════════════════════════════════════════════════
    story.append(sp(6))
    story.append(p("BENCHMARK DE ALGORITMOS DE", make_style("cv1",
        fontSize=20, fontName="Helvetica",
        textColor=C_ACCENT, alignment=TA_CENTER, spaceAfter=2)))
    story.append(p("ORDENAÇÃO INTERNA", make_style("cv2",
        fontSize=32, fontName="Helvetica-Bold",
        textColor=C_WHITE, alignment=TA_CENTER, spaceAfter=2)))
    story.append(sp(0.5))
    story.append(HRFlowable(width="60%", thickness=2, color=C_ACCENT,
                             hAlign="CENTER", spaceAfter=14))
    story.append(p("Análise Comparativa de Desempenho", make_style("cv3",
        fontSize=14, fontName="Helvetica-Oblique",
        textColor=colors.HexColor("#8b949e"), alignment=TA_CENTER, spaceAfter=4)))
    story.append(sp(1.5))

    # Tabela de info da capa
    capa_data = [
        ["Algoritmos Avaliados", "5 algoritmos clássicos"],
        ["Cenários de Teste",    "Aleatório · Ordenado · Inv. Ordenado"],
        ["Tamanhos de Vetor",    "5.000 · 10.000 · 50.000 elementos"],
        ["Linguagem",           "C++17  (compilado com -O0)"],
        ["Métricas Coletadas",  "Tempo (ms) · Comparações · Swaps"],
    ]
    capa_tbl = Table(capa_data, colWidths=[5.5*cm, 10*cm])
    capa_tbl.setStyle(TableStyle([
        ("FONTNAME",    (0,0), (-1,-1), "Helvetica"),
        ("FONTNAME",    (0,0), (0,-1), "Helvetica-Bold"),
        ("FONTSIZE",    (0,0), (-1,-1), 10),
        ("TEXTCOLOR",   (0,0), (0,-1), C_ACCENT),
        ("TEXTCOLOR",   (1,0), (1,-1), colors.HexColor("#c9d1d9")),
        ("ROWBACKGROUNDS", (0,0), (-1,-1),
            [colors.HexColor("#161b22"), colors.HexColor("#21262d")]),
        ("GRID",        (0,0), (-1,-1), 0.5, colors.HexColor("#30363d")),
        ("LEFTPADDING", (0,0), (-1,-1), 12),
        ("RIGHTPADDING",(0,0), (-1,-1), 12),
        ("TOPPADDING",  (0,0), (-1,-1), 8),
        ("BOTTOMPADDING",(0,0),(-1,-1), 8),
        ("ROWSPAN",     (0,0), (-1,-1), 1),
    ]))
    story.append(capa_tbl)
    story.append(sp(2))
    story.append(p("2026", make_style("cv4",
        fontSize=12, fontName="Helvetica",
        textColor=colors.HexColor("#8b949e"), alignment=TA_CENTER)))
    story.append(PageBreak())

    # ══════════════════════════════════════════════════════════════════════════
    # 1. INTRODUÇÃO
    # ══════════════════════════════════════════════════════════════════════════
    story.append(section("1. Introdução"))
    story.append(hr())
    story.append(p(
        "A ordenação de dados é uma das operações fundamentais em ciência da computação. "
        "A escolha do algoritmo adequado impacta diretamente o desempenho de sistemas — "
        "desde aplicações de alto desempenho até dispositivos embarcados com recursos limitados. "
        "Este relatório apresenta um <b>benchmark controlado</b> que mede e compara cinco "
        "algoritmos clássicos de ordenação interna em termos de:"
    ))
    story.append(bullet("Tempo de execução (ms)"))
    story.append(bullet("Número de comparações entre elementos"))
    story.append(bullet("Número de trocas (swaps) realizadas"))
    story.append(sp(0.3))
    story.append(p(
        "Os testes foram realizados em três cenários distintos — vetor <b>aleatório</b>, "
        "<b>já ordenado</b> e <b>inversamente ordenado</b> — para três tamanhos de entrada: "
        "<b>5.000</b>, <b>10.000</b> e <b>50.000 elementos</b>. "
        "O ambiente foi compilado com <i>-O0</i> (sem otimizações do compilador) "
        "para que os tempos reflitam o comportamento algorítmico real."
    ))

    # ══════════════════════════════════════════════════════════════════════════
    # 2. FUNDAMENTOS TEÓRICOS
    # ══════════════════════════════════════════════════════════════════════════
    story.append(section("2. Fundamentos Teóricos"))
    story.append(hr())
    story.append(p(
        "A seguir, descrevemos cada algoritmo avaliado: seu princípio de funcionamento, "
        "complexidade assintótica e casos de uso — incluindo aplicações em "
        "<b>sistemas embarcados</b>."
    ))

    algos_info = [
        {
            "title": "2.1 Counting Sort — Método por Distribuição",
            "complexity": [
                ("Melhor caso", "O(n + k)"),
                ("Médio caso",  "O(n + k)"),
                ("Pior caso",   "O(n + k)"),
                ("Espaço",      "O(k)"),
            ],
            "stable": True,
            "inplace": False,
            "desc": (
                "O Counting Sort é um algoritmo <b>não baseado em comparações</b>: "
                "em vez de comparar pares de elementos, conta a frequência de cada valor "
                "e usa essas contagens para reconstruir o vetor ordenado. Isso o torna "
                "extremamente rápido quando o intervalo de valores <i>k</i> é pequeno em "
                "relação a <i>n</i>, quebrando o limite teórico de O(n log n) imposto "
                "a algoritmos baseados em comparação."
            ),
            "embedded": (
                "Ideal para ordenar <b>prioridades de tarefas em RTOS</b> (faixa de 0–255), "
                "notas de alunos, identificadores de sensores ou qualquer domínio inteiro "
                "e limitado. É a etapa interna do Radix Sort. Muito usado em "
                "<b>DSP e telecomunicações</b> para histogramas de frequência. "
                "<i>Limitação embarcada</i>: requer vetor auxiliar de tamanho k, "
                "o que pode ser proibitivo se k for grande."
            ),
        },
        {
            "title": "2.2 Insertion Sort — Método por Inserção",
            "complexity": [
                ("Melhor caso", "O(n)   — vetor já ordenado"),
                ("Médio caso",  "O(n²)"),
                ("Pior caso",   "O(n²)  — vetor inversamente ordenado"),
                ("Espaço",      "O(1)"),
            ],
            "stable": True,
            "inplace": True,
            "desc": (
                "Funciona como ordenar cartas na mão: para cada elemento, "
                "desloca os maiores à direita e insere o elemento na posição correta. "
                "É <b>adaptativo</b> (beneficia-se de dados parcialmente ordenados) e "
                "<b>online</b> (pode processar elementos à medida que chegam). "
                "No melhor caso (vetor já ordenado), realiza apenas n−1 comparações e zero trocas."
            ),
            "embedded": (
                "Algoritmo <b>padrão para vetores pequenos</b> (n &lt; 32) em implementações "
                "híbridas como <b>Timsort</b> (Python/Java) e <b>Introsort</b> (C++ std::sort). "
                "Excelente em <b>microcontroladores com RAM restrita</b> (AVR, ARM Cortex-M) "
                "pois é in-place e sem overhead. Ideal para <b>manutenção de listas quase "
                "ordenadas em tempo real</b> (inserção de novos sensores em uma fila ordenada)."
            ),
        },
        {
            "title": "2.3 Merge Sort — Método por Intercalação",
            "complexity": [
                ("Melhor caso", "O(n log n)"),
                ("Médio caso",  "O(n log n)"),
                ("Pior caso",   "O(n log n) — garantido"),
                ("Espaço",      "O(n)"),
            ],
            "stable": True,
            "inplace": False,
            "desc": (
                "Algoritmo divide-and-conquer: divide o vetor ao meio recursivamente "
                "até sub-vetores unitários, depois <b>intercala</b> os pares ordenados. "
                "Garante O(n log n) em <i>todos</i> os cenários — melhor, médio e pior caso. "
                "É a base do <b>Timsort</b> (Python, Java, Android) e da ordenação "
                "estável de bancos de dados."
            ),
            "embedded": (
                "Usado em <b>sistemas de tempo real críticos</b> onde a garantia de "
                "O(n log n) no pior caso é mandatória (aviônicos, automotivo AUTOSAR). "
                "Excelente para <b>ordenação externa</b> (arquivos maiores que a RAM). "
                "<i>Limitação embarcada</i>: requer O(n) de memória auxiliar — "
                "problemático em MCUs com poucos kB de RAM."
            ),
        },
        {
            "title": "2.4 Selection Sort — Método por Seleção",
            "complexity": [
                ("Melhor caso", "O(n²)  — comparações fixas n(n−1)/2"),
                ("Médio caso",  "O(n²)"),
                ("Pior caso",   "O(n²)"),
                ("Espaço",      "O(1)"),
            ],
            "stable": False,
            "inplace": True,
            "desc": (
                "Em cada passo, encontra o menor elemento do sub-vetor restante "
                "e o coloca na posição correta. O número de <b>comparações é sempre fixo</b> "
                "— n(n−1)/2 — independentemente do estado inicial. Porém, realiza "
                "<b>no máximo n−1 trocas</b>, o mínimo possível entre os algoritmos O(n²). "
                "Não é adaptativo: não se beneficia de dados parcialmente ordenados."
            ),
            "embedded": (
                "O número mínimo de swaps torna o Selection Sort valioso quando "
                "<b>o custo de escrita é alto</b>: memória <b>EEPROM</b> e <b>Flash NAND</b> "
                "em MCUs (AVR ATmega, STM32) têm ciclos de escrita limitados (~100k escritas). "
                "Minimizar swaps prolonga a vida útil do hardware. "
                "Adequado para <b>tabelas de calibração</b> ou <b>configurações de fábrica</b> "
                "armazenadas em memória não-volátil."
            ),
        },
        {
            "title": "2.5 Quick Sort — Método por Substituição/Troca",
            "complexity": [
                ("Melhor caso", "O(n log n)"),
                ("Médio caso",  "O(n log n)"),
                ("Pior caso",   "O(n²)  — mitigado com mediana-de-três"),
                ("Espaço",      "O(log n) — pilha de recursão"),
            ],
            "stable": False,
            "inplace": True,
            "desc": (
                "Seleciona um <b>pivô</b> e particiona o vetor: elementos menores à "
                "esquerda, maiores à direita — recursivamente. Implementado aqui com "
                "<b>mediana-de-três</b> (pivô = mediana entre arr[left], arr[mid], arr[right]), "
                "eliminando praticamente o risco de O(n²) em vetores ordenados. "
                "É o algoritmo mais rápido na prática para dados aleatórios: "
                "<b>cache-friendly</b>, in-place e com constante baixa."
            ),
            "embedded": (
                "Base do <b>qsort()</b> da libc e do <b>std::sort</b> do C++ (via Introsort). "
                "Usado em <b>FreeRTOS</b>, <b>Zephyr OS</b> e na maioria dos SDKs embarcados. "
                "<i>Cuidados</i>: a pilha de recursão pode ser problema em MCUs com stack "
                "pequena — solução: versão iterativa ou limite de profundidade. "
                "<b>NÃO recomendado</b> quando a garantia de pior caso é mandatória "
                "(use Merge Sort ou Heap Sort nesses casos)."
            ),
        },
    ]

    for info in algos_info:
        story.append(sp(0.2))
        story.append(subsection(info["title"]))

        # Descrição
        story.append(p(info["desc"]))

        # Tabela de complexidade inline
        comp_rows = [[p("Caso", S_TABLE_HDR), p("Complexidade", S_TABLE_HDR)]]
        for case, val in info["complexity"]:
            comp_rows.append([p(case, S_TABLE_CELL_L), p(f"<b>{val}</b>", S_TABLE_CELL)])

        # Adiciona linha estável/in-place
        comp_rows.append([p("Estável?",  S_TABLE_CELL_L),
                          p("✓ Sim" if info["stable"] else "✗ Não", S_TABLE_CELL)])
        comp_rows.append([p("In-place?", S_TABLE_CELL_L),
                          p("✓ Sim" if info["inplace"] else "✗ Não", S_TABLE_CELL)])

        comp_tbl = Table(comp_rows, colWidths=[5*cm, 9*cm], hAlign="LEFT")
        comp_tbl.setStyle(TableStyle([
            ("BACKGROUND",  (0,0), (-1,0),  C_PRIMARY),
            ("TEXTCOLOR",   (0,0), (-1,0),  C_WHITE),
            ("ROWBACKGROUNDS", (0,1), (-1,-1), [C_WHITE, C_ROW_ALT]),
            ("GRID",        (0,0), (-1,-1), 0.4, C_BORDER),
            ("FONTNAME",    (0,1), (0,-1), "Helvetica-Bold"),
            ("FONTSIZE",    (0,0), (-1,-1), 9),
            ("LEFTPADDING", (0,0), (-1,-1), 8),
            ("TOPPADDING",  (0,0), (-1,-1), 5),
            ("BOTTOMPADDING",(0,0),(-1,-1), 5),
        ]))
        story.append(comp_tbl)
        story.append(sp(0.3))

        # Casos de uso embarcados
        story.append(p(f"<b>📟 Casos de Uso em Sistemas Embarcados:</b> {info['embedded']}"))
        story.append(sp(0.2))

    # ══════════════════════════════════════════════════════════════════════════
    # 3. TABELA COMPARATIVA
    # ══════════════════════════════════════════════════════════════════════════
    story.append(PageBreak())
    story.append(section("3. Tabela Comparativa de Desempenho"))
    story.append(hr())
    story.append(p(
        "A tabela a seguir consolida todos os resultados coletados durante o benchmark. "
        "Os valores de tempo estão em <b>milissegundos (ms)</b>. "
        "Valores superiores a 1 segundo são exibidos em segundos (s)."
    ))
    story.append(sp(0.3))

    ALGOS    = ["Counting Sort", "Insertion Sort", "Merge Sort", "Selection Sort", "Quick Sort"]
    SCENARIOS = [("Aleatorio", "Aleatório"), ("Ordenado", "Ordenado"), ("Inv. Ordenado", "Inv. Ordenado")]
    SIZES    = [5000, 10000, 50000]

    for size in SIZES:
        story.append(subsection(f"Vetor de {size:,} elementos".replace(",", ".")))

        # Cabeçalho
        hdr = [
            p("Algoritmo",     S_TABLE_HDR),
            p("Cenário",       S_TABLE_HDR),
            p("Tempo",         S_TABLE_HDR),
            p("Comparações",   S_TABLE_HDR),
            p("Swaps",         S_TABLE_HDR),
        ]
        tbl_data = [hdr]

        for algo in ALGOS:
            for sc_key, sc_label in SCENARIOS:
                r = get(data, algo, sc_key, size)
                if r:
                    tbl_data.append([
                        p(algo,                     S_TABLE_CELL_L),
                        p(sc_label,                 S_TABLE_CELL),
                        p(fmt_time(r["Tempo_ms"]),  S_TABLE_CELL),
                        p(fmt_num(r["Comparacoes"]),S_TABLE_CELL),
                        p(fmt_num(r["Swaps"]),      S_TABLE_CELL),
                    ])

        tbl = Table(tbl_data,
                    colWidths=[3.8*cm, 3.5*cm, 2.6*cm, 3.3*cm, 2.6*cm],
                    repeatRows=1)

        # Estilo dinâmico: destaca linhas de pior e melhor tempo
        style_cmds = [
            ("BACKGROUND",    (0,0), (-1,0),  C_PRIMARY),
            ("TEXTCOLOR",     (0,0), (-1,0),  C_WHITE),
            ("GRID",          (0,0), (-1,-1), 0.4, C_BORDER),
            ("LEFTPADDING",   (0,0), (-1,-1), 6),
            ("RIGHTPADDING",  (0,0), (-1,-1), 6),
            ("TOPPADDING",    (0,0), (-1,-1), 4),
            ("BOTTOMPADDING", (0,0), (-1,-1), 4),
            ("FONTNAME",      (0,1), (0,-1),  "Helvetica-Bold"),
        ]

        # Alterna cor das linhas por bloco de algoritmo
        algo_colors = [
            colors.HexColor("#f6f8fa"),
            colors.HexColor("#eaf5ff"),
            colors.HexColor("#f6f8fa"),
            colors.HexColor("#fff8e6"),
            colors.HexColor("#f6f8fa"),
        ]
        for i, algo in enumerate(ALGOS):
            for j in range(3):
                row = 1 + i * 3 + j
                style_cmds.append(("BACKGROUND", (0,row), (-1,row), algo_colors[i]))

        tbl.setStyle(TableStyle(style_cmds))
        story.append(tbl)
        story.append(sp(0.6))

    # ══════════════════════════════════════════════════════════════════════════
    # 4. GRÁFICOS DE DESEMPENHO
    # ══════════════════════════════════════════════════════════════════════════
    story.append(PageBreak())
    story.append(section("4. Gráficos de Desempenho"))
    story.append(hr())

    # 4.1 Tempo por cenário
    story.append(subsection("4.1 Tempo de Execução × Tamanho do Vetor"))
    story.append(p(
        "Os gráficos abaixo mostram, em <b>escala logarítmica</b>, como o tempo de execução "
        "cresce com o tamanho do vetor para cada cenário. A separação clara entre "
        "os grupos O(n²) (Insertion/Selection Sort) e O(n log n) (Merge/Quick Sort) "
        "demonstra empiricamente a diferença de complexidade."
    ))
    story.append(sp(0.3))
    for sc_key, sc_label in SCENARIOS:
        safe = sc_key.replace(" ", "_").replace(".", "")
        path = os.path.join(OUTPUT_DIR, f"tempo_por_cenario_{safe}.png")
        story.extend(img(path, caption=f"Figura: Tempo de execução — Cenário {sc_label}"))

    story.append(PageBreak())

    # 4.2 Heatmap
    story.append(subsection("4.2 Heatmap de Tempo (n = 50.000)"))
    story.append(p(
        "O heatmap consolida em uma única visualização o desempenho de todos os "
        "algoritmos nos três cenários para n = 50.000. Cores mais <b>verdes</b> indicam "
        "algoritmos rápidos; cores <b>vermelhas</b> indicam lentidão. "
        "A escala é logarítmica (log do tempo) para permitir a comparação visual "
        "entre valores de ordens de grandeza muito diferentes."
    ))
    story.append(sp(0.3))
    story.extend(img(
        os.path.join(OUTPUT_DIR, "heatmap_tempo.png"),
        caption="Figura: Heatmap de tempo de execução (ms) — n = 50.000"
    ))

    story.append(PageBreak())

    # 4.3 Barras
    story.append(subsection("4.3 Comparação Direta — n = 50.000, Cenário Aleatório"))
    story.append(p(
        "O gráfico de barras evidencia a diferença de desempenho em escala logarítmica. "
        "Counting Sort e Quick Sort dominam o cenário aleatório, enquanto "
        "Insertion Sort e Selection Sort ficam mais de <b>500× mais lentos</b> que o Quick Sort."
    ))
    story.append(sp(0.3))
    story.extend(img(
        os.path.join(OUTPUT_DIR, "barras_50k_aleatorio.png"),
        caption="Figura: Comparação de tempo (escala log) — n = 50.000, Aleatório"
    ))

    story.append(PageBreak())

    # 4.4 Comparações e Swaps
    story.append(subsection("4.4 Número de Comparações e Swaps"))
    story.append(p(
        "Os gráficos a seguir mostram como o número de comparações e trocas cresce "
        "com o tamanho do vetor. Observe que o <b>Selection Sort</b> apresenta "
        "sempre exatamente n(n−1)/2 comparações (independente do cenário), enquanto "
        "o número de swaps é apenas O(n) — ilustrando seu tradeoff único."
    ))
    story.append(sp(0.3))
    story.extend(img(
        os.path.join(OUTPUT_DIR, "comparacoes_por_cenario.png"),
        width=PAGE_W - 2*MARGIN,
        caption="Figura: Número de comparações × tamanho do vetor (3 cenários)"
    ))
    story.append(sp(0.4))
    story.extend(img(
        os.path.join(OUTPUT_DIR, "swaps_por_cenario.png"),
        width=PAGE_W - 2*MARGIN,
        caption="Figura: Número de swaps × tamanho do vetor (3 cenários)"
    ))

    story.append(PageBreak())

    # 4.5 Pior caso
    story.append(subsection("4.5 Análise de Pior Caso vs. Melhor Caso"))
    story.append(p(
        "O gráfico compara, para cada algoritmo, seu melhor e seu pior cenário "
        "com n = 50.000. A amplitude da barra (razão pior/melhor) revela a "
        "<b>sensibilidade ao dado de entrada</b>."
    ))
    story.append(sp(0.3))
    story.extend(img(
        os.path.join(OUTPUT_DIR, "pior_caso_analise.png"),
        caption="Figura: Melhor caso vs. Pior caso por algoritmo — n = 50.000"
    ))

    story.append(PageBreak())

    # 4.6 Complexidade teórica
    story.append(subsection("4.6 Dados Reais vs. Complexidade Teórica"))
    story.append(p(
        "Sobreposição das curvas de tempo medido com as curvas teóricas normalizadas "
        "O(n²) e O(n log n). No painel esquerdo, Insertion Sort e Selection Sort "
        "seguem <b>precisamente</b> a curva teórica quadrática. No painel direito, "
        "Merge Sort e Quick Sort ficam abaixo da curva O(n log n) — evidenciando "
        "constantes multiplicativas menores na prática."
    ))
    story.append(sp(0.3))
    story.extend(img(
        os.path.join(OUTPUT_DIR, "crescimento_complexidade.png"),
        width=PAGE_W - 2*MARGIN,
        caption="Figura: Crescimento real vs. crescimento teórico"
    ))

    # ══════════════════════════════════════════════════════════════════════════
    # 5. ANÁLISE CRÍTICA
    # ══════════════════════════════════════════════════════════════════════════
    story.append(PageBreak())
    story.append(section("5. Análise Crítica"))
    story.append(hr())

    story.append(subsection("5.1 Qual algoritmo foi melhor no pior caso?"))
    story.append(p(
        "O <b>Merge Sort</b> foi o melhor algoritmo em termos de garantia de pior caso. "
        "Seus tempos para n = 50.000 foram:"
    ))
    story.append(bullet("Aleatório:           23,35 ms"))
    story.append(bullet("Ordenado:            17,72 ms"))
    story.append(bullet("Inversamente Ord.:   28,21 ms"))
    story.append(sp(0.2))
    story.append(p(
        "A variação máxima foi de apenas <b>~60%</b> entre o melhor e o pior cenário, "
        "confirmando sua complexidade O(n log n) garantida. Em contraste, o Insertion Sort "
        "variou <b>27.000×</b> entre o melhor (0,27 ms) e o pior caso (7.384 ms). "
        "O Counting Sort foi o mais rápido em termos absolutos (1,17–1,45 ms), mas depende "
        "de domínio inteiro limitado — não é algoritmo de propósito geral."
    ))

    story.append(subsection("5.2 Por que o Quick Sort é rápido, mas pode falhar em vetores ordenados?"))
    story.append(p(
        "O Quick Sort é rápido na prática por três razões:"
    ))
    story.append(bullet(
        "<b>Cache-friendly</b>: o particionamento acessa a memória sequencialmente, "
        "aproveitando linhas de cache (localidade espacial)."
    ))
    story.append(bullet(
        "<b>In-place</b>: não requer vetor auxiliar, eliminando cópias de memória "
        "presentes no Merge Sort."
    ))
    story.append(bullet(
        "<b>Constante baixa</b>: as operações internas são simples comparações e trocas."
    ))
    story.append(sp(0.2))
    story.append(p(
        "Porém, sem a estratégia de pivô adequada, vetores <b>já ordenados</b> são seu "
        "pior inimigo. Com pivô = último elemento e vetor crescente, cada particionamento "
        "resulta em 0 | n−1 elementos — criando n níveis de recursão com n comparações cada "
        "→ <b>O(n²)</b>. Neste benchmark, a <b>mediana-de-três</b> evitou essa degradação: "
        "o Quick Sort completou 50.000 elementos ordenados em apenas <b>2,49 ms</b>, "
        "resultado competitivo com o Merge Sort (17,72 ms) nesse cenário."
    ))

    story.append(subsection("5.3 O que mudou de O(n²) para O(n log n) na prática?"))
    story.append(p(
        "A diferença entre O(n²) e O(n log n) é dramática conforme n cresce:"
    ))

    # Tabela de crescimento teórico
    theory_hdr = [
        p("n",          S_TABLE_HDR),
        p("n²",         S_TABLE_HDR),
        p("n·log₂(n)",  S_TABLE_HDR),
        p("Razão n²/n·log n", S_TABLE_HDR),
    ]
    theory_rows = [theory_hdr]
    for n in [1000, 5000, 10000, 50000, 100000, 1000000]:
        n2   = n * n
        nlog = n * math.log2(n)
        ratio = n2 / nlog
        theory_rows.append([
            p(f"{n:,}".replace(",","."),           S_TABLE_CELL),
            p(f"{n2:,.0f}".replace(",","."),       S_TABLE_CELL),
            p(f"{nlog:,.0f}".replace(",","."),     S_TABLE_CELL),
            p(f"<b>{ratio:.0f}×</b>",              S_TABLE_CELL),
        ])

    theory_tbl = Table(theory_rows, colWidths=[3*cm, 4*cm, 4*cm, 4.5*cm])
    theory_tbl.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (-1,0),  C_PRIMARY),
        ("TEXTCOLOR",     (0,0), (-1,0),  C_WHITE),
        ("ROWBACKGROUNDS",(0,1), (-1,-1), [C_WHITE, C_ROW_ALT]),
        ("GRID",          (0,0), (-1,-1), 0.4, C_BORDER),
        ("TOPPADDING",    (0,0), (-1,-1), 5),
        ("BOTTOMPADDING", (0,0), (-1,-1), 5),
        ("LEFTPADDING",   (0,0), (-1,-1), 8),
    ]))
    story.append(theory_tbl)
    story.append(sp(0.4))
    story.append(p(
        "Para n = 50.000, um algoritmo O(n²) executa <b>~3.000 vezes mais operações</b> "
        "que um O(n log n). Nos dados reais: Selection Sort realizou <b>1,25 bilhão</b> "
        "de comparações vs. <b>718 mil</b> do Merge Sort — razão de <b>1.740×</b>. "
        "Isso se reflete diretamente no tempo: 5.217 ms vs. 23 ms — razão de <b>226×</b>. "
        "A diferença de constante explica por que a razão de tempo não iguala a de operações."
    ))

    story.append(subsection("5.4 Resumo: Quando usar cada algoritmo?"))

    resumo_data = [
        [p("Algoritmo", S_TABLE_HDR), p("Use quando...", S_TABLE_HDR),
         p("Evite quando...", S_TABLE_HDR)],
        [p("Counting Sort",  S_TABLE_CELL_L),
         p("Inteiros em faixa limitada, máxima velocidade", S_TABLE_CELL_L),
         p("Dados reais/floats ou k muito grande", S_TABLE_CELL_L)],
        [p("Insertion Sort",  S_TABLE_CELL_L),
         p("n pequeno, dados quase ordenados, online", S_TABLE_CELL_L),
         p("n grande com dados aleatórios", S_TABLE_CELL_L)],
        [p("Merge Sort",      S_TABLE_CELL_L),
         p("Necessidade de O(n log n) garantido, dados estáveis", S_TABLE_CELL_L),
         p("RAM restrita (requer O(n) extra)", S_TABLE_CELL_L)],
        [p("Selection Sort",  S_TABLE_CELL_L),
         p("Memória EEPROM/Flash (mínimo de escritas)", S_TABLE_CELL_L),
         p("Qualquer cenário onde performance importa", S_TABLE_CELL_L)],
        [p("Quick Sort",      S_TABLE_CELL_L),
         p("Caso geral, dados aleatórios, propósito geral", S_TABLE_CELL_L),
         p("Pior caso garantido mandatório, stack pequena", S_TABLE_CELL_L)],
    ]
    resumo_tbl = Table(resumo_data, colWidths=[3.5*cm, 6.5*cm, 5.5*cm])
    resumo_tbl.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (-1,0),  C_PRIMARY),
        ("TEXTCOLOR",     (0,0), (-1,0),  C_WHITE),
        ("ROWBACKGROUNDS",(0,1), (-1,-1), [C_WHITE, C_ROW_ALT]),
        ("GRID",          (0,0), (-1,-1), 0.4, C_BORDER),
        ("FONTNAME",      (0,1), (0,-1),  "Helvetica-Bold"),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
        ("TOPPADDING",    (0,0), (-1,-1), 6),
        ("BOTTOMPADDING", (0,0), (-1,-1), 6),
        ("LEFTPADDING",   (0,0), (-1,-1), 7),
    ]))
    story.append(resumo_tbl)

    # ══════════════════════════════════════════════════════════════════════════
    # 6. CONCLUSÃO
    # ══════════════════════════════════════════════════════════════════════════
    story.append(PageBreak())
    story.append(section("6. Conclusão"))
    story.append(hr())
    story.append(p(
        "Este benchmark demonstrou empiricamente as diferenças de desempenho entre "
        "cinco algoritmos clássicos de ordenação interna, confirmando as previsões "
        "teóricas da análise assintótica:"
    ))
    story.append(sp(0.2))
    story.append(bullet(
        "O <b>Counting Sort</b> foi o mais rápido em termos absolutos (~1,4 ms para 50k), "
        "mas seu uso é restrito a inteiros em domínio limitado."
    ))
    story.append(bullet(
        "O <b>Quick Sort</b> com mediana-de-três mostrou o melhor equilíbrio para "
        "uso geral: rápido (~10 ms para 50k aleatório) e sem degradação nos cenários "
        "ordenados graças à estratégia de pivô."
    ))
    story.append(bullet(
        "O <b>Merge Sort</b> foi o mais previsível e seguro, com menor variação entre "
        "cenários — indispensável quando a garantia de O(n log n) é mandatória."
    ))
    story.append(bullet(
        "O <b>Insertion Sort</b> revelou comportamento dual extremo: imbatível em "
        "vetores ordenados (0,27 ms), mas catastrófico no pior caso (7,38 s)."
    ))
    story.append(bullet(
        "O <b>Selection Sort</b> confirmou seu nicho único: mínimo de swaps (O(n)) "
        "com comparações fixas — útil apenas quando o custo de escrita é dominante."
    ))
    story.append(sp(0.4))
    story.append(p(
        "A transição de O(n²) para O(n log n) representa, para n = 50.000, "
        "uma redução de <b>mais de 1.700× no número de operações</b> e "
        "<b>226× no tempo de execução</b>. Em aplicações de tempo real, "
        "sistemas embarcados e processamento de grandes volumes de dados, "
        "a escolha correta do algoritmo de ordenação é uma decisão de engenharia crítica."
    ))
    story.append(sp(0.6))
    story.append(HRFlowable(width="40%", thickness=1, color=C_ACCENT,
                             hAlign="CENTER", spaceAfter=10))
    story.append(p("Fim do Relatório", make_style("fim",
        fontSize=10, fontName="Helvetica-Oblique",
        textColor=C_MUTED, alignment=TA_CENTER)))

    # ── Build ─────────────────────────────────────────────────────────────────
    print(f"\n📄 Gerando PDF: {OUTPUT_PDF}")
    doc.build(story, onFirstPage=on_first_page, onLaterPages=on_page)
    print(f"✅ Relatório gerado com sucesso: {OUTPUT_PDF}")
    size_kb = os.path.getsize(OUTPUT_PDF) / 1024
    print(f"   Tamanho: {size_kb:.1f} KB")


if __name__ == "__main__":
    build_report()
