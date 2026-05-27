/*
 * DEMO 02: Deadlock e Soluções
 * Compile: g++ -std=c++17 -pthread -o demo2 02_deadlock.cpp
 *
 * As 4 condições de Coffman demonstradas.
 * FIX 1: ordenação de locks
 * FIX 2: std::scoped_lock (C++17)
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

std::mutex recurso_A, recurso_B;
std::mutex barreira_mtx;
std::condition_variable barreira_cv;
int prontos = 0;
std::atomic<bool> deadlock_ocorreu{false};

void aguardar_ambos_prontos() {
    std::unique_lock<std::mutex> lk(barreira_mtx);
    prontos++;
    barreira_cv.notify_all();
    barreira_cv.wait(lk, []{ return prontos >= 2; });
}

void processo_1_problema() {
    std::cout << "  [P1] Travando Recurso A...\n";
    recurso_A.lock();
    std::cout << "  [P1] Tem A! Esperando P2 pegar B...\n";
    aguardar_ambos_prontos();
    std::cout << "  [P1] Tentando pegar B... (P2 ja tem!)\n";
    if (recurso_B.try_lock()) { recurso_B.unlock(); }
    else { std::cout << "  [P1] BLOQUEADO! DEADLOCK!\n"; deadlock_ocorreu = true; }
    recurso_A.unlock();
}

void processo_2_problema() {
    std::cout << "  [P2] Travando Recurso B...\n";
    recurso_B.lock();
    std::cout << "  [P2] Tem B! Esperando P1 pegar A...\n";
    aguardar_ambos_prontos();
    std::cout << "  [P2] Tentando pegar A... (P1 ja tem!)\n";
    if (recurso_A.try_lock()) { recurso_A.unlock(); }
    else { std::cout << "  [P2] BLOQUEADO! DEADLOCK!\n"; deadlock_ocorreu = true; }
    recurso_B.unlock();
}

void fix1_processo(int id) {
    std::string p = "  [P" + std::to_string(id) + "]";
    recurso_A.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    recurso_B.lock();
    std::cout << p << " Tem A e B! Trabalhando e liberando.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    recurso_B.unlock(); recurso_A.unlock();
}

void fix2_processo(int id) {
    std::string p = "  [P" + std::to_string(id) + "]";
    std::scoped_lock lock(recurso_A, recurso_B); // atomico, anti-deadlock
    std::cout << p << " scoped_lock: Tem A e B simultaneamente!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

void sep(const std::string& t) {
    std::cout << "\n" << std::string(58,'-') << "\n  " << t << "\n" << std::string(58,'-') << "\n";
}

int main() {
    std::cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    std::cout <<   "║         DEMO 02: Deadlock e suas Solucoes               ║\n";
    std::cout <<   "╚══════════════════════════════════════════════════════════╝\n";
    std::cout << "\n  4 condicoes de Coffman: Excl. Mutua + Manter&Esperar\n";
    std::cout << "  + Nao-preempcao + Espera Circular => DEADLOCK\n";

    sep("PROBLEMA: Deadlock (P1 tem A quer B; P2 tem B quer A)");
    prontos = 0; deadlock_ocorreu = false;
    std::thread t1(processo_1_problema), t2(processo_2_problema);
    t1.join(); t2.join();
    if (deadlock_ocorreu) std::cout << "\n  Em producao ficariam travados PARA SEMPRE!\n";

    sep("FIX 1: Ordenacao de Locks (ambos: A antes de B)");
    std::thread t3(fix1_processo, 1), t4(fix1_processo, 2);
    t3.join(); t4.join();
    std::cout << "  OK! Ordem consistente elimina Espera Circular.\n";

    sep("FIX 2: std::scoped_lock (C++17 - recomendado)");
    std::thread t5(fix2_processo, 1), t6(fix2_processo, 2);
    t5.join(); t6.join();
    std::cout << "  OK! Aquisicao atomica de multiplos mutexes.\n\n";
    return 0;
}
