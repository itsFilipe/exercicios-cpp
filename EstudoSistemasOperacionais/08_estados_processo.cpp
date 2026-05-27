/*
 * DEMO 08: Estados de Processo e Mudança de Contexto
 * Compile: g++ -std=c++17 -pthread -o demo8 08_estados_processo.cpp
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <atomic>

std::mutex print_mtx;
std::atomic<int> ctx_switches{0};
enum class E{NEW,READY,RUNNING,WAITING,TERMINATED};

std::string nome(E e){switch(e){case E::NEW:return"NEW       ";case E::READY:return"READY     ";case E::RUNNING:return"RUNNING   ";case E::WAITING:return"WAITING   ";case E::TERMINATED:return"TERMINATED";}return"?";}

void log(const std::string& p,E de,E para,const std::string& motivo){
    std::lock_guard<std::mutex> lk(print_mtx);
    std::cout<<"  ["<<p<<"] "<<nome(de)<<"-> "<<nome(para)<<"  ("<<motivo<<")\n";
}

void ciclo(const std::string& nm, int burst, bool io, int io_ms){
    log(nm,E::NEW,E::READY,"admitido pelo SO");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    ctx_switches++; log(nm,E::READY,E::RUNNING,"CPU cedida");
    std::this_thread::sleep_for(std::chrono::milliseconds(burst/2));
    if(io){
        log(nm,E::RUNNING,E::WAITING,"pediu E/S"); ctx_switches++;
        std::this_thread::sleep_for(std::chrono::milliseconds(io_ms));
        log(nm,E::WAITING,E::READY,"E/S concluida");
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        ctx_switches++; log(nm,E::READY,E::RUNNING,"CPU cedida novamente");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(burst/2));
    log(nm,E::RUNNING,E::TERMINATED,"terminou");
}

int main(){
    std::cout<<"\n╔══════════════════════════════════════════════════════╗\n";
    std::cout<<  "║   DEMO 08: Estados de Processo + Mudanca Contexto   ║\n";
    std::cout<<  "╚══════════════════════════════════════════════════════╝\n";
    std::cout<<"\n  5 estados: NEW -> READY -> RUNNING -> WAITING -> TERMINATED\n";
    std::cout<<"  Mudanca contexto: SO salva registradores+PC do atual\n";
    std::cout<<"  e carrega os do proximo. Overhead real de CPU!\n";
    std::cout<<"\n  P1=CPU-bound  P2=IO-bound  P3=IO-bound\n";
    std::cout<<"  "<<std::string(58,'-')<<"\n";
    std::thread t1(ciclo,"P1-CPU",300,false,0);
    std::thread t2(ciclo,"P2-IO ",200,true,150);
    std::thread t3(ciclo,"P3-IO ",250,true,200);
    t1.join();t2.join();t3.join();
    std::cout<<"  "<<std::string(58,'-')<<"\n";
    std::cout<<"  Trocas de contexto: "<<ctx_switches<<"\n";
    std::cout<<"\n  P1 fica RUNNING quase todo o tempo.\n";
    std::cout<<"  P2/P3 alternam RUNNING <-> WAITING (IO-bound).\n";
    std::cout<<"  Linux faz ~1000 trocas de contexto por segundo!\n\n";
    return 0;
}
