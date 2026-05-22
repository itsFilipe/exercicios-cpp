/*
 * DEMO 09: Starvation e Escalonamento com Aging
 * Compile: g++ -std=c++17 -o demo9 09_starvation_prioridade.cpp
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

struct P{ std::string nome; int prio_orig, prio_atual, chegada, burst, espera; bool done; };

void sem_aging(){
    std::cout<<"\n"<<std::string(58,'=')<<"\n  PARTE 1: Prioridade pura (sem aging) -> STARVATION\n"<<std::string(58,'=')<<"\n";
    std::vector<P> ps={{"P_alta1",1,1,0,3,0,false},{"P_alta2",1,1,2,3,0,false},{"P_alta3",1,1,4,3,0,false},{"P_baixa",5,5,0,2,0,false}};
    int t=0,c=0;
    while(c<(int)ps.size()&&t<25){
        for(auto&p:ps) if(p.chegada==t) std::cout<<"  [t="<<t<<"] "<<p.nome<<" chega (prio="<<p.prio_orig<<")\n";
        P* sel=nullptr;
        for(auto&p:ps) if(!p.done&&p.chegada<=t) if(!sel||p.prio_atual<sel->prio_atual) sel=&p;
        if(sel){std::cout<<"  [t="<<t<<"] CPU -> "<<sel->nome<<" (prio="<<sel->prio_atual<<")\n";t+=sel->burst;sel->done=true;c++;for(auto&p:ps)if(!p.done&&p.chegada<=t)p.espera+=sel->burst;}
        else t++;
    }
    std::cout<<"\n  Resultado:\n";
    for(auto&p:ps) std::cout<<"  "<<std::setw(10)<<p.nome<<(p.done?" -> CONCLUIDO":" -> STARVATION! Nunca rodou.")<<" espera="<<p.espera<<"\n";
}

void com_aging(){
    std::cout<<"\n"<<std::string(58,'=')<<"\n  PARTE 2: Prioridade + AGING -> Sem starvation\n  Regra: a cada 2u de espera, prioridade melhora 1\n"<<std::string(58,'=')<<"\n";
    std::vector<P> ps={{"P_alta1",1,1,0,3,0,false},{"P_alta2",1,1,2,3,0,false},{"P_alta3",1,1,4,3,0,false},{"P_baixa",5,5,0,2,0,false}};
    int t=0,c=0;
    while(c<(int)ps.size()&&t<30){
        for(auto&p:ps) if(p.chegada==t) std::cout<<"  [t="<<t<<"] "<<p.nome<<" chega\n";
        for(auto&p:ps) if(!p.done&&p.chegada<=t&&p.espera>0) p.prio_atual=std::max(1,p.prio_orig-p.espera/2);
        P* sel=nullptr;
        for(auto&p:ps) if(!p.done&&p.chegada<=t) if(!sel||p.prio_atual<sel->prio_atual) sel=&p;
        if(sel){std::cout<<"  [t="<<t<<"] CPU -> "<<sel->nome<<" (prio_orig="<<sel->prio_orig<<" prio_atual="<<sel->prio_atual<<" esp="<<sel->espera<<")\n";t+=sel->burst;sel->done=true;c++;for(auto&p:ps)if(!p.done&&p.chegada<=t)p.espera+=sel->burst;}
        else t++;
    }
    std::cout<<"\n  Resultado:\n";
    for(auto&p:ps) std::cout<<"  "<<std::setw(10)<<p.nome<<(p.done?" -> CONCLUIDO":" -> ainda esperando")<<" espera="<<p.espera<<"\n";
    std::cout<<"\n  Com aging, P_baixa foi promovida e rodou!\n";
    std::cout<<"  Linux CFS usa vruntime (aging automatico).\n\n";
}

int main(){
    std::cout<<"\n╔══════════════════════════════════════════════════════╗\n";
    std::cout<<  "║   DEMO 09: Starvation + Prioridade + Aging          ║\n";
    std::cout<<  "╚══════════════════════════════════════════════════════╝\n";
    std::cout<<"\n  Starvation: processo de baixa prioridade nunca roda\n";
    std::cout<<"  pois processos de alta chegam continuamente.\n";
    std::cout<<"  Aging: quanto mais espera, maior a prioridade.\n";
    sem_aging();
    com_aging();
    return 0;
}
