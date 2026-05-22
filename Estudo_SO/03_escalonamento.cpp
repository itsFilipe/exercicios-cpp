/*
 * DEMO 03: Escalonamento de Processos
 * Compile: g++ -std=c++17 -o demo3 03_escalonamento.cpp
 *
 * Algoritmos: FIFO, SJF (nao-preemptivo), Round-Robin
 * Saida: Gantt chart + metricas de desempenho
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <iomanip>

struct Processo {
    std::string nome; int chegada, burst, inicio=0, fim=0, espera=0, retorno=0;
};
struct Fatia { std::string nome; int dur; };

void gantt(const std::vector<Fatia>& g) {
    std::cout << "\n  ";
    for (auto& f : g) { int w=f.dur*2; std::string l=f.nome; while((int)l.size()<w)l+=" "; std::cout<<"|"<<l.substr(0,w); }
    std::cout<<"|\n  ";
    int t=0; std::cout<<t;
    for (auto& f : g) { t+=f.dur; std::cout<<std::setw(f.dur*2)<<t; }
    std::cout<<"\n";
}

void metricas(const std::vector<Processo>& p) {
    double se=0,sr=0;
    std::cout<<"\n  "<<std::left<<std::setw(6)<<"Nome"<<std::setw(10)<<"Chegada"<<std::setw(8)<<"Burst"<<std::setw(10)<<"Espera"<<"Retorno\n";
    std::cout<<"  "<<std::string(42,'-')<<"\n";
    for (auto& x:p) { se+=x.espera; sr+=x.retorno; std::cout<<"  "<<std::setw(6)<<x.nome<<std::setw(10)<<x.chegada<<std::setw(8)<<x.burst<<std::setw(10)<<x.espera<<x.retorno<<"\n"; }
    std::cout<<"\n  Espera media: "<<se/p.size()<<"  |  Retorno medio: "<<sr/p.size()<<"\n";
}

void fifo(std::vector<Processo> p) {
    std::cout<<"\n"<<std::string(60,'=')<<"\n  FIFO (First Come First Served)\n"<<std::string(60,'=');
    std::sort(p.begin(),p.end(),[](auto&a,auto&b){return a.chegada<b.chegada;});
    std::vector<Fatia> g; int t=0;
    for (auto& x:p) { if(t<x.chegada)t=x.chegada; x.inicio=t; x.fim=t+x.burst; x.espera=x.inicio-x.chegada; x.retorno=x.fim-x.chegada; g.push_back({x.nome,x.burst}); t=x.fim; }
    gantt(g); metricas(p);
}

void sjf(std::vector<Processo> p) {
    std::cout<<"\n"<<std::string(60,'=')<<"\n  SJF (Shortest Job First)\n"<<std::string(60,'=');
    std::vector<Fatia> g; std::vector<bool> done(p.size(),false); int t=0,c=0,n=p.size();
    while(c<n) {
        int idx=-1;
        for(int i=0;i<n;i++) if(!done[i]&&p[i].chegada<=t) if(idx==-1||p[i].burst<p[idx].burst) idx=i;
        if(idx==-1){t++;continue;}
        p[idx].inicio=t; p[idx].fim=t+p[idx].burst; p[idx].espera=p[idx].inicio-p[idx].chegada; p[idx].retorno=p[idx].fim-p[idx].chegada;
        g.push_back({p[idx].nome,p[idx].burst}); t=p[idx].fim; done[idx]=true; c++;
    }
    gantt(g); metricas(p);
}

void rr(std::vector<Processo> p, int q) {
    std::cout<<"\n"<<std::string(60,'=')<<"\n  Round-Robin (quantum="<<q<<")\n"<<std::string(60,'=');
    int n=p.size(); std::vector<int> rem(n); for(int i=0;i<n;i++) rem[i]=p[i].burst;
    std::vector<Fatia> g; std::queue<int> fila; std::vector<bool> nf(n,false); int t=0,c=0;
    for(int i=0;i<n;i++) if(p[i].chegada==0){fila.push(i);nf[i]=true;}
    while(c<n) {
        if(fila.empty()){t++;continue;}
        int idx=fila.front(); fila.pop();
        int ex=std::min(q,rem[idx]);
        if(rem[idx]==p[idx].burst) p[idx].inicio=t;
        g.push_back({p[idx].nome,ex}); t+=ex; rem[idx]-=ex;
        for(int i=0;i<n;i++) if(!nf[i]&&p[i].chegada<=t&&rem[i]>0){fila.push(i);nf[i]=true;}
        if(rem[idx]==0){p[idx].fim=t;p[idx].retorno=p[idx].fim-p[idx].chegada;p[idx].espera=p[idx].retorno-p[idx].burst;c++;}
        else fila.push(idx);
    }
    gantt(g); metricas(p);
}

int main() {
    std::cout<<"\n╔══════════════════════════════════════════════════════════╗\n";
    std::cout<<  "║        DEMO 03: Escalonamento de Processos              ║\n";
    std::cout<<  "╚══════════════════════════════════════════════════════════╝\n";
    std::vector<Processo> procs={{"P1",0,6},{"P2",1,4},{"P3",2,2},{"P4",3,5},{"P5",4,3}};
    std::cout<<"\n  Processos: "; for(auto&p:procs) std::cout<<p.nome<<"(cheg="<<p.chegada<<",burst="<<p.burst<<") ";
    fifo(procs); sjf(procs); rr(procs,2);
    std::cout<<"\n  RESUMO: FIFO=simples; SJF=min espera(starvation!); RR=mais justo\n\n";
    return 0;
}
