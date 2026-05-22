/*
 * DEMO 06: Segmentação de Memória
 * Compile: g++ -std=c++17 -o demo6 06_segmentacao.cpp
 */
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <functional>

enum class Perm { R, RW };
struct Segmento { std::string nome; int base, limite; Perm perm; };

int traduzir(const std::vector<Segmento>& tab, int seg, int off, bool esc) {
    if(seg<0||seg>=(int)tab.size()) throw std::runtime_error("SEGFAULT: segmento invalido!");
    if(off<0||off>=tab[seg].limite) throw std::runtime_error("SEGFAULT: offset fora do limite!");
    if(esc&&tab[seg].perm==Perm::R) throw std::runtime_error("SEGFAULT: escrita em segmento somente-leitura!");
    return tab[seg].base+off;
}

void acesso(const std::vector<Segmento>& tab, int seg, int off, bool esc, const std::string& desc) {
    std::cout<<"\n  ["<<(esc?"ESCRITA":"LEITURA")<<"] "<<desc<<"\n";
    std::cout<<"  Virtual:(seg="<<seg<<",off="<<off<<") -> ";
    try { std::cout<<"Fisico:"<<traduzir(tab,seg,off,esc)<<"  [OK]\n"; }
    catch(std::exception& e){ std::cout<<e.what()<<" (SIGSEGV)\n"; }
}

int main() {
    std::cout<<"\n╔══════════════════════════════════════════════╗\n";
    std::cout<<  "║    DEMO 06: Segmentacao de Memoria           ║\n";
    std::cout<<  "╚══════════════════════════════════════════════╝\n";
    std::cout<<"\n  Endereco virtual = (num_segmento, offset)\n";
    std::cout<<"  Endereco fisico  = base[seg] + offset\n";
    std::cout<<"  MMU valida: offset < limite e permissao\n";

    std::vector<Segmento> tab={{"CODE",1000,500,Perm::R},{"DATA",2000,300,Perm::RW},{"STACK",5000,200,Perm::RW}};
    std::cout<<"\n  Tabela de Segmentos:\n";
    std::cout<<"  "<<std::string(48,'-')<<"\n";
    std::cout<<"  "<<std::setw(4)<<"Seg"<<std::setw(8)<<"Nome"<<std::setw(8)<<"Base"<<std::setw(8)<<"Limite"<<std::setw(6)<<"Perm\n";
    std::cout<<"  "<<std::string(48,'-')<<"\n";
    for(int i=0;i<(int)tab.size();i++) std::cout<<"  "<<std::setw(4)<<i<<std::setw(8)<<tab[i].nome<<std::setw(8)<<tab[i].base<<std::setw(8)<<tab[i].limite<<std::setw(6)<<(tab[i].perm==Perm::R?"R":"R/W")<<"\n";

    std::cout<<"\n  --- Acessos validos ---";
    acesso(tab,0,100,false,"Ler instrucao do programa (CODE)");
    acesso(tab,1, 50,true, "Escrever em variavel global (DATA)");
    acesso(tab,2,180,true, "Push na pilha (STACK)");

    std::cout<<"\n  --- Violacoes (devem falhar!) ---";
    acesso(tab,0, 10,true, "Tentar escrever no codigo (injecao!)");
    acesso(tab,1,999,false,"Ler alem do limite de DATA");
    acesso(tab,9,  0,false,"Segmento 9 inexistente");

    std::cout<<"\n  Segmentacao: blocos VARIAVEIS, frag EXTERNA, logico\n";
    std::cout<<"  Paginacao  : blocos FIXOS,    frag INTERNA, fisico\n\n";
    return 0;
}
