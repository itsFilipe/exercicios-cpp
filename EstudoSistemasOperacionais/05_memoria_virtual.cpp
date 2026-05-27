/*
 * DEMO 05: Memória Virtual e Page Replacement
 * Compile: g++ -std=c++17 -o demo5 05_memoria_virtual.cpp
 *
 * FIFO vs LRU page replacement com visualização passo a passo
 */
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <optional>
#include <iomanip>

struct PTE { bool presente; int frame; }; // Page Table Entry

void mostrar(const std::map<int,PTE>& tab, const std::vector<std::optional<int>>& frames, int pf, int total) {
    std::cout<<"  RAM:[";
    for(int i=0;i<(int)frames.size();i++){if(i)std::cout<<"|";if(frames[i])std::cout<<"P"<<std::setw(2)<<*frames[i];else std::cout<<"   ";}
    std::cout<<"]  PF="<<pf<<"/"<<total<<"\n";
}

void fifo_sim(const std::vector<int>& seq, int nf) {
    std::cout<<"\n"<<std::string(58,'=')<<"\n  FIFO Page Replacement\n  Regra: a pagina mais ANTIGA sai.\n"<<std::string(58,'=')<<"\n";
    std::vector<std::optional<int>> frames(nf);
    std::map<int,PTE> tab; std::list<int> ordem; int pf=0;
    for(int i=0;i<(int)seq.size();i++){
        int pg=seq[i]; std::cout<<"\n  Acesso ["<<i+1<<"]: P"<<pg;
        if(tab.count(pg)&&tab[pg].presente){std::cout<<" -> HIT\n";}
        else{
            pf++; std::cout<<" -> PAGE FAULT\n";
            int fl=-1; for(int f=0;f<nf;f++) if(!frames[f]){fl=f;break;}
            if(fl!=-1){frames[fl]=pg;tab[pg]={true,fl};ordem.push_back(pg);std::cout<<"  Carregou P"<<pg<<" no Frame "<<fl<<"\n";}
            else{int v=ordem.front();ordem.pop_front();int fv=tab[v].frame;std::cout<<"  Remove P"<<v<<", carrega P"<<pg<<" no Frame "<<fv<<"\n";tab[v].presente=false;frames[fv]=pg;tab[pg]={true,fv};ordem.push_back(pg);}
        }
        mostrar(tab,frames,pf,i+1);
    }
    std::cout<<"\n  RESULTADO FIFO: "<<pf<<" page faults em "<<seq.size()<<" acessos ("<<100.0*pf/seq.size()<<"% miss)\n";
}

void lru_sim(const std::vector<int>& seq, int nf) {
    std::cout<<"\n"<<std::string(58,'=')<<"\n  LRU Page Replacement\n  Regra: a pagina MENOS RECENTEMENTE USADA sai.\n"<<std::string(58,'=')<<"\n";
    std::vector<std::optional<int>> frames(nf);
    std::map<int,PTE> tab; std::list<int> lru; int pf=0;
    for(int i=0;i<(int)seq.size();i++){
        int pg=seq[i]; std::cout<<"\n  Acesso ["<<i+1<<"]: P"<<pg;
        if(tab.count(pg)&&tab[pg].presente){std::cout<<" -> HIT\n";lru.remove(pg);lru.push_front(pg);}
        else{
            pf++; std::cout<<" -> PAGE FAULT\n";
            int fl=-1; for(int f=0;f<nf;f++) if(!frames[f]){fl=f;break;}
            if(fl!=-1){frames[fl]=pg;tab[pg]={true,fl};lru.push_front(pg);std::cout<<"  Carregou P"<<pg<<" no Frame "<<fl<<"\n";}
            else{int v=lru.back();lru.pop_back();int fv=tab[v].frame;std::cout<<"  Remove P"<<v<<" (menos recente), carrega P"<<pg<<"\n";tab[v].presente=false;frames[fv]=pg;tab[pg]={true,fv};lru.push_front(pg);}
        }
        mostrar(tab,frames,pf,i+1);
    }
    std::cout<<"\n  RESULTADO LRU: "<<pf<<" page faults em "<<seq.size()<<" acessos ("<<100.0*pf/seq.size()<<"% miss)\n";
}

int main() {
    std::cout<<"\n╔══════════════════════════════════════════════════════╗\n";
    std::cout<<  "║     DEMO 05: Memoria Virtual e Page Replacement     ║\n";
    std::cout<<  "╚══════════════════════════════════════════════════════╝\n";
    std::cout<<"\n  Processo usa enderecos VIRTUAIS (paginas).\n";
    std::cout<<"  MMU traduz pagina -> frame fisico na RAM.\n";
    std::cout<<"  Page Fault: pagina nao esta na RAM -> busca no disco.\n";
    std::vector<int> seq={1,2,3,4,1,2,5,1,2,3,4,5};
    int nf=3;
    std::cout<<"\n  Sequencia: "; for(int p:seq) std::cout<<"P"<<p<<" ";
    std::cout<<"\n  Frames na RAM: "<<nf<<"\n";
    fifo_sim(seq,nf);
    lru_sim(seq,nf);
    std::cout<<"\n  COMPARATIVO:\n";
    std::cout<<"  FIFO: simples, sofre Anomalia de Belady\n";
    std::cout<<"  LRU:  mais inteligente, Linux usa variante (Clock/2Q)\n\n";
    return 0;
}
