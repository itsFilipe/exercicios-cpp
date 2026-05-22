/*
 * DEMO 07: Semáforo - Produtor e Consumidor
 * Compile: g++ -std=c++17 -pthread -o demo7 07_semaforo_produtor_consumidor.cpp
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <chrono>
#include <iomanip>

class Semaforo {
    int v; std::mutex m; std::condition_variable cv;
public:
    explicit Semaforo(int val):v(val){}
    void wait(){std::unique_lock<std::mutex> lk(m);cv.wait(lk,[this]{return v>0;});v--;}
    void signal(){std::lock_guard<std::mutex> lk(m);v++;cv.notify_one();}
    int get(){std::lock_guard<std::mutex> lk(m);return v;}
};

const int CAP=5;
std::queue<int> buf;
std::mutex buf_mtx, print_mtx;
Semaforo sem_vagas(CAP), sem_itens(0);
std::atomic<int> total_prod{0}, total_cons{0};

void log_buf(const std::string& quem){
    std::lock_guard<std::mutex> lk(print_mtx);
    std::cout<<"  "<<std::setw(24)<<std::left<<quem<<" Buffer:[";
    auto tmp=buf; while(!tmp.empty()){std::cout<<tmp.front()<<" ";tmp.pop();}
    for(int i=(int)buf.size();i<CAP;i++) std::cout<<"_ ";
    std::cout<<"] vagas="<<sem_vagas.get()<<" itens="<<sem_itens.get()<<"\n";
}

void produtor(int id, int qtd){
    for(int i=0;i<qtd;i++){
        int item=id*10+i;
        sem_vagas.wait();
        {std::lock_guard<std::mutex> lk(buf_mtx);buf.push(item);}
        sem_itens.signal(); total_prod++;
        log_buf("[Prod "+std::to_string(id)+"] +"+std::to_string(item));
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
}

void consumidor(int id, int qtd){
    for(int i=0;i<qtd;i++){
        sem_itens.wait();
        int item;
        {std::lock_guard<std::mutex> lk(buf_mtx);item=buf.front();buf.pop();}
        sem_vagas.signal(); total_cons++;
        log_buf("[Cons "+std::to_string(id)+"] -"+std::to_string(item));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main(){
    std::cout<<"\n╔══════════════════════════════════════════════════════╗\n";
    std::cout<<  "║   DEMO 07: Semaforo - Produtor e Consumidor         ║\n";
    std::cout<<  "╚══════════════════════════════════════════════════════╝\n";
    std::cout<<"\n  Semaforo: wait()/P() bloqueia se 0; signal()/V() acorda\n";
    std::cout<<"  sem_vagas (ini="<<CAP<<"): produtores esperam se buffer cheio\n";
    std::cout<<"  sem_itens (ini=0): consumidores esperam se buffer vazio\n";
    std::cout<<"  Buffer capacidade: "<<CAP<<" | 2 produtores + 3 consumidores\n";
    std::cout<<"\n  "<<std::string(58,'-')<<"\n";
    std::thread p1(produtor,1,5),p2(produtor,2,5);
    std::thread c1(consumidor,1,3),c2(consumidor,2,3),c3(consumidor,3,4);
    p1.join();p2.join();c1.join();c2.join();c3.join();
    std::cout<<"  "<<std::string(58,'-')<<"\n";
    std::cout<<"  Produzido:"<<total_prod<<"  Consumido:"<<total_cons<<"  Buffer final:"<<buf.size()<<"\n";
    std::cout<<"\n  LICAO: Semaforo coordena sem busy-wait.\n";
    std::cout<<"  Mutex binario = semaforo inicializado com 1.\n\n";
    return 0;
}
