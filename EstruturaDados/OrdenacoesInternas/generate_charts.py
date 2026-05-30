"""
generate_charts.py
==================
Gera todos os gráficos para o relatório técnico de Ordenações Internas.

Gráficos produzidos (salvos em results/):
  1. tempo_por_cenario_<cenário>.png  — linhas: tempo × tamanho (um por cenário)
  2. comparacoes_por_cenario.png      — linhas: comparações × tamanho
  3. swaps_por_cenario.png            — linhas: swaps × tamanho
  4. heatmap_tempo.png                — heatmap tempo (ms) por algoritmo × cenário (50k)
  5. barras_50k_aleatorio.png         — barras comparativas (tempo) para 50k aleatório
  6. pior_caso_analise.png            — análise pior caso: cada algoritmo em seu pior cenário

Uso:
  python3 generate_charts.py

Requisitos:
  pip install pandas matplotlib numpy
"""

import os
import csv
import math
import numpy as np
import matplotlib
matplotlib.use("Agg")          # backend sem janela (funciona em servidores/CI)
import matplotlib.pyplot as plt
import matplotlib.ticker as mticker
from matplotlib.colors import LinearSegmentedColormap

# ── Configuração global de estilo ────────────────────────────────────────────
plt.rcParams.update({
    "figure.dpi":        150,
    "figure.facecolor":  "#0d1117",
    "axes.facecolor":    "#161b22",
    "axes.edgecolor":    "#30363d",
    "axes.labelcolor":   "#c9d1d9",
    "axes.titlecolor":   "#f0f6fc",
    "axes.grid":         True,
    "grid.color":        "#21262d",
    "grid.linestyle":    "--",
    "grid.linewidth":    0.6,
    "xtick.color":       "#8b949e",
    "ytick.color":       "#8b949e",
    "legend.facecolor":  "#161b22",
    "legend.edgecolor":  "#30363d",
    "legend.labelcolor": "#c9d1d9",
    "text.color":        "#c9d1d9",
    "font.family":       "DejaVu Sans",
    "font.size":         10,
    "lines.linewidth":   2.2,
    "lines.markersize":  7,
})

# ── Paleta de cores por algoritmo ────────────────────────────────────────────
COLORS = {
    "Counting Sort":  "#58a6ff",   # azul
    "Insertion Sort": "#f78166",   # laranja-vermelho
    "Merge Sort":     "#56d364",   # verde
    "Selection Sort": "#d2a8ff",   # roxo
    "Quick Sort":     "#ffa657",   # laranja dourado
}

MARKERS = {
    "Counting Sort":  "o",
    "Insertion Sort": "s",
    "Merge Sort":     "^",
    "Selection Sort": "D",
    "Quick Sort":     "P",
}

ALGO_ORDER = [
    "Counting Sort", "Insertion Sort", "Merge Sort", "Selection Sort", "Quick Sort"
]

SCENARIO_ORDER = ["Aleatorio", "Ordenado", "Inv. Ordenado"]

SCENARIO_LABELS = {
    "Aleatorio":     "Aleatório",
    "Ordenado":      "Ordenado",
    "Inv. Ordenado": "Inversamente Ordenado",
}

OUTPUT_DIR = "results"

