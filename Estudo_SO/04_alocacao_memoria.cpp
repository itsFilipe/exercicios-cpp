/*
 * DEMO 04: Estratégias de Alocação de Memória
 * Compile: g++ -std=c++17 -o demo4 04_alocacao_memoria.cpp
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <functional>

struct Bloco { int inicio, tamanho; bool livre; std::string proc; };
using Mem = std::vector<Bloco>;
struct Aloc { std::string proc; int tam; };

void imprimir_mem(const Mem& m) {
    std::cout << "  [";
    for (auto& b : m) {
        int w = b.tamanho * 2; std::string l = b.livre ? std::string(w,'.') : b.proc;
        while((int)l.size()<w) l+=" "; if((int)l.size()>w) l=l.substr(0,w);
        std::cout << l;
    }
    std::cout << "]\n";
}

void alocar_bloco(Mem& m, int idx, const Aloc& a) {
    int sobra = m[idx].tamanho - a.tam;
    m[idx].livre=false; m[idx].proc=a.proc; m[idx].tamanho=a.tam;
    if (sobra>0) m.insert(m.begin()+idx+1, {m[idx].inicio+a.tam, sobra, true, ""});
}

Mem mem_inicial() {
    return {{0,10,false,"OS"},{10,15,true,""},{25,5,false,"PX"},{30,20,true,""},{50,10,false,"PY"}};
}

bool first_fit(Mem& m, const Aloc& a) {
    for(int i=0;i<(int)m.size();i++) if(m[i].livre&&m[i].tamanho>=a.tam){alocar_bloco(m,i,a);return true;}
    return false;
}
bool best_fit(Mem& m, const Aloc& a) {
    int best=-1,menor=INT_MAX;
    for(int i=0;i<(int)m.size();i++) if(m[i].livre&&m[i].tamanho>=a.tam){int s=m[i].tamanho-a.tam;if(s<menor){menor=s;best=i;}}
    if(best==-1)return false; alocar_bloco(m,best,a); return true;
}
bool worst_fit(Mem& m, const Aloc& a) {
    int worst=-1,maior=-1;
    for(int i=0;i<(int)m.size();i++) if(m[i].livre&&m[i].tamanho>=a.tam&&m[i].tamanho>maior){maior=m[i].tamanho;worst=i;}
    if(worst==-1)return false; alocar_bloco(m,worst,a); return true;
}
bool next_fit(Mem& m, const Aloc& a, int& ult) {
    int n=m.size();
    for(int k=0;k<n;k++){int i=(ult+k)%n;if(m[i].livre&&m[i].tamanho>=a.tam){alocar_bloco(m,i,a);ult=i;return true;}}
    return false;
}

void rodar(const std::string& nome, const std::vector<Aloc>& pedidos, std::function<bool(Mem&,const Aloc&)> fn) {
    std::cout<<"\n"<<std::string(58,'-')<<"\n  "<<nome<<"\n"<<std::string(58,'-')<<"\n";
    Mem m=mem_inicial(); std::cout<<"  Inicial: "; imprimir_mem(m);
    for(auto& a:pedidos) {
        std::cout<<"\n  -> "<<a.proc<<"("<<a.tam<<"u): ";
        std::cout<<(fn(m,a)?"OK":"FALHOU")<<"\n";
        imprimir_mem(m);
    }
    int livre=0,maior=0; for(auto& b:m) if(b.livre){livre+=b.tamanho;maior=std::max(maior,b.tamanho);}
    std::cout<<"  Livre total="<<livre<<"  Maior bloco="<<maior<<"  Frag.externa="<<(livre-maior)<<"\n";
}

int main() {
    std::cout<<"\n╔═══════════════════════════════════════════════════════╗\n";
    std::cout<<  "║    DEMO 04: Estrategias de Alocacao de Memoria        ║\n";
    std::cout<<  "╚═══════════════════════════════════════════════════════╝\n";
    std::cout<<"\n  Legenda: OS=sistema  PX/PY=ja alocados  '.'=livre\n";
    std::vector<Aloc> pedidos={{"P1",8},{"P2",12},{"P3",3}};
    std::cout<<"  Pedidos: "; for(auto& a:pedidos) std::cout<<a.proc<<"("<<a.tam<<"u) ";
    rodar("FIRST-FIT  (1o bloco que cabe)", pedidos, [](Mem& m, const Aloc& a){return first_fit(m,a);});
    rodar("BEST-FIT   (menor bloco que cabe)", pedidos, [](Mem& m, const Aloc& a){return best_fit(m,a);});
    rodar("WORST-FIT  (maior bloco disponivel)", pedidos, [](Mem& m, const Aloc& a){return worst_fit(m,a);});
    int ult=0;
    rodar("NEXT-FIT   (continua de onde parou)", pedidos, [&](Mem& m, const Aloc& a){return next_fit(m,a,ult);});
    std::cout<<"\n  RESUMO: First=rapido | Best=frag.minima | Worst=sobra util | Next=uniforme\n\n";
    return 0;
}
