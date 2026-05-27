CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

TARGETS  = demo1 demo2 demo3 demo4 demo5 demo6 demo7 demo8 demo9

all: $(TARGETS)
	@echo ""
	@echo "==================================================="
	@echo "  Todos os programas compilados!"
	@echo "  make run1  -> Race Condition vs. Mutex"
	@echo "  make run2  -> Deadlock e Solucoes"
	@echo "  make run3  -> Escalonamento (FIFO/SJF/RR)"
	@echo "  make run4  -> Alocacao de Memoria"
	@echo "  make run5  -> Memoria Virtual / Page Fault"
	@echo "  make run6  -> Segmentacao de Memoria"
	@echo "  make run7  -> Semaforo / Produtor-Consumidor"
	@echo "  make run8  -> Estados de Processo"
	@echo "  make run9  -> Starvation e Aging"
	@echo "==================================================="

demo1: 01_condicao_de_corrida.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
demo2: 02_deadlock.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
demo3: 03_escalonamento.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
demo4: 04_alocacao_memoria.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
demo5: 05_memoria_virtual.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
demo6: 06_segmentacao.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
demo7: 07_semaforo_produtor_consumidor.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
demo8: 08_estados_processo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
demo9: 09_starvation_prioridade.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run1: demo1
	./demo1
run2: demo2
	./demo2
run3: demo3
	./demo3
run4: demo4
	./demo4
run5: demo5
	./demo5
run6: demo6
	./demo6
run7: demo7
	./demo7
run8: demo8
	./demo8
run9: demo9
	./demo9

runall: all
	$(MAKE) run1 run2 run3 run4 run5 run6 run7 run8 run9

clean:
	rm -f $(TARGETS)

.PHONY: all clean runall run1 run2 run3 run4 run5 run6 run7 run8 run9