# ── Leitura do CSV ────────────────────────────────────────────────────────────
def load_csv(path: str) -> list[dict]:
    rows = []
    with open(path, newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            row["Tamanho"]     = int(row["Tamanho"])
            row["Tempo_ms"]    = float(row["Tempo_ms"])
            row["Comparacoes"] = int(row["Comparacoes"])
            row["Swaps"]       = int(row["Swaps"])
            rows.append(row)
    return rows


def filter_data(data, algo=None, scenario=None, size=None):
    result = data
    if algo:     result = [r for r in result if r["Algoritmo"] == algo]
    if scenario: result = [r for r in result if r["Cenario"]   == scenario]
    if size:     result = [r for r in result if r["Tamanho"]   == size]
    return result


def get_sizes(data):
    return sorted(set(r["Tamanho"] for r in data))


# ── Helpers de plotagem ───────────────────────────────────────────────────────
def save(fig, name: str):
    path = os.path.join(OUTPUT_DIR, name)
    fig.savefig(path, bbox_inches="tight", facecolor=fig.get_facecolor())
    print(f"  ✔ Salvo: {path}")
    plt.close(fig)


def fmt_number(n):
    """Formata número grande com sufixo k/M."""
    if n >= 1_000_000:
        return f"{n/1_000_000:.1f}M"
    if n >= 1_000:
        return f"{n/1_000:.0f}k"
    return str(n)


# ════════════════════════════════════════════════════════════════════════════
# GRÁFICO 1 — Linhas: Tempo de execução × Tamanho (um por cenário)
# ════════════════════════════════════════════════════════════════════════════
def plot_time_by_scenario(data):
    sizes = get_sizes(data)
    x = np.arange(len(sizes))
    x_labels = [fmt_number(s) for s in sizes]

    for scenario in SCENARIO_ORDER:
        fig, ax = plt.subplots(figsize=(9, 5.5))
        fig.suptitle(
            f"Tempo de Execução × Tamanho do Vetor\nCenário: {SCENARIO_LABELS[scenario]}",
            fontsize=13, fontweight="bold", color="#f0f6fc", y=1.01
        )

        for algo in ALGO_ORDER:
            pts = filter_data(data, algo=algo, scenario=scenario)
            pts.sort(key=lambda r: r["Tamanho"])
            y = [r["Tempo_ms"] for r in pts]

            ax.plot(x, y,
                    color=COLORS[algo],
                    marker=MARKERS[algo],
                    label=algo)

            # Rótulo no ponto final
            ax.annotate(
                f"{y[-1]:.1f}ms",
                xy=(x[-1], y[-1]),
                xytext=(4, 0), textcoords="offset points",
                fontsize=7.5, color=COLORS[algo], va="center"
            )

        ax.set_xticks(x)
        ax.set_xticklabels(x_labels)
        ax.set_xlabel("Tamanho do Vetor (n)", labelpad=8)
        ax.set_ylabel("Tempo (ms)", labelpad=8)
        ax.set_yscale("log")
        ax.yaxis.set_major_formatter(mticker.FuncFormatter(lambda v, _: f"{v:.2g}"))
        ax.legend(loc="upper left", fontsize=9)
        ax.set_title("")
        fig.tight_layout()

        safe_name = scenario.replace(" ", "_").replace(".", "")
        save(fig, f"tempo_por_cenario_{safe_name}.png")


# ════════════════════════════════════════════════════════════════════════════
# GRÁFICO 2 — Linhas: Comparações × Tamanho (todos cenários, grade 1×3)
# ════════════════════════════════════════════════════════════════════════════
def plot_comparisons(data):
    sizes = get_sizes(data)
    x = np.arange(len(sizes))
    x_labels = [fmt_number(s) for s in sizes]

    fig, axes = plt.subplots(1, 3, figsize=(16, 5.5), sharey=False)
    fig.suptitle("Número de Comparações × Tamanho do Vetor",
                 fontsize=13, fontweight="bold", color="#f0f6fc")

    for ax, scenario in zip(axes, SCENARIO_ORDER):
        for algo in ALGO_ORDER:
            pts = filter_data(data, algo=algo, scenario=scenario)
            pts.sort(key=lambda r: r["Tamanho"])
            y = [r["Comparacoes"] for r in pts]
            ax.plot(x, y, color=COLORS[algo], marker=MARKERS[algo], label=algo)

        ax.set_xticks(x)
        ax.set_xticklabels(x_labels)
        ax.set_xlabel("Tamanho (n)", labelpad=6)
        ax.set_ylabel("Comparações" if scenario == "Aleatorio" else "", labelpad=6)
        ax.set_title(SCENARIO_LABELS[scenario], fontsize=10, pad=6)
        ax.set_yscale("log")
        ax.yaxis.set_major_formatter(
            mticker.FuncFormatter(lambda v, _: fmt_number(int(v)))
        )
        if scenario == "Aleatorio":
            ax.legend(loc="upper left", fontsize=8)

    fig.tight_layout()
    save(fig, "comparacoes_por_cenario.png")


# ════════════════════════════════════════════════════════════════════════════
# GRÁFICO 3 — Linhas: Swaps × Tamanho (todos cenários, grade 1×3)
# ════════════════════════════════════════════════════════════════════════════
def plot_swaps(data):
    sizes = get_sizes(data)
    x = np.arange(len(sizes))
    x_labels = [fmt_number(s) for s in sizes]

    fig, axes = plt.subplots(1, 3, figsize=(16, 5.5), sharey=False)
    fig.suptitle("Número de Trocas (Swaps) × Tamanho do Vetor",
                 fontsize=13, fontweight="bold", color="#f0f6fc")

    for ax, scenario in zip(axes, SCENARIO_ORDER):
        for algo in ALGO_ORDER:
            pts = filter_data(data, algo=algo, scenario=scenario)
            pts.sort(key=lambda r: r["Tamanho"])
            y = [r["Swaps"] for r in pts]

            # Adiciona 1 para poder usar log (evitar log(0))
            y_plot = [max(v, 1) for v in y]
            ax.plot(x, y_plot, color=COLORS[algo], marker=MARKERS[algo], label=algo)

        ax.set_xticks(x)
        ax.set_xticklabels(x_labels)
        ax.set_xlabel("Tamanho (n)", labelpad=6)
        ax.set_ylabel("Swaps" if scenario == "Aleatorio" else "", labelpad=6)
        ax.set_title(SCENARIO_LABELS[scenario], fontsize=10, pad=6)
        ax.set_yscale("log")
        ax.yaxis.set_major_formatter(
            mticker.FuncFormatter(lambda v, _: fmt_number(int(v)))
        )
        if scenario == "Aleatorio":
            ax.legend(loc="upper left", fontsize=8)

    fig.tight_layout()
    save(fig, "swaps_por_cenario.png")


# ════════════════════════════════════════════════════════════════════════════
# GRÁFICO 4 — Heatmap: Tempo (ms) para 50k elementos
# ════════════════════════════════════════════════════════════════════════════
def plot_heatmap(data):
    size = 50_000
    matrix = []
    row_labels = ALGO_ORDER
    col_labels  = [SCENARIO_LABELS[s] for s in SCENARIO_ORDER]

    for algo in ALGO_ORDER:
        row = []
        for scenario in SCENARIO_ORDER:
            pts = filter_data(data, algo=algo, scenario=scenario, size=size)
            row.append(pts[0]["Tempo_ms"] if pts else 0.0)
        matrix.append(row)

    mat = np.array(matrix, dtype=float)
    # Normaliza por log para não deixar Counting Sort sumir na escala
    mat_log = np.log1p(mat)

    # Paleta: verde escuro → amarelo → vermelho
    cmap = LinearSegmentedColormap.from_list(
        "benchmark",
        ["#0d4429", "#56d364", "#ffa657", "#f78166", "#8b0000"]
    )

    fig, ax = plt.subplots(figsize=(9, 5))
    fig.suptitle(f"Heatmap de Tempo de Execução (ms) — n = {fmt_number(size)}",
                 fontsize=13, fontweight="bold", color="#f0f6fc")

    im = ax.imshow(mat_log, cmap=cmap, aspect="auto")

    ax.set_xticks(range(len(col_labels)))
    ax.set_xticklabels(col_labels, fontsize=10)
    ax.set_yticks(range(len(row_labels)))
    ax.set_yticklabels(row_labels, fontsize=10)
    ax.tick_params(top=False, bottom=True, labeltop=False, labelbottom=True)
    ax.grid(False)

    # Anota cada célula com o valor real em ms
    for i in range(len(ALGO_ORDER)):
        for j in range(len(SCENARIO_ORDER)):
            val = mat[i, j]
            text = f"{val:.2f}ms" if val < 1000 else f"{val/1000:.2f}s"
            brightness = mat_log[i, j] / mat_log.max()
            txt_color  = "#0d1117" if brightness > 0.55 else "#f0f6fc"
            ax.text(j, i, text, ha="center", va="center",
                    fontsize=10, fontweight="bold", color=txt_color)

    cbar = fig.colorbar(im, ax=ax, fraction=0.03, pad=0.02)
    cbar.set_label("log(tempo + 1)", color="#c9d1d9", fontsize=8)
    cbar.ax.yaxis.set_tick_params(color="#8b949e")
    plt.setp(cbar.ax.yaxis.get_ticklabels(), color="#8b949e")

    fig.tight_layout()
    save(fig, "heatmap_tempo.png")


# ════════════════════════════════════════════════════════════════════════════
# GRÁFICO 5 — Barras: Tempo para n=50k, cenário Aleatório
# ════════════════════════════════════════════════════════════════════════════
def plot_bars_50k(data):
    size     = 50_000
    scenario = "Aleatorio"

    algos  = []
    tempos = []
    for algo in ALGO_ORDER:
        pts = filter_data(data, algo=algo, scenario=scenario, size=size)
        if pts:
            algos.append(algo)
            tempos.append(pts[0]["Tempo_ms"])

    fig, ax = plt.subplots(figsize=(10, 5.5))
    fig.suptitle(
        f"Tempo de Execução — n = {fmt_number(size)}, Cenário: Aleatório\n"
        f"(escala logarítmica)",
        fontsize=12, fontweight="bold", color="#f0f6fc"
    )

    bars = ax.bar(
        algos, tempos,
        color=[COLORS[a] for a in algos],
        edgecolor="#0d1117", linewidth=0.8,
        width=0.55
    )

    for bar, val in zip(bars, tempos):
        text = f"{val:.2f}ms" if val < 1000 else f"{val/1000:.2f}s"
        ax.text(
            bar.get_x() + bar.get_width() / 2,
            bar.get_height() * 1.15,
            text, ha="center", va="bottom",
            fontsize=9.5, fontweight="bold",
            color="#f0f6fc"
        )

    ax.set_yscale("log")
    ax.set_ylabel("Tempo (ms) — escala log", labelpad=8)
    ax.set_xlabel("")
    ax.yaxis.set_major_formatter(
        mticker.FuncFormatter(lambda v, _: f"{v:.1f}ms" if v < 1000 else f"{v/1000:.1f}s")
    )
    ax.tick_params(axis="x", labelsize=10)
    fig.tight_layout()
    save(fig, "barras_50k_aleatorio.png")


# ════════════════════════════════════════════════════════════════════════════
# GRÁFICO 6 — Análise de pior caso: cada algoritmo no seu cenário mais lento
# ════════════════════════════════════════════════════════════════════════════
def plot_worst_case(data):
    """
    Para cada algoritmo, encontra o cenário com o maior tempo em n=50k
    e plota uma barra dupla: melhor caso vs pior caso.
    """
    size = 50_000

    best_times  = []
    worst_times = []
    worst_keys  = []   # chave original do cenário (e.g. "Aleatorio")

    for algo in ALGO_ORDER:
        times_by_scenario = {}
        for scenario in SCENARIO_ORDER:
            pts = filter_data(data, algo=algo, scenario=scenario, size=size)
            if pts:
                times_by_scenario[scenario] = pts[0]["Tempo_ms"]

        if not times_by_scenario:
            continue

        best_scenario  = min(times_by_scenario, key=times_by_scenario.get)
        worst_scenario = max(times_by_scenario, key=times_by_scenario.get)

        best_times.append(times_by_scenario[best_scenario])
        worst_times.append(times_by_scenario[worst_scenario])
        worst_keys.append(worst_scenario)   # guarda a chave, não o label

    x      = np.arange(len(ALGO_ORDER))
    width  = 0.35

    fig, ax = plt.subplots(figsize=(11, 6))
    fig.suptitle(
        f"Melhor Caso vs. Pior Caso — n = {fmt_number(size)}\n"
        "(o pior caso de cada algoritmo está indicado no eixo X)",
        fontsize=12, fontweight="bold", color="#f0f6fc"
    )

    bars_best  = ax.bar(x - width/2, best_times,  width, label="Melhor Caso",
                        color="#56d364", edgecolor="#0d1117", linewidth=0.8)
    bars_worst = ax.bar(x + width/2, worst_times, width, label="Pior Caso",
                        color="#f78166", edgecolor="#0d1117", linewidth=0.8)

    for bar, val in zip(bars_best, best_times):
        text = f"{val:.2f}ms" if val < 1000 else f"{val/1000:.2f}s"
        ax.text(bar.get_x() + bar.get_width()/2, bar.get_height()*1.1,
                text, ha="center", va="bottom", fontsize=8, color="#56d364")

    for bar, val, wkey in zip(bars_worst, worst_times, worst_keys):
        text = f"{val:.1f}ms" if val < 1000 else f"{val/1000:.2f}s"
        ax.text(bar.get_x() + bar.get_width()/2, bar.get_height()*1.1,
                text, ha="center", va="bottom", fontsize=8, color="#f78166")

    ax.set_xticks(x)
    ax.set_xticklabels(ALGO_ORDER, fontsize=9.5)
    ax.set_yscale("log")
    ax.set_ylabel("Tempo (ms) — escala log", labelpad=8)
    ax.yaxis.set_major_formatter(
        mticker.FuncFormatter(lambda v, _: f"{v:.1f}ms" if v < 1000 else f"{v/1000:.1f}s")
    )
    ax.legend(fontsize=10)

    # Anota o pior cenário abaixo de cada grupo de barras
    for i, wkey in enumerate(worst_keys):
        label = SCENARIO_LABELS[wkey]
        short = label if len(label) <= 10 else label[:7] + "…"
        ax.text(x[i] + width/2, worst_times[i] * 0.5,
                f"← {short}", ha="left", va="center",
                fontsize=7, color="#ffa657", rotation=0)

    fig.tight_layout()
    save(fig, "pior_caso_analise.png")


# ════════════════════════════════════════════════════════════════════════════
# GRÁFICO 7 — Curva de crescimento teórico sobreposta aos dados reais (50k ref)
# ════════════════════════════════════════════════════════════════════════════
def plot_complexity_growth(data):
    """
    Plota a curva de tempo medido no cenário aleatório e sobrepõe
    as curvas de crescimento teórico normalizadas.
    """
    sizes  = get_sizes(data)
    xs     = np.array(sizes, dtype=float)

    fig, axes = plt.subplots(1, 2, figsize=(14, 5.5))
    fig.suptitle("Crescimento do Tempo de Execução — Dados Reais vs. Complexidade Teórica",
                 fontsize=12, fontweight="bold", color="#f0f6fc")

    # — Painel esquerdo: algoritmos O(n²) —
    ax_quad = axes[0]
    ax_quad.set_title("Algoritmos O(n²)", fontsize=10, pad=6)

    quad_algos = ["Insertion Sort", "Selection Sort"]
    for algo in quad_algos:
        pts = filter_data(data, algo=algo, scenario="Aleatorio")
        pts.sort(key=lambda r: r["Tamanho"])
        y = np.array([r["Tempo_ms"] for r in pts])
        ax_quad.plot(xs, y, color=COLORS[algo], marker=MARKERS[algo], label=algo)

    # Curva teórica n² normalizada pelo ponto de 5k do Selection Sort
    ref_pts = filter_data(data, algo="Selection Sort", scenario="Aleatorio", size=5000)
    if ref_pts:
        t0 = ref_pts[0]["Tempo_ms"]
        n0 = 5000.0
        y_theory = t0 * (xs / n0) ** 2
        ax_quad.plot(xs, y_theory, "--", color="#8b949e", linewidth=1.2, label="Teórico O(n²)")

    ax_quad.set_yscale("log")
    ax_quad.set_xlabel("Tamanho (n)", labelpad=6)
    ax_quad.set_ylabel("Tempo (ms)", labelpad=6)
    ax_quad.set_xticks(xs)
    ax_quad.set_xticklabels([fmt_number(int(s)) for s in xs])
    ax_quad.yaxis.set_major_formatter(
        mticker.FuncFormatter(lambda v, _: f"{v:.1f}ms" if v < 1000 else f"{v/1000:.1f}s")
    )
    ax_quad.legend(fontsize=9)

    # — Painel direito: algoritmos O(n log n) e O(n+k) —
    ax_nlog = axes[1]
    ax_nlog.set_title("Algoritmos O(n log n) e O(n+k)", fontsize=10, pad=6)

    fast_algos = ["Merge Sort", "Quick Sort", "Counting Sort"]
    for algo in fast_algos:
        pts = filter_data(data, algo=algo, scenario="Aleatorio")
        pts.sort(key=lambda r: r["Tamanho"])
        y = np.array([r["Tempo_ms"] for r in pts])
        ax_nlog.plot(xs, y, color=COLORS[algo], marker=MARKERS[algo], label=algo)

    # Curva teórica n·log(n) normalizada pelo ponto de 5k do Merge Sort
    ref_pts2 = filter_data(data, algo="Merge Sort", scenario="Aleatorio", size=5000)
    if ref_pts2:
        t0 = ref_pts2[0]["Tempo_ms"]
        n0 = 5000.0
        y_theory2 = t0 * (xs * np.log2(xs)) / (n0 * math.log2(n0))
        ax_nlog.plot(xs, y_theory2, "--", color="#8b949e", linewidth=1.2, label="Teórico O(n log n)")

    ax_nlog.set_yscale("log")
    ax_nlog.set_xlabel("Tamanho (n)", labelpad=6)
    ax_nlog.set_ylabel("Tempo (ms)", labelpad=6)
    ax_nlog.set_xticks(xs)
    ax_nlog.set_xticklabels([fmt_number(int(s)) for s in xs])
    ax_nlog.yaxis.set_major_formatter(
        mticker.FuncFormatter(lambda v, _: f"{v:.3f}ms" if v < 1 else (f"{v:.1f}ms" if v < 1000 else f"{v/1000:.1f}s"))
    )
    ax_nlog.legend(fontsize=9)

    fig.tight_layout()
    save(fig, "crescimento_complexidade.png")


# ════════════════════════════════════════════════════════════════════════════
# MAIN
# ════════════════════════════════════════════════════════════════════════════
def main():
    csv_path = os.path.join(OUTPUT_DIR, "benchmark_results.csv")
    if not os.path.exists(csv_path):
        print(f"[ERRO] CSV não encontrado: {csv_path}")
        print("Execute o benchmark primeiro: ./benchmark")
        return

    print(f"\n📊 Lendo dados de: {csv_path}")
    data = load_csv(csv_path)
    print(f"   {len(data)} linhas carregadas.\n")

    print("Gerando gráficos...\n")
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    plot_time_by_scenario(data)       # 3 arquivos (um por cenário)
    plot_comparisons(data)            # comparacoes_por_cenario.png
    plot_swaps(data)                  # swaps_por_cenario.png
    plot_heatmap(data)                # heatmap_tempo.png
    plot_bars_50k(data)               # barras_50k_aleatorio.png
    plot_worst_case(data)             # pior_caso_analise.png
    plot_complexity_growth(data)      # crescimento_complexidade.png

    print(f"\n✅ Todos os gráficos salvos em ./{OUTPUT_DIR}/")
    print("   Arquivos gerados:")
    for f in sorted(os.listdir(OUTPUT_DIR)):
        if f.endswith(".png"):
            print(f"     • {f}")


if __name__ == "__main__":
    main()
